#include "qfflog.h"
#include <QDebug>

//#include "qffmpegutility.h"
extern "C"{
#include <libavutil/log.h>
#include <libavutil/error.h>
}
// in one source file
Q_LOGGING_CATEGORY(ffmpeg, "ffmpeg")
void QFFLog::registerLog()
{
    av_log_set_level(AV_LOG_DEBUG);
//    av_log_set_callback(&QFFLog::callbackFunction);

}

void QFFLog::callbackFunction(void *ptr, int lowlevel, const char *msg, va_list arguments)
{
    char buffer[256];
    vsnprintf (buffer,256,msg, arguments);
    auto enumData = QMetaEnum::fromType<QFFLog::Level>();
    qCDebug(ffmpeg)<<enumData.valueToKey(QFFLog::convertLowToHigh(lowlevel))<<buffer;
}

void QFFLog::setLevel(int highlevel)
{
    av_log_set_level(convertHighToLow(highlevel));
}

int QFFLog::convertLowToHigh(int lowlevel)
{
    int highlevel;
    switch(lowlevel){
    case AV_LOG_INFO:
        highlevel = QFFLog::Info ;
        break;
    case AV_LOG_DEBUG:
        highlevel = QFFLog::Debug;
        break;
    case AV_LOG_ERROR:
        highlevel = QFFLog::Error;
        break;
    case AV_LOG_FATAL:
        highlevel = QFFLog::Fatal;
        break;
    case AV_LOG_PANIC:
        highlevel = QFFLog::Panic;
        break;
    case AV_LOG_QUIET:
        highlevel = QFFLog::Quiet ;
        break;
    }
    return highlevel;
}

int QFFLog::convertHighToLow(int highlevel)
{
    int lowlevel;
    auto level = static_cast<QFFLog::Level>(highlevel);
    switch(level){
    case QFFLog::Info:
        lowlevel = AV_LOG_INFO;
        break;
    case QFFLog::Debug:
        lowlevel = AV_LOG_DEBUG;
        break;
    case QFFLog::Error:
        lowlevel = AV_LOG_ERROR;
        break;
    case QFFLog::Fatal:
        lowlevel = AV_LOG_FATAL;
        break;
    case QFFLog::Panic:
        lowlevel = AV_LOG_PANIC;
        break;
    case QFFLog::Quiet:
        lowlevel = AV_LOG_QUIET;
        break;
    }
    return lowlevel;
}

void QFFLog::LogError(int code)
{
    char buf[256];
    av_strerror(code,buf,256);
    QFFLog::callbackFunction(NULL,AV_LOG_ERROR,buf,{});
//    qDebug()<<__LINE__<<__PRETTY_FUNCTION__<<buf;
}
