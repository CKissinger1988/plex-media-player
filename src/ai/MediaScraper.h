#ifndef __MEDIASCRAPER_H__
#define __MEDIASCRAPER_H__

#include "core/ComponentManager.h"
#include "utils/Utils.h"
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QObject>

class MediaScraper : public ComponentBase
{
  Q_OBJECT
  DEFINE_SINGLETON(MediaScraper);

public:
  bool componentInitialize() override;
  const char* componentName() override { return "MediaScraper"; }
  bool componentExport() override { return true; }

public slots:
  QString searchMovies(const QString& query, int limit = 20, const QString& genre = "",
                       const QString& year = "", const QString& media_type = "all");
  QString getTvDetails(const QString& tv_id);
  QString getSeasonDetails(const QString& tv_id, int season_number);
  QString getGenres();
  QString getTrendingMovies(int limit = 20);

private:
  MediaScraper();
  ~MediaScraper() override;

  QNetworkAccessManager* m_networkManager;
  QString syncRequest(const QString& urlStr);
  QJsonObject formatMovieItem(const QJsonObject& m);
};

#endif
