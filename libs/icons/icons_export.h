#ifndef ICONS_EXPORT

#include <QtGlobal>
/* This macro is only for building DLLs on windows. */

#ifndef Q_OS_WIN
#define ICONS_EXPORT
#elif defined(ICONS_DLL)
#define ICONS_EXPORT Q_DECL_EXPORT
#else
#define ICONS_EXPORT Q_DECL_IMPORT
#endif

#endif        //  #ifndef ICONS_EXPORTICONS_EXPORT

