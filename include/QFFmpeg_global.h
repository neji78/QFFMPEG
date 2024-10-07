#ifndef QFFMPEG_GLOBAL_H
#define QFFMPEG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QFFMPEG_LIBRARY)
#  define QFFMPEG_EXPORT Q_DECL_EXPORT
#else
#  define QFFMPEG_EXPORT Q_DECL_IMPORT
#endif

#endif // QFFMPEG_GLOBAL_H
