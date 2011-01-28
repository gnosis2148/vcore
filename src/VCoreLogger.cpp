/*----------------------------------------------------------*

	VCoreLogger.cpp
	The Logger Thread is a ZMQ SUB socket-based thread
	Implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <VCoreLogger.h>


//-------------------- Implementation ------------------------
VCoreLogger::VCoreLogger ()
{
}

int		VCoreLogger::Init	(VCoreConfigOptions* pOptions)
{
	m_pConfigOptions = pOptions;
	return 0;
}


int	VCoreLogger::Run	()
{
	return 0;
}
