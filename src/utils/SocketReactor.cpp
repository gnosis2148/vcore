/*----------------------------------------------------------*

	SocketReactor.cpp
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Assert.h>
#include <SocketReactor.h>
#include <OS_Platform.h>

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
		
		nSockCount = select (0, &reads, &writes, &excepts, NULL);

		rc = ProcessFdSets (&reads, &writes, &excepts);
	}
	return 0;
}

int	SocketReactor::ProcessFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
	int rc;
	std::list<ReactorEndpoint*>::const_iterator it = m_endpoints.begin ();
	while (it != m_endpoints.end ())
	{
		ReactorEndpoint* pEP = *it;
		if (pEP->GetSocket()->IsInSet (excepts))
		{
			HandleError (pEP);
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
	return 0;
}



int	SocketReactor::UpdateFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
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
				if (pEP->ShouldReconnect ())
				{
					pEP->GetSocket()->Connect ();
				}
			}
		}

		*it++;
	}
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

int	SocketReactor::HandleError			(ReactorEndpoint* pEP)
{
	if (pEP->GetType () == ReactorEndpoint::EPTYPE_SERVER_CLIENT)
	{
		pEP->Shutdown ();
		m_endpoints.remove (pEP);
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
	OS_Abort_If ((pConn==NULL));
	AddEndpoint (pConn);
	return 0;
}

int	SocketReactor::HandleRead			(ReactorEndpoint* pEP)
{
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

int	SocketReactor::OnReceive	(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP)
{
	return 0;
}

int	SocketReactor::OnDisconnect(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP)
{
	return 0;
}
