#ifndef AUDIODEVICEMANAGER_H
#define AUDIODEVICEMANAGER_H

#include <QObject>
#include <QVariant>
#include <QSet>
#include <mpv/client.h>
#include "QtHelper.h"

class AudioDeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit AudioDeviceManager(mpv::qt::Handle mpv, QObject* parent = nullptr);

    void setVolume(int volume);
    int volume() const;
    void setMuted(bool muted);
    bool muted() const;
    QVariant getAudioDeviceList();
    void setAudioDevice(const QString& name);
    void setAudioDelay(qint64 milliseconds);
    void updateAudioDeviceList();
    void checkCurrentAudioDevice(const QSet<QString>& old_devs, const QSet<QString>& new_devs);

private:
    mpv::qt::Handle m_mpv;
    QSet<QString> m_audioDevices;
};

#endif // AUDIODEVICEMANAGER_H
