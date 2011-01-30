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
	szLoggerAddress = "inproc://vcore_logger";
	OS_Assert (szLoggerAddress!=NULL);

	// the code below is an attempt to break the 0mq dependency
	// init zmq socket for SUB (sink)
	//m_pZmqContext = zmq_init (1);
	//OS_Assert (m_pZmqContext != NULL);

	//m_pRecvSocket = zmq_socket (m_pZmqContext, ZMQ_SUB);
	//OS_Assert (m_pRecvSocket != NULL);

	//int rc = zmq_bind (m_pRecvSocket, szLoggerAddress);
	//OS_Assert (rc >= 0);

	return 0;
}


