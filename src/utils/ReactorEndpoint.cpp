/*----------------------------------------------------------*

	ReactorEndpoint.cpp
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <ReactorEndpoint.h>
#include <SimpleParser.h>
//-------------------- Constants and Definitions -------------

//-------------------- Implementation -------------------------
ReactorEndpoint::ReactorEndpoint	(const char* szAddress, EndpointType epType)
{
	int rc = ParseAddress (szAddress, epType);
	OS_Abort_If ((rc<0));

	m_type = epType;
	m_bAutoReconnect = (m_type == ReactorEndpoint::EPTYPE_CLIENT);
}

bool	ReactorEndpoint::NeedsRead		()
{
	if (this->m_type == ReactorEndpoint::EPTYPE_SERVER)
		return true;
	return false;
}

bool	ReactorEndpoint::NeedsWrite		()
{
	return false;
}


int	ReactorEndpoint::Init		() // alloc the data queue
{
	int rc;
	rc = m_sendQueue.AllocateMemory (m_nSendQueueSize);
	OS_Abort_If ((rc<0));

	rc = m_recvQueue.AllocateMemory (m_nRecvQueueSize);
	OS_Abort_If ((rc<0));

	// prepare the socket
	m_pSock = OS_CreateSocket ();
	rc = m_pSock->Init (m_szHostname, m_nPortNum);

	return 0;
}

int	ReactorEndpoint::ParseAddress		(const char* szAddress, EndpointType epType)
{
	char szTransport [REACTOR_ENDPOINT_MAX_TRANSPORT_NAME_LENGTH];
	char szPortNum [REACTOR_ENDPOINT_MAX_PORT_NUM_LENGTH];

	int nCurPos = 0;
	int rc = ParseToken (szAddress, &nCurPos, '/', szTransport, REACTOR_ENDPOINT_MAX_TRANSPORT_NAME_LENGTH);
	OS_AssertMsg ((rc>=0), "No transport specified");
	OS_AssertMsg ((szAddress[nCurPos+1]=='/'), "Incorrect address format - use <transport>://<address>:<port>");

	nCurPos += 2;
	rc = ParseToken (szAddress, &nCurPos, ':', m_szHostname, REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH);
	OS_AssertMsg ((rc>=0), "No port number specified");

	nCurPos ++;
	rc = ParseToken (szAddress, &nCurPos, ':', szPortNum, REACTOR_ENDPOINT_MAX_PORT_NUM_LENGTH);
	m_nPortNum = atoi (szPortNum);
	OS_AssertMsg ((m_nPortNum > 0), "Illegal port number");

	return 0;
}

