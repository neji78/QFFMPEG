#include "qffmpeg.h"
#include <qfflog.h>
extern "C"{
#include <libavformat/avformat.h>
#include "libavutil/attributes.h"
#include <libavutil/dict.h>
#include <libavutil/log.h>
}

QFFMPEG::QFFMPEG(const QString &filePath):
    m_filePath(filePath)
{
    QFFLog::registerLog();
    getMediaData(filePath);
}

QString QFFMPEG::filePath() const
{
    return m_filePath;
}

void QFFMPEG::setFilePath(const QString &filePath)
{
    if(m_filePath == filePath)
        return;
    m_filePath = filePath;
}

QMetaData QFFMPEG::metaData() const
{
    return m_metaData;
}

void QFFMPEG::getMediaData(const QString &filePath)
{
    int ret = 0;
    AVFormatContext *fmt_ctx = NULL;
    const AVDictionaryEntry *tag = NULL;
    if ((ret = avformat_open_input(&fmt_ctx, filePath.toStdString().c_str(), NULL, NULL))){
        QFFLog::LogError(ret);
        return;
    }

    if ((ret = avformat_find_stream_info(fmt_ctx, NULL)) < 0) {
        QFFLog::LogError(ret);
        return;
    }

    QVariantMap data;
    while ((tag = av_dict_iterate(fmt_ctx->metadata, tag)))
        data.insert(tag->key,tag->value);
    m_metaData = QMetaData(data);

    for (unsigned int i = 0; i < fmt_ctx->nb_streams; ++i) {
        AVStream* stream = fmt_ctx->streams[i];
        if (stream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            m_videoStream = QVideoStream(*stream);
        } else if (stream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            m_audioStream = QAudioStream(*stream);
        }
    }
    avformat_close_input(&fmt_ctx);
}

void QFFMPEG::setMetaData(QMetaData metaData)
{
    if (m_metaData == metaData)
        return;

    m_metaData = metaData;
}

QVideoStream QFFMPEG::getVideoStream() const
{
    return m_videoStream;
}

QAudioStream QFFMPEG::getAudioStream() const
{
    return m_audioStream;
}
