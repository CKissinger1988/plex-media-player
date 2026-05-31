#include "MediaScraper.h"
#include "QsLog.h"
#include <QEventLoop>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QUrlQuery>

const QString TMDB_API_KEY = "829a43a98259bc44cae297489c7e3bba";
const QString TMDB_BASE_URL = "https://api.themoviedb.org/3";
const QString POSTER_BASE_URL = "https://image.tmdb.org/t/p/w500";

MediaScraper::MediaScraper() : ComponentBase(nullptr)
{
  m_networkManager = new QNetworkAccessManager(this);
}

MediaScraper::~MediaScraper() {}

bool MediaScraper::componentInitialize()
{
  QLOG_INFO() << "MediaScraper initializing...";
  return true;
}

QString MediaScraper::syncRequest(const QString& urlStr)
{
  QNetworkRequest request((QUrl(urlStr)));
  request.setHeader(QNetworkRequest::UserAgentHeader,
                    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like "
                    "Gecko) Chrome/120.0.0.0 Safari/537.36");

  QNetworkReply* reply = m_networkManager->get(request);
  QEventLoop loop;
  connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
  loop.exec();

  QString result;
  if (reply->error() == QNetworkReply::NoError)
  {
    result = QString::fromUtf8(reply->readAll());
  }
  else
  {
    QLOG_ERROR() << "TMDB Request Error:" << reply->errorString();
  }
  reply->deleteLater();
  return result;
}

static QString getSlug(const QString& text)
{
  QString slug = text.toLower();
  slug.replace(QRegularExpression("[^a-z0-9]+"), "-");
  if (slug.startsWith("-"))
    slug = slug.mid(1);
  if (slug.endsWith("-"))
    slug.chop(1);
  return slug;
}

QJsonObject MediaScraper::formatMovieItem(const QJsonObject& m)
{
  QJsonObject item;

  QString tmdb_id = m.contains("id") ? QString::number(m["id"].toInt()) : "";
  QString title = m.contains("title") ?
                  m["title"].toString() :
                  (m.contains("name") ? m["name"].toString() : "Unknown Title");
  QString release_date = m.contains("release_date") ?
                         m["release_date"].toString() :
                         (m.contains("first_air_date") ? m["first_air_date"].toString() : "");
  QString year = !release_date.isEmpty() ? release_date.split("-").first() : "N/A";

  QString poster_path = m["poster_path"].toString();
  QString thumbnail_url = !poster_path.isEmpty() ?
                          (POSTER_BASE_URL + poster_path) :
                          "https://watchseries.bar/assets/img/no-poster.svg";

  QString slug = getSlug(title);
  bool is_tv = m.contains("first_air_date") || m["media_type"].toString() == "tv";
  QString site_url =
  QString("https://watchseries.bar/%1/%2/%3").arg(is_tv ? "tv-series" : "movie", slug, tmdb_id);

  QString embed_url = QString("https://vidsrc.to/embed/%1/%2").arg(is_tv ? "tv" : "movie", tmdb_id);

  item["id"] = tmdb_id;
  item["title"] = QString("%1 (%2)").arg(title, year);
  item["image_url"] = thumbnail_url;
  item["thumbnail_url"] = thumbnail_url;
  item["page_url"] = site_url;
  item["video_url"] = embed_url;
  item["type"] = "video";
  item["description"] =
  m.contains("overview") ? m["overview"].toString() : "Secure encrypted stream source.";
  item["rating"] = m["vote_average"].toDouble();
  item["is_tv"] = is_tv;

  return item;
}

QString MediaScraper::searchMovies(const QString& query, int limit, const QString& genre,
                                   const QString& year, const QString& media_type)
{
  QString url;
  if (query.isEmpty())
  {
    url = QString("%1/discover/%2?api_key=%3&sort_by=popularity.desc")
          .arg(TMDB_BASE_URL, media_type == "movie" ? "movie" : "tv", TMDB_API_KEY);
    if (!genre.isEmpty())
      url += "&with_genres=" + genre;
    if (!year.isEmpty())
      url += QString("&%1=%2").arg(
      media_type == "movie" ? "primary_release_year" : "first_air_date_year", year);
  }
  else
  {
    url = QString("%1/search/multi?api_key=%2&query=%3")
          .arg(TMDB_BASE_URL, TMDB_API_KEY, QString::fromUtf8(QUrl::toPercentEncoding(query)));
  }

  QString response = syncRequest(url);
  if (response.isEmpty())
    return "[]";

  QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
  QJsonArray results = doc.object()["results"].toArray();

  QJsonArray formattedResults;
  int count = 0;
  for (int i = 0; i < results.size() && count < limit; ++i)
  {
    QJsonObject m = results[i].toObject();
    QString m_type =
    m.contains("media_type") ? m["media_type"].toString() : (m.contains("title") ? "movie" : "tv");
    if (media_type != "all" && m_type != media_type)
      continue;

    formattedResults.append(formatMovieItem(m));
    count++;
  }

  return QJsonDocument(formattedResults).toJson(QJsonDocument::Compact);
}

QString MediaScraper::getTvDetails(const QString& tv_id)
{
  QString url = QString("%1/tv/%2?api_key=%3").arg(TMDB_BASE_URL, tv_id, TMDB_API_KEY);
  return syncRequest(url);
}

QString MediaScraper::getSeasonDetails(const QString& tv_id, int season_number)
{
  QString url = QString("%1/tv/%2/season/%3?api_key=%4")
                .arg(TMDB_BASE_URL, tv_id, QString::number(season_number), TMDB_API_KEY);
  return syncRequest(url);
}

QString MediaScraper::getGenres()
{
  QString url = QString("%1/genre/movie/list?api_key=%2").arg(TMDB_BASE_URL, TMDB_API_KEY);
  QString response = syncRequest(url);
  if (response.isEmpty())
    return "[]";
  QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
  return QJsonDocument(doc.object()["genres"].toArray()).toJson(QJsonDocument::Compact);
}

QString MediaScraper::getTrendingMovies(int limit)
{
  QString url = QString("%1/trending/all/day?api_key=%2").arg(TMDB_BASE_URL, TMDB_API_KEY);
  QString response = syncRequest(url);
  if (response.isEmpty())
    return "[]";

  QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
  QJsonArray results = doc.object()["results"].toArray();

  QJsonArray formattedResults;
  for (int i = 0; i < qMin(results.size(), limit); ++i)
  {
    formattedResults.append(formatMovieItem(results[i].toObject()));
  }

  return QJsonDocument(formattedResults).toJson(QJsonDocument::Compact);
}
