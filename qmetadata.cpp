#include "qmetadata.h"
extern "C"{
#include <libavformat/avformat.h>
}
QMetaData::QMetaData(const QVariantMap& data)
{
    m_creationTime = data.value("creation_time").toDateTime();
    m_title = data.value("title").toString();
    m_majorBrand = data.value("major_brand").toString();
    m_copyRight = data.value("copyRight").toString();
    m_compatibleBrands = data.value("compatible_brands").toString().split(" ");
    m_minorVersion = data.value("minor_version").toInt();
    m_mediaType = data.value("media_type").toInt();
    if(m_mediaType == AVMEDIA_TYPE_AUDIO){
         m_audioData = QAudioData(data);
    }
}

bool QMetaData::operator ==(const QMetaData &obj)
{
    return m_title == obj.title();
}
QDebug operator<<(QDebug dbg, const QMetaData &data)
{
    dbg.nospace() << "QMetaData(" <<
        "audioData: "<<data.audioData() <<
        ", compatibleBrands: "<<data.compatibleBrands() <<
        ", copyRight: "<<data.copyRight() <<
        ", creationTime: "<<data.creationTime() <<
        ", majorBrand: "<<data.majorBrand() <<
        ", mediaType: "<<data.mediaType() <<
        ", minorVersion: "<<data.minorVersion() <<
        ", title: "<<data.title()
                  << ")";
    return dbg.maybeSpace();
}
QDateTime QMetaData::creationTime() const
{
    return m_creationTime;
}

QString QMetaData::title() const
{
    return m_title;
}

QString QMetaData::majorBrand() const
{
    return m_majorBrand;
}

QString QMetaData::copyRight() const
{
    return m_copyRight;
}

QStringList QMetaData::compatibleBrands() const
{
    return m_compatibleBrands;
}

int QMetaData::minorVersion() const
{
    return m_minorVersion;
}

int QMetaData::mediaType() const
{
    return m_mediaType;
}

QAudioData QMetaData::audioData() const
{
    return m_audioData;
}
