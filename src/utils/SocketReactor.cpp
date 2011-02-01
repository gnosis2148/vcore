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
	fd_set reads, writes, excepts;
	int rc;

	rc = UpdateFdSets (&reads, &writes, &excepts);
	OS_Abort_If ((rc<0));

	return 0;
}

int	SocketReactor::UpdateFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts)
{
	std::list<ReactorEndpoint*>::const_iterator it = m_serverEndpoints.begin ();
	while (it != m_serverEndpoints.end ())
	{
		ReactorEndpoint* pEP = *it;
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
	m_serverEndpoints.push_back (pEndpoint);
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
