#ifndef QAUDIODATA_H
#define QAUDIODATA_H

#include <QVariantMap>
#include <QDebug>

class QAudioData
{
public:
    QAudioData(){}
    QAudioData(const QVariantMap& data);

    QString artist() const;

    QString album() const;

    QString genre() const;

    QString track() const;

    QString disc() const;

    QString lyrics() const;

    QStringList composer() const;

    int compilation() const;

    int gaplessPlayback() const;

    int rating() const;
    friend QDebug operator<<(QDebug dbg, const QAudioData &data);


private:
    QString m_artist;
    QString m_album;
    QString m_genre;
    QString m_track;
    QString m_disc;
    QString m_lyrics;
    QStringList m_composer;
    int m_compilation;
    int m_gaplessPlayback;
    int m_rating;


};

#endif // QAUDIODATA_H
