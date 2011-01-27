/*----------------------------------------------------------*

	ConfigOptions.cpp
	A generic config option file parser utility - 
	implementation

*-----------------------------------------------------------*/

//-------------------- Include files -------------
#include <ConfigOptions.h>

//-------------------- Constants and Definitions -------------

//-------------------- Class Implementation ------------------
ConfigItem::ConfigItem	()
{
	m_bRegistered = false;
}


ConfigOptions::ConfigOptions		()
{
}


int	ConfigOptions::Read				(const char* szFileName)
{
	return 0;
}


int	ConfigOptions::RegisterInt		(const char* szItemName, int nDefaultValue, int nItemID)
{
	return 0;
}

int	ConfigOptions::RegisterString	(const char* szItemName, const char* szDefaultValue, int nItemID)
{
	return 0;
}

int			ConfigOptions::GetInt			(const char* szItemName, int* pnValue)
{
	return 0;
}

const char* ConfigOptions::GetString		(const char* szItemName)
{
	return 0;
}

int	ConfigOptions::OnReadDone	()
{
	return 0;
}

