SOURCES += \
        qaudiodata.cpp \
        qaudiostream.cpp \
        qcodec.cpp \
        qfflog.cpp \
        qffmpeg.cpp \
        qmetadata.cpp \
        qvideostream.cpp


HEADERS += \
    include/qaudiodata.h \
    include/qaudiostream.h \
    include/qcodec.h \
    include/qfflog.h \
    include/qffmpeg.h \
    include/qffmpegutility.h \
    include/qmetadata.h \
    include/qvideostream.h
INCLUDEPATH += $$PWD/3rdParty/include
INCLUDEPATH += $$PWD/include

win32 {

    ## Windows common build here
    !contains(QT_ARCH, x86_64) {

        LIBS += -L$$PWD/3rdParty/lib/windows/x86/static/ -lavformat -lavcodec -lavutil -lbcrypt -lz

    } else {


    }
}
android{

contains(QT_ARCH, armeabi-v7a) {
    LIBS += -L$$PWD/3rdParty/lib/android/armeabi-v7a/ \
            -lavformat -lavcodec -lavutil -lz
} else: contains(QT_ARCH, arm64-v8a) {
    LIBS += -L$$PWD/3rdParty/lib/android/aarch64-linux-android/ \
            -lavformat -lavcodec -lavutil -lz
}

}
