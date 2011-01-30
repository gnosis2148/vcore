/*----------------------------------------------------------*

	ReactorEndpoint.h
	

*-----------------------------------------------------------*/
#ifndef _REACTOR_ENDPOINT_H_
#define _REACTOR_ENDPOINT_H_

//-------------------- Include files -------------------------
#include <OS_Thread.h>
#include <OS_Assert.h>
#include <DataQueue.h>
//-------------------- Constants and Definitions -------------
#ifndef REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH
#define REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH	256
#endif

//-------------------- Class Definition ----------------------
class ReactorEndpoint
{
public:
	typedef enum
	{
		EPTYPE_SERVER,
		EPTYPE_CLIENT,
		EPTYPE_SERVER_CLIENT
	} EndpointType;
protected:
	int				fd;
	EndpointType	m_type;
	DataQueue		m_sendQueue;
	DataQueue		m_recvQueue;
	char			m_szHostname [REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH];
	int				m_nPortNum;
	char			m_szLastError [OS_ERROR_MESSAGE_LENGTH];

public: //------------- config options --------
	int		m_nSendQueueSize;
	int		m_nRecvQueueSize;
	bool	m_bAutoReconnect;

public: //------------- methods ---------------
	ReactorEndpoint	();
public:
	int			Init			(const char* szAddress, EndpointType epType); // alloc the data queue
	const char*	GetLastError	() { return m_szLastError; }
};


#endif // _REACTOR_ENDPOINT_H_