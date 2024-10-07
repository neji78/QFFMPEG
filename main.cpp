#include <QDebug>
#include <qffmpeg.h>
#include <QElapsedTimer>
int main ()
{
    auto path = "D:\\FFMPEG\\transformation\\flip\\qffmpeg\\media\\test.mp4";
    QFFMPEG ffmpeg(path);
    qDebug()<<__LINE__<<__PRETTY_FUNCTION__<<ffmpeg.getAudioStream();
    return 0;
}
