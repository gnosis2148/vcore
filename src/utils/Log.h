/*----------------------------------------------------------*

	Log.h
	Debugging and test-automation interface

*-----------------------------------------------------------*/
#ifndef _LOG_H_
#define _LOG_H_

//-------------------- Include files -------------------------
#include <stdio.h>

#define LOG_DEBUG	1
#define	LOG_ERROR	2
#define	LOG_FATAL	3


int	LOG_PrintMessage (int nLevel, const char* szFileName, int nLineNum, const char* szFormat, ...);

#ifdef _DEBUG
#define LOG_Debug LOG_PrintMessage (LOG_DEBUG, __FILE__, __LINE__, 
#define LOG_Error LOG_PrintMessage (LOG_ERROR, __FILE__, __LINE__, 
#define LOG_Fatal LOG_PrintMessage (LOG_FATAL, __FILE__, __LINE__, 
#define LOG_END );
#else // _DEBUG
#define LOG_Debug 
#define LOG_Error 
#define LOG_Fatal 
#define LOG_END
#endif 


#endif // _LOG_H_