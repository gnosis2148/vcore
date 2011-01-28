/*----------------------------------------------------------*

	VCoreClass.h
	A VCore is a class instantiated within the DLL

*-----------------------------------------------------------*/
#ifndef _VCORE_CLASS_H_
#define _VCORE_CLASS_H_

//-------------------- Include files -------------------------
#include <ClientConnection.h>
#include <VCoreConfigOptions.h>
#include <VCoreBuildDefs.h>
#include <VCoreLogger.h>


//-------------------- Class Definition ----------------------
class VCore
{
protected:
	ClientConnection	m_connections [VCORE_MAX_CONN_CLIENTS];	
	VCoreConfigOptions	m_cfg;
	VCoreLogger			m_logger;
	bool				m_bPleaseStop; // set from outside to indicate stop request
public:
	VCore	();
	~VCore	();
public: 
//----- the public DLL API maps to these class methods
	int		Init	(const char* szConfigFileName);
	int		Start	();
	int		Stop	();
	
	VCoreConfigOptions&	GetConfigOptions	();
	int					GetVersion			(int* pnMajor, int* pnMinor);

};



#endif // _ZCORE_CLASS_H_