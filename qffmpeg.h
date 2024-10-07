#ifndef QFFMPEG_H
#define QFFMPEG_H

#include <QObject>
#include "qmetadata.h"
#include <qaudiostream.h>
#include <qvideostream.h>
extern "C"{
#include <libavutil/dict.h>
}
class QFFMPEG : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QMetaData metaData READ metaData WRITE setMetaData NOTIFY metaDataChanged)
public:
    QFFMPEG(const QString& filePath, QObject* parent = nullptr);
    QString filePath() const;
    void setFilePath(const QString &filePath);
    QMetaData metaData() const;
    void getMediaData(const QString& filePath);
    QAudioStream getAudioStream() const;
    QVideoStream getVideoStream() const;

public slots:
    void setMetaData(QMetaData metaData);

signals:
    void metaDataChanged(QMetaData metaData);

private:
    QString m_filePath;
    QMetaData m_metaData;
    QAudioStream m_audioStream;
    QVideoStream m_videoStream;

};

#endif // QFFMPEG_H
