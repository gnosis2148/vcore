/*----------------------------------------------------------*

	OS_SocketWin32.cpp
	Platform-specific socket implementation
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <win32/OS_Socket_win32.h>

int	OS_SocketWin32::Create		()
{
	m_sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_sock < 0)
		return -1;
	return 0;
}



int	OS_SocketWin32::Bind	(int nMaxConnections)
{
	m_bIsValid = false;
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;	// Since this socket is listening for connections,
							// any local address will do
	serverInfo.sin_port = htons(m_nDestPortNum);		// Convert integer 8888 to network-byte order
							// and insert into the port field

	// Bind the socket to our local server address
	int nret = bind(m_sock, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		return -1;
	}
	
	int val = 1;
	nret = setsockopt (m_sock, SOL_SOCKET, SO_REUSEADDR, (const char*)&val, sizeof(val));
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		return -1;
	}

	nret = listen (m_sock, nMaxConnections);
	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		return -1;
	}
	m_bIsValid = true;
	return 0;
}


int		OS_SocketWin32::AddToSet	(void* pSet)
{
	FD_SET* pset = (FD_SET*)pSet;
	FD_SET (m_sock, pSet);
	return 0;
}

bool	OS_SocketWin32::IsInSet		(void* pSet)
{
	FD_SET* pset = (FD_SET*)pSet;
	return FD_ISSET (m_sock, pset)?true:false;
}


int		OS_SocketWin32::Connect		()
{
	m_bIsValid = false;
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = inet_addr(m_szHostName);	// Since this socket is listening for connections,
							// any local address will do
	serverInfo.sin_port = htons(m_nDestPortNum);		// Convert integer 8888 to network-byte order
							// and insert into the port field

	// Bind the socket to our local server address
	int nret = connect(m_sock, (LPSOCKADDR)&serverInfo, sizeof(serverInfo));

	if (nret < 0)
		return -1;
	m_bIsValid = true;
	return 0;
}

int		OS_SocketWin32::Close		()
{
	closesocket (m_sock);
	ResetState ();
	return 0;
}


OS_Socket*	OS_SocketWin32::Accept		()
{
	OS_SocketWin32* pNewSock = new OS_SocketWin32 ();
	pNewSock->m_sock = accept (m_sock, NULL, NULL);
	if (pNewSock->m_sock < 0)
	{
		delete pNewSock;
		return NULL;
	}
	pNewSock->m_bIsValid = true;
	return pNewSock;
}

int			OS_SocketWin32::Read		(void* pDestBuffer, int nMaxBytesToRead)
{
	int rc = recv (m_sock, (char*)pDestBuffer, nMaxBytesToRead, 0);
	return rc;
}

