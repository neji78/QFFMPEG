
win32 {

    ## Windows common build here
    !contains(QT_ARCH, x86_64) {
#    INCLUDEPATH += $$PWD/x264/include
#    LIBS += -L$$PWD/x264/lib/ -lx264
INCLUDEPATH += $$PWD/win32/static/include
LIBS += -L$$PWD/win32/static/lib/ -lavformat -lavcodec -lavutil -lbcrypt -lz
#    INCLUDEPATH += $$PWD/win32/dynamic/include
#    LIBS += -L$$PWD/win32/dynamic/lib/ -lavformat -lavutil
#    LIBS += -L$$PWD/win86/lib/ -lavformat -lavutil -lavcodec -lavfilter -lx264



    } else {


    }
}
