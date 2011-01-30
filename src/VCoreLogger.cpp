/*----------------------------------------------------------*

	VCoreLogger.cpp
	The Logger Thread is a ZMQ SUB socket-based thread
	Implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Assert.h>
#include <VCoreLogger.h>

//-------------------- Implementation ------------------------
VCoreLogger::VCoreLogger ()
{
}

int		VCoreLogger::Init	(VCoreConfigOptions* pOptions)
{
	m_pConfigOptions = pOptions;
	// obtain logger address from config
	const char* szLoggerAddress = pOptions->GetString ("logger.address");
	// temp only
	szLoggerAddress = "tcp://localhost:5555";
	OS_AssertMsg ((szLoggerAddress!=NULL), "logger.address missing from config");

	m_pServerEP = new ReactorEndpoint ();
	OS_AssertMsg ((m_pServerEP!=NULL), "Out of memory");

	int rc = m_pServerEP->Init (szLoggerAddress, ReactorEndpoint::EPTYPE_SERVER);
	OS_AssertMsg ((rc >= 0), m_pServerEP->GetLastError ());

	rc = this->AddEndpoint (m_pServerEP);
	OS_AssertMsg ((rc >= 0), this->GetLastError ());
	

	return 0;
}




