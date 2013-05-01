#ifndef MOBMETAEXPORT

#include <QtGlobal>
/* This macro is only for building DLLs on windows. */

#ifndef Q_OS_WIN
#define MOBMETAEXPORT
#elif defined(MOBILITYMETADATA_DLL)
#define MOBMETAEXPORT Q_DECL_EXPORT
#else
#define MOBMETAEXPORT Q_DECL_IMPORT
#endif


#endif        //  #ifndef MOBMETAEXPORT


