QT -= gui

TEMPLATE = lib
android{
targetOS = android
CONFIG += shared
}
win32{
targetOS = win32
CONFIG += staticlib
}
CONFIG += c++17

include(config.pri)



DESTDIR = $$PWD/lib/$$targetOS/$$QT_ARCH


# Install headers to the include directory
target.path = $$DESTDIR
# Set the output directory for the compiled library files (optional)

# Include directory for the headers (optional, but useful for clarity)
INCLUDEPATH += $$PWD/include
INSTALLS += target



