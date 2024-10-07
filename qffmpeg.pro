QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle



SOURCES += \
        main.cpp \
        qaudiodata.cpp \
        qaudiostream.cpp \
        qcodec.cpp \
        qfflog.cpp \
        qffmpeg.cpp \
        qmetadata.cpp \
        qvideostream.cpp



include(ffmpeg/ffmpeg.pri)

HEADERS += \
    qaudiodata.h \
    qaudiostream.h \
    qcodec.h \
    qfflog.h \
    qffmpeg.h \
    qffmpegutility.h \
    qmetadata.h \
    qvideostream.h


