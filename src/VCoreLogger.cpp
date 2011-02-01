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
	int rc;
	m_pConfigOptions = pOptions;
	rc = pOptions->GetInt ("server.reactor_queue_size_send", &m_nSendQueueSize);
	rc = pOptions->GetInt ("server.reactor_queue_size_recv", &m_nRecvQueueSize);
	// obtain logger address from config
	const char* szLoggerAddress = pOptions->GetString ("logger.address");
	// temp only
	szLoggerAddress = "tcp://localhost:5555";
	OS_AssertMsg ((szLoggerAddress!=NULL), "logger.address missing from config");

	m_pServerEP = new ReactorEndpoint (szLoggerAddress, ReactorEndpoint::EPTYPE_SERVER);
	OS_AssertMsg ((m_pServerEP!=NULL), "Out of memory");

	rc = this->AddEndpoint (m_pServerEP);
	OS_AssertMsg ((rc >= 0), this->GetLastError ());

	return 0;
}




