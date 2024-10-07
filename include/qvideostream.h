#ifndef QVIDEOSTREAM_H
#define QVIDEOSTREAM_H
#include <qcodec.h>
#include <QSize>

class QVideoStream
{
public:
    QVideoStream(){}
    QVideoStream(const AVStream& stream);
    QVideoStream operator =(const QVideoStream& obj);
    QCodec codec() const;
    QSize resolution() const;
    quint64 duration() const;
    friend QDebug operator<<(QDebug dbg, const QVideoStream &data);
private:
    QCodec m_codec;
    QSize m_resolution;
    quint64 m_duration;
};

#endif // QVIDEOSTREAM_H
