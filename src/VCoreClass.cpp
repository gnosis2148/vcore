/*----------------------------------------------------------*

	zcore_class.cpp
	ZCore class implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Assert.h>
#include <VCoreClass.h>

VCore::VCore	()
{
	m_bPleaseStop = false;
}

VCore::~VCore	()
{
}

int		VCore::Init	(const char* szConfigFileName)
{
	int rc;
	rc = m_cfg.Read (szConfigFileName);
	if (rc < 0)
	{
		OS_Error (m_cfg.GetLastError());
		OS_Fatal ("Could not read config file");
		return -1;
	}

	rc = m_logger.Init (&m_cfg);
	if (rc < 0)
	{
		OS_Fatal ("Could not init logger");
		return -1;
	}

	m_logger.Start ();
	return 0;
}


VCoreConfigOptions&	VCore::GetConfigOptions	()
{
	return m_cfg;
}

int	VCore::GetVersion			(int* pnMajor, int* pnMinor)
{
	return 0;
}
