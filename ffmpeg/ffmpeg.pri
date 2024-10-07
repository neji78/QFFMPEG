SOURCES += \
        qaudiodata.cpp \
        qaudiostream.cpp \
        qcodec.cpp \
        qfflog.cpp \
        qffmpeg.cpp \
        qmetadata.cpp \
        qvideostream.cpp


HEADERS += \
    qaudiodata.h \
    qaudiostream.h \
    qcodec.h \
    qfflog.h \
    qffmpeg.h \
    qffmpegutility.h \
    qmetadata.h \
    qvideostream.h
INCLUDEPATH += $$PWD/3rdParty/include

win32 {

    ## Windows common build here
    !contains(QT_ARCH, x86_64) {

        LIBS += -L$$PWD/3rdParty/lib/windows/x86/static/ -lavformat -lavcodec -lavutil -lbcrypt -lz

    } else {


    }
}
android{
    LIBS += -L$$PWD/3rdParty/lib/android/aarch64-linux-android/ -lavformat -lavcodec -lavutil -lbcrypt -lz
}
