#include <QDebug>
#include <qffmpeg.h>
#include <QElapsedTimer>
int main ()
{
    QElapsedTimer es;
    es.start();
    QFFMPEG ffmpeg("D:\\FFMPEG\\transformation\\flip\\flipVideo\\media\\avitest.avi");
    return 0;
}
