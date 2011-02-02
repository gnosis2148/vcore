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
	bool	m_bIsValid; // for server socket - if bound, for client socket - if connected

protected:
	OS_Socket	();
public:
	virtual	int			Init		(const char* szHostAddr, int nPortNum);
	virtual	int			Bind		(int nMaxConnections) = 0;
	virtual	int			AddToSet	(void* pSet) = 0;
	virtual bool		IsInSet		(void* pSet) = 0;
	virtual int			Connect		() = 0;
	virtual int			Create		() = 0;
	virtual int			Close		() = 0;
	virtual OS_Socket*	Accept		() = 0;
	virtual int			Read		(void* pDestBuffer, int nMaxBytesToRead) = 0;
	
public:
	bool	IsValid			()	{ return m_bIsValid; }
	void	ResetState		();
public:
	~OS_Socket	();
protected:

};


#endif // _OS_SOCKET_H_