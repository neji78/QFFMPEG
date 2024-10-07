QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle



SOURCES += \
        main.cpp \


include(ffmpeg/ffmpeg.pri)


ANDROID_ABIS = armeabi-v7a


