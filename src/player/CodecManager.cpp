#include "CodecManager.h"
#include "QsLog.h"
#include "CodecsComponent.h"

#ifdef TARGET_RPI
#include <bcm_host.h>
#include <interface/vmcs_host/vcgencmd.h>
#endif

CodecManager::CodecManager(mpv::qt::Handle mpv, QObject* parent)
    : QObject(parent), m_mpv(mpv)
{
}

void CodecManager::initializeCodecSupport()
{
    QMap<QString, QString> all = { { "vc1", "WVC1" }, { "mpeg2video", "MPG2" } };
    for (auto name : all.keys())
    {
        bool ok = true;
#ifdef TARGET_RPI
        char res[100] = "";
        bcm_host_init();
        if (vc_gencmd(res, sizeof(res), "codec_enabled %s", all[name].toUtf8().data()))
            res[0] = '\0'; // error
        ok = !!strstr(res, "=enabled");
#endif
        m_codecSupport[name] = ok;
        QLOG_INFO() << "Codec" << name << (ok ? "present" : "disabled");
    }
}

bool CodecManager::checkCodecSupport(const QString& codec)
{
    if (m_codecSupport.contains(codec))
        return m_codecSupport[codec];
    return true;
}

QList<CodecDriver> convertCodecList(mpv::qt::Handle mpv, QVariant list, CodecType type)
{
    QList<CodecDriver> codecs;
    foreach (const QVariant& e, list.toList())
    {
        QVariantMap map = e.toMap();
        QString family = map["family"].toString();
        QString codec = map["codec"].toString();
        QString driver = map["driver"].toString();

        if (family != "" && family != "lavc")
            continue;

        CodecDriver ncodec = {};
        ncodec.type = type;
        ncodec.format = codec;
        ncodec.driver = driver;
        ncodec.present = true;
        codecs.append(ncodec);
    }
    return codecs;
}

QList<CodecDriver> CodecManager::installedCodecDrivers()
{
    QList<CodecDriver> codecs;
    codecs.append(convertCodecList(m_mpv, mpv::qt::get_property(m_mpv, "decoder-list"), CodecType::Decoder));
    codecs.append(convertCodecList(m_mpv, mpv::qt::get_property(m_mpv, "encoder-list"), CodecType::Encoder));
    return codecs;
}

QStringList CodecManager::installedDecoderCodecs()
{
    QStringList formats;
    bool hasPcm = false;
    for (auto driver : installedCodecDrivers())
    {
        if (driver.type == CodecType::Decoder && checkCodecSupport(driver.format))
        {
            QString name = Codecs::plexNameFromFF(driver.format);
            if (name.startsWith("pcm_") && name != "pcm_bluray" && name != "pcm_dvd")
            {
                if (hasPcm)
                    continue;
                hasPcm = true;
                name = "pcm";
            }
            formats.append(name);
        }
    }
    return formats;
}
