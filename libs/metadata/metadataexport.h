#ifndef METADATAEXPORT

#include <QtGlobal>
/* This macro is only for building DLLs on windows. */

#ifndef Q_OS_WIN
#define METADATAEXPORT
#elif defined(METADATA_DLL)
#define METADATAEXPORT Q_DECL_EXPORT
#else
#define METADATAEXPORT Q_DECL_IMPORT
#endif


#endif        //  #ifndef METADATAEXPORT_H


