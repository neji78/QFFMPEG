#include "qvideostream.h"

QVideoStream::QVideoStream(const AVStream& stream):
    m_codec(*stream.codecpar)
{
    m_duration = stream.duration;
    m_resolution = QSize(stream.codecpar->width , stream.codecpar->height );
}

QVideoStream QVideoStream::operator =(const QVideoStream &obj)
{
    m_codec = obj.codec();
    m_resolution = obj.resolution();
    m_duration = obj.duration();
    return *this;
}

QCodec QVideoStream::codec() const
{
    return m_codec;
}

QSize QVideoStream::resolution() const
{
    return m_resolution;
}

quint64 QVideoStream::duration() const
{
    return m_duration;
}
QDebug operator<<(QDebug dbg, const QVideoStream &data)
{
    dbg.nospace() << "QVideoStream(" <<
        "QCodec: "<<data.codec() <<
        ", m_resolution: "<<data.resolution() <<
        ", m_duration: "<<data.duration()
                  << ")";
    return dbg.maybeSpace();
}
