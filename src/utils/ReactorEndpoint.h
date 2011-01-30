/*----------------------------------------------------------*

	ReactorEndpoint.h
	

*-----------------------------------------------------------*/
#ifndef _REACTOR_ENDPOINT_H_
#define _REACTOR_ENDPOINT_H_

//-------------------- Include files -------------------------
#include <OS_Thread.h>
#include <DataQueue.h>
//-------------------- Class Definition ----------------------
class ReactorEndpoint
{
public:
	typedef enum
	{
		EPTYPE_LISTENER,
		EPTYPE_CLIENT
	} EndpointType;
protected:
	int				fd;
	EndpointType	m_type;
	DataQueue		m_sendQueue;
	DataQueue		m_recvQueue;
public:
	ReactorEndpoint	();
public:

};


#endif // _REACTOR_ENDPOINT_H_