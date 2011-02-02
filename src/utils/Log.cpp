/*----------------------------------------------------------*

	Log.cpp
	Debugging and test-automation interface - implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <stdarg.h>
#include <Log.h>

#define LOG_MAX_MESSAGE_LENGTH	1024

static char* LOG_GetMessageLevel (int nLevel)
{
	if (nLevel == LOG_DEBUG)
		return "DEBUG";
	if (nLevel == LOG_ERROR)
		return "ERROR";
	//if (nLevel == LOG_FATAL)
		return "FATAL";
}

int	LOG_PrintMessage (int nLevel, const char* szFileName, int nLineNum, const char* szFormat, ...)
{
	char szMessage [LOG_MAX_MESSAGE_LENGTH];
	va_list args;
	va_start (args, szFormat);
	vsprintf (szMessage, szFormat, args);
	va_end (args);

	fprintf (stderr, "%s\t%-40s\t[%s:%d]\n", LOG_GetMessageLevel (nLevel), szMessage, szFileName, nLineNum);
	return 0;
}

