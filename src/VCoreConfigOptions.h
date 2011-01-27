/*----------------------------------------------------------*

	VCoreConfigOptions.h
	VCore specific confg
	Inherits from: ConfigOptions

*-----------------------------------------------------------*/
#ifndef _VCORE_CONFIG_OPTIONS_H_
#define _VCORE_CONFIG_OPTIONS_H_

//-------------------- Include files -------------------------
#include <ConfigOptions.h>
#include <VCoreBuildDefs.h>



//-------------------- Class Definition ----------------------
class VCoreConfigOptions : public ConfigOptions
{
public:
	int	m_nListenPort;
public:
	VCoreConfigOptions	();
public:
	virtual	int	OnReadDone	();

};


#endif // _VCORE_CONFIG_OPTIONS_H_