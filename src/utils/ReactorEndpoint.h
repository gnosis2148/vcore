/*----------------------------------------------------------*

	ReactorEndpoint.h
	

*-----------------------------------------------------------*/
#ifndef _REACTOR_ENDPOINT_H_
#define _REACTOR_ENDPOINT_H_

//-------------------- Include files -------------------------
#include <OS_Thread.h>
#include <OS_Platform.h>
#include <OS_Assert.h>
#include <DataQueue.h>
#include <WireProtocol.h>
//-------------------- Constants and Definitions -------------
#define REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH	256
#define REACTOR_ENDPOINT_MAX_TRANSPORT_NAME_LENGTH 8
#define REACTOR_ENDPOINT_MAX_PORT_NUM_LENGTH 8
//-------------------- Class Definition ----------------------
class ReactorEndpoint
{
	friend class SocketReactor;
public:
	typedef enum
	{
		EPTYPE_SERVER,
		EPTYPE_CLIENT,
		EPTYPE_SERVER_CLIENT
	} EndpointType;
protected:
	OS_Socket*		m_pSock;
	EndpointType	m_type;
	DataQueue		m_sendQueue;
	DataQueue		m_recvQueue;
	char			m_szHostname [REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH];

	int				m_nPortNum;
	char			m_szLastError [OS_ERROR_MESSAGE_LENGTH];
	WireProtocol*	m_pWireProtocol;
protected: //------------- config options --------
	int		m_nSendQueueSize;
	int		m_nRecvQueueSize;
	bool	m_bAutoReconnect;
	int		m_nMaxConnections; // for server EP's only
public: //------------- methods ---------------
	ReactorEndpoint	(const char* szAddress, EndpointType epType);
	ReactorEndpoint	(OS_Socket* pSock);
public:
	int				Init			(); // alloc the data queue
	int				Shutdown		(); // close the socket
	int				Reset			(); // reset state but keep the socket open
	int				HandleError		();
	const char*		GetLastError	() { return m_szLastError; }
	bool			NeedsRead		();
	bool			NeedsWrite		();
	EndpointType	GetType			() { return m_type; }
	OS_Socket*		GetSocket		() { return m_pSock; }
	bool			ShouldReconnect	();
	int				Read			();
	int				GetRecvData		(char** ppData, int* pnDataCount);
	void			SetWireProtocol	(WireProtocol* pProtocol);
protected:
	int		ParseAddress		(const char* szAddress, EndpointType epType);
};


#endif // _REACTOR_ENDPOINT_H_