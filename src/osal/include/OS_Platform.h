/*----------------------------------------------------------*

	OS_Platform.h
	Platform-dependent definitions

*-----------------------------------------------------------*/
#ifndef _OS_PLATFORM_H_
#define _OS_PLATFORM_H_

//-------------------- Include files -------------------------
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
int	OS_PlatformInit	();
#endif

//--------------- Object instantiation -----------------------
#include <OS_Socket.h>
OS_Socket*	OS_CreateSocket ();



#endif // _OS_PLATFORM_H_