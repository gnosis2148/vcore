/*----------------------------------------------------------*

	OS_SocketWin32.cpp
	Platform-specific socket implementation
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <win32/OS_Socket_win32.h>

int	OS_SocketWin32::Bind	()
{
	SOCKADDR_IN serverInfo;
	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr.s_addr = INADDR_ANY;	// Since this socket is listening for connections,
							// any local address will do
	serverInfo.sin_port = htons(8888);		// Convert integer 8888 to network-byte order
							// and insert into the port field

	// Bind the socket to our local server address
	int nret = bind(m_sock, (LPSOCKADDR)&serverInfo, sizeof(struct sockaddr));

	if (nret == SOCKET_ERROR)
	{
		nret = WSAGetLastError();
		return -1;
	}

	return 0;
}




