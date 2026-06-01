#ifndef SUBTITLEMANAGER_H
#define SUBTITLEMANAGER_H

#include <QObject>
#include <QString>
#include <mpv/client.h>
#include "QtHelper.h"

class SubtitleManager : public QObject
{
    Q_OBJECT
public:
    explicit SubtitleManager(mpv::qt::Handle mpv, QObject* parent = nullptr);

    void setSubtitleStream(const QString& subtitleStream);
    void setSubtitleDelay(qint64 milliseconds);

private:
    mpv::qt::Handle m_mpv;
    QString m_currentSubtitleStream;
};

#endif // SUBTITLEMANAGER_H
