QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
include($$PWD/ffmpeg/ffmpeg.pri)
SOURCES += \
        main.cpp

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target


#-lws2_32 -lbcrypt -latomic -liconv
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ffmpeg/
#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ffmpeg/
#-lavcodec  -lavfilter -lavutil
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ffmpeg/ \
#-lavcodec -lavformat -lavfilter -lavutil


#DEPENDPATH += $$PWD/ffmpeg/include


#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += \
#$$PWD/ffmpeg/libavutil.a \
#$$PWD/ffmpeg/libavformat.a \
#$$PWD/ffmpeg/libavcodec.a \
#$$PWD/ffmpeg/libavfilter.a \
#$$PWD/ffmpeg/libswresample.a \
#$$PWD/ffmpeg/libswscale.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ffmpeg/libavcodec.a
#$$PWD/ffmpeg/libavfilter.a \
#$$PWD/ffmpeg/libavformat.a \
#$$PWD/ffmpeg/libavutil.a \
#$$PWD/ffmpeg/libswresample.a \
#$$PWD/ffmpeg/libswscale.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/ffmpeg/avcodec.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/ffmpeg/avcodecd.lib

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/ffmpeg/ -lavfilter
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/ffmpeg/ -lavfilterd

#DISTFILES += \
#    ffmpegConfig.pri


