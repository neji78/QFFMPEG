QT -= gui

TEMPLATE = lib
CONFIG += staticlib

CONFIG += c++17

include(config.pri)
DESTDIR = $$PWD/lib
# Install headers to the include directory
target.path = $$DESTDIR
# Set the output directory for the compiled library files (optional)

# Include directory for the headers (optional, but useful for clarity)
INCLUDEPATH += $$PWD/include
INSTALLS += target



