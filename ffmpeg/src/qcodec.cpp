#include "qcodec.h"
#include <qffmpegutility.h>
#include <QMetaEnum>
QCodec::QCodec(const AVCodecParameters& codec)
{
    m_type = codec.codec_type;
    m_id = codec.codec_id;
    m_bitrate = codec.bit_rate;
    m_name = avcodec_get_name(m_id);
}

QCodec QCodec::operator =(const QCodec &obj)
{
    m_type = obj.getType();
    m_id = obj.getId();
    m_bitrate = obj.getBitrate();
    m_name = obj.getName();
    return *this;
}

AVMediaType QCodec::getType() const
{
    return m_type;
}

AVCodecID QCodec::getId() const
{
    return m_id;
}

qint64 QCodec::getBitrate() const
{
    return m_bitrate;
}

QString QCodec::getName() const
{
    return m_name;
}

QString QCodec::getTypeName() const
{
    return av_get_media_type_string(m_type);
}
QDebug operator<<(QDebug dbg, const QCodec &data)
{
    dbg.nospace() << "QCodec(" <<
        "type: "<<data.getTypeName() <<
        ", id: "<<data.getId() <<
        ", name: "<<data.getName() <<
        ", bitrate: "<<data.getBitrate()
                  << ")";
    return dbg.maybeSpace();
}
