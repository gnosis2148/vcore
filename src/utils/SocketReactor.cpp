/*----------------------------------------------------------*

	SocketReactor.cpp
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Assert.h>
#include <SocketReactor.h>
#include <Utils.h>

//-------------------- Implementation ------------------------
SocketReactor::SocketReactor	()
{
	m_nSendQueueSize = 32768;
	m_nRecvQueueSize = 32768;

}

SocketReactor::~SocketReactor	()
{
}


int	SocketReactor::Run	()
{
	int nSockCount;
	while (true)
	{
		fd_set reads, writes, excepts;
		int rc;

		rc = UpdateFdSets (&reads, &writes, &excepts);
		OS_Abort_If ((rc<0));
		
		LOG_Debug "Before select total sockets %d", m_endpoints.size() LOG_END;
		nSockCount = select (0, &reads, &writes, &excepts, NULL);
		LOG_Debug "Out of select %d", nSockCount LOG_END;

		if (nSockCount < 0)
		{
			LOG_Error "select() error %d", OS_GetLastSocketError () LOG_END;
		}
		else
		{
			rc = ProcessFdSets (&reads, &writes, &excepts);
		}
	}
	return 0;
}

int	SocketReactor::ProcessFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
	LOG_Debug "enter %s", __FUNCTION__ LOG_END;
	std::list<ReactorEndpoint*>::iterator it = m_endpoints.begin ();
	while (it != m_endpoints.end ())
	{
		ReactorEndpoint* pEP = *it;
		if (pEP->GetSocket()->IsInSet (excepts))
		{
			HandleError (it, pEP);
		}
		else // reads or writes
		{
			if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER)
			{
				if (pEP->GetSocket()->IsInSet (reads)) // new connection
				{
					HandleNewConnection (pEP);
				}

			}
			else
			{
				if (pEP->GetSocket()->IsInSet (reads))
					HandleRead (pEP);
				if (pEP->GetSocket()->IsInSet (writes))
					HandleWrite (pEP);
			}
		} // else: reads or writes
		*it++;
	}
	LOG_Debug "exit %s", __FUNCTION__ LOG_END;
	return 0;
}



int	SocketReactor::UpdateFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
	LOG_Debug "enter %s", __FUNCTION__ LOG_END;
	FD_ZERO (reads);
	FD_ZERO (writes);
	FD_ZERO (excepts);

	int rc;
	std::list<ReactorEndpoint*>::iterator it = m_endpoints.begin ();
	while (it != m_endpoints.end ())
	{
		ReactorEndpoint* pEP = *it;
		if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER)
		{
			if (pEP->GetSocket()->IsValid ())
			{
				pEP->GetSocket ()->AddToSet (reads);
				pEP->GetSocket ()->AddToSet (excepts);
			}
			else // socket invalid
			{
				rc = pEP->GetSocket()->Bind (pEP->m_nMaxConnections);
			}
		}
		else
		{
			if (pEP->GetSocket ()->IsValid ())
			{
				pEP->GetSocket ()->AddToSet (reads);
				if (pEP->m_sendQueue.GetByteCount () > 0)
					pEP->GetSocket ()->AddToSet (writes);
				pEP->GetSocket ()->AddToSet (excepts);
			}
			else // invalid
			{
				if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER_CLIENT)
				{
					HandleError (it, pEP);
				}
				else if (pEP->ShouldReconnect ())
				{
					pEP->GetSocket()->Connect ();
				}
			}
		}

		*it++;
	}
	LOG_Debug "exit %s", __FUNCTION__ LOG_END;
	return 0;
}


int	SocketReactor::Stop	()
{
	return 0;
}


int	SocketReactor::AddEndpoint		(ReactorEndpoint* pEndpoint)
{
	pEndpoint->m_nRecvQueueSize = m_nRecvQueueSize;
	pEndpoint->m_nSendQueueSize = m_nSendQueueSize;
	pEndpoint->Init ();
	m_endpoints.push_back (pEndpoint);

	return 0;
}

int	SocketReactor::HandleError			(std::list<ReactorEndpoint*>::iterator& it, ReactorEndpoint* pEP)
{
	LOG_Debug "HandleError 0x%x", pEP LOG_END;
	if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER_CLIENT)
	{
		pEP->Shutdown ();
		it = m_endpoints.erase (it);
		delete pEP;
	}
	else if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER)
	{
		pEP->Reset ();
	}
	else if (pEP->GetType () == ReactorEndpoint::EPTYPE_CLIENT)
	{
		pEP->Reset ();
	}

	return 0;
}

int	SocketReactor::HandleNewConnection	(ReactorEndpoint* pEP)
{
	OS_Socket* pSock = pEP->GetSocket()->Accept();
	ReactorEndpoint* pConn = new ReactorEndpoint (pSock);
	LOG_Debug "HandleNewConnection (0x%x) new is 0x%x", pEP, pConn LOG_END;
	OS_Abort_If ((pConn==NULL));
	AddEndpoint (pConn);
	return 0;
}

int	SocketReactor::HandleRead			(ReactorEndpoint* pEP)
{
	LOG_Debug "HandleRead 0x%x", pEP LOG_END;
	int rc = pEP->Read ();
	if (rc <= 0)
	{
		if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER_CLIENT)
		{
			LOG_Debug "Invalidate EP 0x%x", pEP LOG_END;
			pEP->Shutdown ();
			//m_endpoints.remove (pEP);
		}
	}
	else // valid data
	{
		int nDataCount;
		char* pRecvData;
		pEP->GetRecvData (&pRecvData, &nDataCount);
		
		bool bMessageComplete = IsMessageComplete (pEP, pRecvData, &nDataCount);
		
	}
	return 0;
}

int	SocketReactor::HandleWrite			(ReactorEndpoint* pEP)
{
	return 0;
}


int	SocketReactor::OnConnect	(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP)
{
	return 0;
}

bool	SocketReactor::IsMessageComplete	(ReactorEndpoint* pOrigEP, char* pData, int* pnDataCountBytes)
{
	return false;
}

int	SocketReactor::OnReceive			(ReactorEndpoint* pOrigEP, char* pData, int nDataCountBytes, bool bMessageComplete)
{
	return 0;
}

int	SocketReactor::OnDisconnect(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP)
{
	return 0;
}
