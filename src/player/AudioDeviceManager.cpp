#include "AudioDeviceManager.h"
#include <mpv/client.h>
#include "QsLog.h"

AudioDeviceManager::AudioDeviceManager(mpv::qt::Handle mpv, QObject* parent)
    : QObject(parent), m_mpv(mpv)
{
}

void AudioDeviceManager::setVolume(int volume)
{
    m_mpv.setProperty("volume", volume);
}

int AudioDeviceManager::volume() const
{
    return m_mpv.getProperty("volume", 0);
}

void AudioDeviceManager::setMuted(bool muted)
{
    m_mpv.setProperty("mute", muted);
}

bool AudioDeviceManager::muted() const
{
    return m_mpv.getProperty("mute", false);
}

QVariant AudioDeviceManager::getAudioDeviceList()
{
    // Implementation details would be moved here from PlayerComponent
    return QVariant();
}

void AudioDeviceManager::setAudioDevice(const QString& name)
{
    m_mpv.setProperty("audio-device", name.toStdString());
}

void AudioDeviceManager::setAudioDelay(qint64 milliseconds)
{
    m_mpv.setProperty("audio-delay", (double)milliseconds / 1000.0);
}

void AudioDeviceManager::updateAudioDeviceList()
{
    // Implementation details would be moved here
}

void AudioDeviceManager::checkCurrentAudioDevice(const QSet<QString>& old_devs, const QSet<QString>& new_devs)
{
    // Implementation details would be moved here
}
