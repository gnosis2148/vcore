/*----------------------------------------------------------*

	VCoreLogger.h
	The Logger Thread is a ZMQ SUB socket-based thread

*-----------------------------------------------------------*/
#ifndef _VCORE_LOGGER_H_
#define _VCORE_LOGGER_H_

//-------------------- Include files -------------------------
#include <VCoreConfigOptions.h>
#include <VCoreBuildDefs.h>
#include <SocketReactor.h>

//-------------------- Class Definition ----------------------

class VCoreLogger : public SocketReactor
{
protected:
	VCoreConfigOptions*	m_pConfigOptions;
public:
	VCoreLogger ();
public:
	int		Init	(VCoreConfigOptions* pOptions);
public:
};


#endif // _VCORE_LOGGER_H_