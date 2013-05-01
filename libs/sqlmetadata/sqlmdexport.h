#ifndef SQLMDEXPORT_H
#define SQLMDEXPORT_H
#include <QtGlobal>
#ifndef Q_OS_WIN
#define SQLMDEXPORT
#elif defined(SQLMETADATA_DLL)
#define SQLMDEXPORT Q_DECL_EXPORT
#else
#define SQLMDEXPORT Q_DECL_IMPORT
#endif

#endif // SQLMDEXPORT_H


