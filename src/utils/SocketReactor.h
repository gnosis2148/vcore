/*----------------------------------------------------------*

	SocketReactor.h
	

*-----------------------------------------------------------*/
#ifndef _SOCKET_REACTOR_H_
#define _SOCKET_REACTOR_H_

//-------------------- Include files -------------------------
#include <list>
//using namespace std;
#include <OS_Thread.h>
#include <OS_Platform.h>
#include <ReactorEndpoint.h>


//-------------------- Class Definition ----------------------
class SocketReactor : public OS_Thread
{
protected:
	char								m_szLastError [OS_ERROR_MESSAGE_LENGTH];
	//std::list<ReactorEndpoint*>			m_serverEndpoints;
	std::list<ReactorEndpoint*>			m_endpoints;
	//---------- config options ------------
	int	m_nSendQueueSize, m_nRecvQueueSize;
public:
	SocketReactor	();
	~SocketReactor	();
public:
	int			AddEndpoint		(ReactorEndpoint* pEndpoint);
	int			Stop			();
	const char*	GetLastError	() { return m_szLastError; }
public:
	virtual	int	Run	();

protected:
	int	UpdateFdSets	(fd_set* reads, fd_set* writes, fd_set* excepts);

//----------- Overridables -----------------------
protected: 
	int	OnConnect	(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP);
	int	OnReceive	(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP);
	int	OnDisconnect(ReactorEndpoint* pOriginatorEP, ReactorEndpoint* pNewEP);
};



#endif // _SOCKET_REACTOR_H_