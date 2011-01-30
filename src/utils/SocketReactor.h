/*----------------------------------------------------------*

	SocketReactor.h
	

*-----------------------------------------------------------*/
#ifndef _SOCKET_REACTOR_H_
#define _SOCKET_REACTOR_H_

//-------------------- Include files -------------------------
#include <OS_Thread.h>
#include <ReactorEndpoint.h>
//-------------------- Class Definition ----------------------
class SocketReactor : public OS_Thread
{
protected:
	char			m_szLastError [OS_ERROR_MESSAGE_LENGTH];

public:
	int			AddEndpoint		(ReactorEndpoint* pEndpoint);
	int			Stop			();
	const char*	GetLastError	() { return m_szLastError; }
public:
	virtual	int	Run	();
};



#endif // _SOCKET_REACTOR_H_