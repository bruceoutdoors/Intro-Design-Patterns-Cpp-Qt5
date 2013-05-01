#include <QtGlobal>
#ifndef DOBJS_EXPORT
/* This macro is only for building DLLs on windows. */
#ifndef Q_OS_WIN
#define DOBJS_EXPORT
#elif defined(DATAOBJECTS_DLL)
#define DOBJS_EXPORT Q_DECL_EXPORT
#else
#define DOBJS_EXPORT Q_DECL_IMPORT
#endif
#endif
