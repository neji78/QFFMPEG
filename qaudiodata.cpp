#include "qaudiodata.h"

QAudioData::QAudioData(const QVariantMap &data)
{
    m_artist = data.value("artist").toString();
    m_album = data.value("album").toString();
    m_genre = data.value("genre").toString();
    m_track = data.value("track").toString();
    m_disc = data.value("disc").toString();
    m_lyrics = data.value("lyrics").toString();
    m_composer = data.value("composer").toString().split(",");
    m_compilation = data.value("compilation").toInt();
    m_gaplessPlayback = data.value("gapless_playback").toInt();
    m_rating = data.value("rating").toInt();
}
QDebug operator<<(QDebug dbg, const QAudioData &data){
    dbg.nospace() << "QAudioData(" <<
        "album: "<<data.album() <<
        ", artist: "<<data.artist() <<
        ", compilation: "<<data.compilation() <<
        ", composer: "<<data.composer() <<
        ", disc: "<<data.disc() <<
        ", gaplessPlayback: "<<data.gaplessPlayback() <<
        ", genre: "<<data.genre() <<
        ", lyrics: "<<data.lyrics() <<
        ", rating: "<<data.rating() <<
        ", track: "<<data.track() <<
        ", album: "<<data.album()
                  << ")";
    return dbg.maybeSpace();
}
QString QAudioData::artist() const
{
    return m_artist;
}

QString QAudioData::album() const
{
    return m_album;
}

QString QAudioData::genre() const
{
    return m_genre;
}

QString QAudioData::track() const
{
    return m_track;
}

QString QAudioData::disc() const
{
    return m_disc;
}

QString QAudioData::lyrics() const
{
    return m_lyrics;
}

QStringList QAudioData::composer() const
{
    return m_composer;
}

int QAudioData::compilation() const
{
    return m_compilation;
}

int QAudioData::gaplessPlayback() const
{
    return m_gaplessPlayback;
}

int QAudioData::rating() const
{
    return m_rating;
}
