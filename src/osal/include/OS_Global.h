/*----------------------------------------------------------*

	OS_Global.h
	Platform-agnostic global funcs - INTERFACE
	The implementation is in OS-specific folders below
	

*-----------------------------------------------------------*/
#ifndef _OS_GLOBAL_H_
#define _OS_GLOBAL_H_

//-------------------- Include files -------------------------

const char* OS_GetLastSocketErrorText	();
int			OS_GetLastSocketError		();

#endif // _OS_GLOBAL_H_

