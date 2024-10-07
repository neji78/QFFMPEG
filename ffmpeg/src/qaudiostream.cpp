#include "qaudiostream.h"

QAudioStream::QAudioStream(const AVStream& stream):
    m_codec(*stream.codecpar)
{
    m_duration = stream.duration;
    m_sampleRate = stream.codecpar->sample_rate;
}

QAudioStream QAudioStream::operator =(const QAudioStream &obj)
{
    m_codec = obj.codec();
    m_sampleRate = obj.sampleRate();
    m_duration = obj.duration();
    return *this;
}

QCodec QAudioStream::codec() const
{
    return m_codec;
}

quint64 QAudioStream::duration() const
{
    return m_duration;
}

quint64 QAudioStream::sampleRate() const
{
    return m_sampleRate;
}
QDebug operator<<(QDebug dbg, const QAudioStream &data)
{
    dbg.nospace() << "QAudioStream(" <<
        "codec: "<<data.codec() <<
        ", sampleRate: "<<data.sampleRate() <<
        ", duration: "<<data.duration()
                  << ")";
    return dbg.maybeSpace();
}
