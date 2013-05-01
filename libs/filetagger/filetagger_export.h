#ifndef FILETAGGER_EXPORT

#include <QtGlobal>
/* This macro is only for building DLLs on windows. */

#ifndef Q_OS_WIN
#define FILETAGGER_EXPORT
#elif defined(FILETAGGER_DLL)
#define FILETAGGER_EXPORT Q_DECL_EXPORT
#else
#define FILETAGGER_EXPORT Q_DECL_IMPORT
#endif
#endif
