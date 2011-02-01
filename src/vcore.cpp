/*----------------------------------------------------------*

	zcore.cpp
	The zcore API implementation

*-----------------------------------------------------------*/

#include <vcore.h>
#include <VCoreClass.h>

static VCore		theVCore;
static VCoreLogger	theLogger;

VCORE_EXPORT	int		vcore_init			(const char* szConfigFileName)
{
	int rc = OS_PlatformInit ();
	OS_Abort_If ((rc<0));
	return theVCore.Init (szConfigFileName);
}

VCORE_EXPORT	int		vcore_get_int_opt	(const char* item_name, int* opt_value)
{
	return theVCore.GetConfigOptions()->GetInt (item_name, opt_value);
}

VCORE_EXPORT	const char*		vcore_get_str_opt	(const char* item_name)
{
	return theVCore.GetConfigOptions()->GetString (item_name);
}

VCORE_EXPORT	int		vcore_start			()
{
	theLogger.Init (theVCore.GetConfigOptions ());
	theLogger.Start ();
//	theVCore.Start ();
	theLogger.Join ();
	return 0;
}

VCORE_EXPORT	int		vcore_stop			()
{
	return theVCore.Stop ();
}

VCORE_EXPORT	int		vcore_get_version	(int* pver_major, int* pver_minor)
{
	return theVCore.GetVersion (pver_major, pver_minor);
}

