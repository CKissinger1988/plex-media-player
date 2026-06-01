#ifndef CODECMANAGER_H
#define CODECMANAGER_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QVariant>
#include <mpv/client.h>
#include "QtHelper.h"

enum class CodecType { Decoder, Encoder };

struct CodecDriver {
    CodecType type;
    QString format;
    QString driver;
    bool present;
};

class CodecManager : public QObject
{
    Q_OBJECT
public:
    explicit CodecManager(mpv::qt::Handle mpv, QObject* parent = nullptr);

    void initializeCodecSupport();
    bool checkCodecSupport(const QString& codec);
    QList<CodecDriver> installedCodecDrivers();
    QStringList installedDecoderCodecs();

private:
    mpv::qt::Handle m_mpv;
    QMap<QString, bool> m_codecSupport;
};

#endif // CODECMANAGER_H
