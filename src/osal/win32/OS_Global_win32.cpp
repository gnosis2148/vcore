/*----------------------------------------------------------*

	OS_Global_win32.cpp
	Platform-agnostic global funcs - Win32 Implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <stdio.h>
#include <OS_Global.h>
#include <OS_Platform.h>


const char* OS_GetLastSocketErrorText	()
{
	return NULL;
}


int			OS_GetLastSocketError		()
{
	return WSAGetLastError ();
}
