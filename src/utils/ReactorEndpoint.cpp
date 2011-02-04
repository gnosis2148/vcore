/*----------------------------------------------------------*

	ReactorEndpoint.cpp
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <Utils.h>
#include <ReactorEndpoint.h>
#include <SimpleParser.h>

//-------------------- Constants and Definitions -------------

//-------------------- Implementation -------------------------
ReactorEndpoint::ReactorEndpoint	(const char* szAddress, EndpointType epType)
{
	m_nMaxConnections = 32;
	int rc = ParseAddress (szAddress, epType);
	OS_Abort_If ((rc<0));

	m_type = epType;
	m_bAutoReconnect = (m_type == ReactorEndpoint::EPTYPE_CLIENT);
}

ReactorEndpoint::ReactorEndpoint	(OS_Socket* pSock)
{
	m_pSock = pSock;
	m_type = ReactorEndpoint::EPTYPE_SERVER_CLIENT;
	m_bAutoReconnect = false;
	m_pWireProtocol = NULL;
}

void	ReactorEndpoint::SetWireProtocol	(WireProtocol* pProtocol)
{
	m_pWireProtocol = pProtocol;
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
	if (m_type != ReactorEndpoint::EPTYPE_SERVER_CLIENT)
	{
		m_pSock = OS_CreateSocket ();
		rc = m_pSock->Init (m_szHostname, m_nPortNum);
		rc = m_pSock->Create ();
		m_bAutoReconnect = true;
	}
	return 0;
}

int	ReactorEndpoint::HandleError	()
{
	LOG_Error "EP 0x%x HandleError", this LOG_END;
	if (m_type == ReactorEndpoint::EPTYPE_SERVER_CLIENT)
	{
		Shutdown ();
	}
	else
	{
		Reset ();
	}
	return 0;
}

int	ReactorEndpoint::Shutdown		()
{
	m_pSock->Close ();
	Reset ();
	return 0;
}

int	ReactorEndpoint::Reset			() // reset state but keep the socket open
{
	m_recvQueue.Reset ();
	m_sendQueue.Reset ();
	m_pSock->ResetState ();
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

bool	ReactorEndpoint::ShouldReconnect	()
{
	if (m_type == ReactorEndpoint::EPTYPE_CLIENT)
		return m_bAutoReconnect;
	return false;
}

int		ReactorEndpoint::Read			()
{
	int nSpaceAvail = m_recvQueue.GetFreeContByteCount ();
	int rc = m_pSock->Read (m_recvQueue.GetFreeArea (), nSpaceAvail);
	if (rc <= 0)
	{
		HandleError ();
		return -1;
	}

	m_recvQueue.WriteDone (rc);
	LOG_Debug "Read %d bytes from 0x%x rc=%d", rc, this, rc LOG_END;
	return rc;
}

int		ReactorEndpoint::GetRecvData		(char** ppData, int* pnDataCount)
{
	*ppData = m_recvQueue.GetWrittenArea ();
	*pnDataCount = m_recvQueue.GetByteCount ();
	return 0;
}
