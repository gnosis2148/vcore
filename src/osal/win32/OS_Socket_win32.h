/*----------------------------------------------------------*

	OS_SocketWin32.h
	Platform-specific socket implementation
	

*-----------------------------------------------------------*/
#ifndef _OS_SOCKET_WIN32_H_
#define _OS_SOCKET_WIN32_H_

//-------------------- Include files -------------------------

#include <OS_Socket.h>
#include <winsock2.h>
class OS_SocketWin32 : public OS_Socket
{
protected:
	SOCKET	m_sock;
public:
	virtual int		Bind		(int nMaxConnections);
	virtual	int		AddToSet	(void* pSet);
	virtual int		Connect		();
	virtual int		Create		();

};



#endif // _OS_SOCKET_WIN32_H_
