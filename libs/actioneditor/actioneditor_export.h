#ifndef ACTIONEDITOR_EXPORT
/** This macro is only for building DLLs on windows.

	The macros below cause ACTIONEDITOR_EXPORT to evaluate to the correct
	thing depending on its use case (being included from an app, or
	building a DLL). This has no effect on non-windows systems.
	*/
	
#include <QtGlobal>
#ifndef Q_WS_WIN
#define ACTIONEDITOR_EXPORT
#elif defined(ACTIONEDITOR_DLL)
#define ACTIONEDITOR_EXPORT Q_DECL_EXPORT
#else
#define ACTIONEDITOR_EXPORT Q_DECL_IMPORT
#endif

#endif        //  #ifndef MYEXPORT_H

