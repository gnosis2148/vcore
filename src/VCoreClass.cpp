/*----------------------------------------------------------*

	zcore_class.cpp
	ZCore class implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <VCoreClass.h>

VCore::VCore	()
{
}

VCore::~VCore	()
{
}

int		VCore::Init	(const char* szConfigFileName)
{
	return 0;
}

int		VCore::Start	()
{
	return 0;
}

int		VCore::Stop	()
{
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
