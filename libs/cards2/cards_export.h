#ifndef CARDS_EXPORT

#include <QtGlobal>
#ifndef Q_OS_WIN
#define CARDS_EXPORT
#elif defined(CARDS_DLL)
#define CARDS_EXPORT Q_DECL_EXPORT
#else
#define CARDS_EXPORT Q_DECL_IMPORT
#endif

#endif // CARDS_EXPORT_H
