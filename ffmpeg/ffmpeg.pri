
win32 {

    ## Windows common build here
    !contains(QT_ARCH, x86_64) {
#        message("x86 build")

        ## Windows x86 (32bit) specific build here

    } else {
#        message("x86_64 build")
        INCLUDEPATH += $$PWD/win86_64/include

         LIBS += -L$$PWD/win86_64/lib/ -lavformat -lavcodec -lavfilter -lavutil -lswresample -lswscale -lpostproc -lz
         LIBS += -L$$PWD/win86_64/lib/ -lbcrypt
#        LIBS += -L$$PWD/win86_64/lib/ -lavutil -lavformat -lavfilter -lavcodec -lpostproc -lswresample -lswscale
        ## Windows x64 (64bit) specific build here

    }
}
