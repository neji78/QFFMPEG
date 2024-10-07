#ifndef QCODEC_H
#define QCODEC_H
extern "C"{
#include <libavformat/avformat.h>
}

#include <QtGlobal>
#include <QDebug>
class QCodec
{
public:
    QCodec(){}
    QCodec(const AVCodecParameters& codec);
    QCodec operator =(const QCodec& obj);
    AVMediaType getType() const;
    AVCodecID getId() const;
    qint64 getBitrate() const;
    friend QDebug operator<<(QDebug dbg, const QCodec &data);

    QString getName() const;

    QString getTypeName() const;

private:
    AVMediaType m_type;
    QString m_name;
    AVCodecID m_id;
    qint64 m_bitrate;
};

#endif // QCODEC_H
