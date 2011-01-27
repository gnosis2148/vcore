/*----------------------------------------------------------*

	VCoreConfigOptions.cpp
	VCore specific config - Implementation
	Inherits from: ConfigOptions

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <VCoreConfigOptions.h>


VCoreConfigOptions::VCoreConfigOptions	()
{
	RegisterInt ("server.listen_port", 80);
}

int	VCoreConfigOptions::OnReadDone	()
{
	int rc = GetInt ("server.listen_port", &m_nListenPort);
	return 0;
}




