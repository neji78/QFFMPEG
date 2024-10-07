#ifndef QAUDIOSTREAM_H
#define QAUDIOSTREAM_H

#include <qcodec.h>
class QAudioStream
{
public:
    QAudioStream(){}
    QAudioStream(const AVStream& stream);
    QAudioStream operator =(const QAudioStream& obj);
    QCodec codec() const;
    quint64 duration() const;
    quint64 sampleRate() const;
    friend QDebug operator<<(QDebug dbg, const QAudioStream &data);

private:
    QCodec m_codec;
    quint64 m_sampleRate;
    quint64 m_duration;
};

#endif // QAUDIOSTREAM_H
