/*----------------------------------------------------------*

	OS_Platform.cpp
	Platform-dependent definitions

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Platform.h>
#include <win32/OS_Socket_win32.h>
	
int	OS_PlatformInit	()
{
	WSADATA wsadata;
	int iResult = WSAStartup (MAKEWORD(2,2), &wsadata);
	if (iResult != 0)
		return -1;
	return 0;
}


OS_Socket*	OS_CreateSocket ()
{
	return new OS_SocketWin32 ();
}
