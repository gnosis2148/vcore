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
public:
	int		Stop	();
public:
	virtual	int	Run	();
};



#endif // _SOCKET_REACTOR_H_