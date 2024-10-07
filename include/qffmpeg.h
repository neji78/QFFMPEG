#ifndef QFFMPEG_H
#define QFFMPEG_H

#include "qmetadata.h"
#include <qaudiostream.h>
#include <qvideostream.h>
extern "C"{
#include <libavutil/dict.h>
}
class QFFMPEG
{
public:
    QFFMPEG(const QString& filePath);
    QString filePath() const;
    void setFilePath(const QString &filePath);
    QMetaData metaData() const;
    void getMediaData(const QString& filePath);
    QAudioStream getAudioStream() const;
    QVideoStream getVideoStream() const;
private:
    void setMetaData(QMetaData metaData);


private:
    QString m_filePath;
    QMetaData m_metaData;
    QAudioStream m_audioStream;
    QVideoStream m_videoStream;

};

#endif // QFFMPEG_H
