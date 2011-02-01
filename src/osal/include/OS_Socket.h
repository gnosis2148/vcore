/*----------------------------------------------------------*

	OS_Socket.h
	Platform-agnostic socket abstraction - INTERFACE
	

*-----------------------------------------------------------*/
#ifndef _OS_SOCKET_H_
#define _OS_SOCKET_H_

//-------------------- Include files -------------------------
#define SOCKET_MAX_HOSTNAME_LEN	256

class	OS_Socket
{
protected:
	char	m_szHostName	[SOCKET_MAX_HOSTNAME_LEN];
	int		m_nDestPortNum;
protected:
	OS_Socket	();
public:
	virtual	int		Init	(const char* szHostAddr, int nPortNum);
	virtual	int		Bind	() = 0;
public:
	~OS_Socket	();


};


#endif // _OS_SOCKET_H_