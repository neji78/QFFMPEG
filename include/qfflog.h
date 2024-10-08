#ifndef QFFLOG_H
#define QFFLOG_H
extern "C"{
#include <libavutil/log.h>
}
#include <QFFmpeg_global.h>
#include <QLoggingCategory>
#include <QMetaEnum>
// in a header
Q_DECLARE_LOGGING_CATEGORY(ffmpeg)
class QFFLog: public QObject
{
    Q_OBJECT
public:
    static void registerLog();
    static void callbackFunction(void* ptr, int, const char* msg, va_list arguments);
    static void setLevel(int highlevel);
    static int convertLowToHigh(int lowlevel);
    static int convertHighToLow(int highlevel);
    static void LogError(int code);
    QFFLog(const QFFLog& obj) = delete;
    QFFLog operator =(const QFFLog& obj) = delete;
    enum Level{
        Info,
        Verbose,
        Debug,
        Error,
        Panic,
        Fatal,
        Quiet
    };
    Q_ENUM(Level)

private:
    QFFLog(){}
    ~QFFLog(){}
};

#endif // QFFLOG_H
