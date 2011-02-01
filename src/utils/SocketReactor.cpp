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
	}
	return 0;
}

int	SocketReactor::UpdateFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
	FD_ZERO (reads);
	FD_ZERO (writes);
	FD_ZERO (excepts);

	int rc;
	std::list<ReactorEndpoint*>::const_iterator it = m_endpoints.begin ();
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
