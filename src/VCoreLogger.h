/*----------------------------------------------------------*

	VCoreLogger.h
	The Logger Thread is a ZMQ SUB socket-based thread

*-----------------------------------------------------------*/
#ifndef _VCORE_LOGGER_H_
#define _VCORE_LOGGER_H_

//-------------------- Include files -------------------------
#include <VCoreConfigOptions.h>
#include <VCoreBuildDefs.h>
#include <OS_Thread.h>


//-------------------- Class Definition ----------------------

class VCoreLogger : public OS_Thread
{
protected:
	VCoreConfigOptions*	m_pConfigOptions;
public:
	VCoreLogger ();
public:
	int		Init	(VCoreConfigOptions* pOptions);
public:
	virtual int	Run	();
};


#endif // _VCORE_LOGGER_H_