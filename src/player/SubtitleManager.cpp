#include "SubtitleManager.h"

SubtitleManager::SubtitleManager(mpv::qt::Handle mpv, QObject* parent)
    : QObject(parent), m_mpv(mpv)
{
}

void SubtitleManager::setSubtitleStream(const QString& subtitleStream)
{
    m_currentSubtitleStream = subtitleStream;
}

void SubtitleManager::setSubtitleDelay(qint64 milliseconds)
{
    mpv::qt::set_property(m_mpv, "sub-delay", milliseconds / 1000.0);
}
