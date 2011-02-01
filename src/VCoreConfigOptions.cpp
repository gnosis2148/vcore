/*----------------------------------------------------------*

	VCoreConfigOptions.cpp
	VCore specific config - Implementation
	Inherits from: ConfigOptions

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <VCoreConfigOptions.h>


VCoreConfigOptions::VCoreConfigOptions	()
{
	// ----------- server config and defaults ----------
	RegisterInt ("server.listen_port", 80);
	RegisterInt ("server.reactor_queue_size_send", 32768);
	RegisterInt ("server.reactor_queue_size_recv", 32768);


	// ----------- --------------------------------------
}

int	VCoreConfigOptions::OnReadDone	()
{
	int rc = GetInt ("server.listen_port", &m_nListenPort);
	return 0;
}




