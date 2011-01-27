/*----------------------------------------------------------*

	ConfigOptions.h
	A generic config option file parser utility

*-----------------------------------------------------------*/
#ifndef _CONFIG_OPTIONS_H_
#define _CONFIG_OPTIONS_H_

//-------------------- Constants and Definitions -------------

#define CONFIG_ITEM_MAX_LEN	256
#define	CONFIG_MAX_ITEMS	64

//-------------------- Class Definition ----------------------
class ConfigItem
{
public:
	typedef enum
	{
		CFGT_INT,
		CFGT_STRING
	} ItemType;
public:
	int			m_nID;
	ItemType	m_type;
	char		m_szName [CONFIG_ITEM_MAX_LEN];
	int			m_nValue;
	char		m_szValue [CONFIG_ITEM_MAX_LEN];
	char		m_szDefaultValue [CONFIG_ITEM_MAX_LEN];
	int			m_nDefaultValue;
	bool		m_bRegistered;
public:
	ConfigItem	();
};

class ConfigOptions
{
protected:
	ConfigItem	m_items [CONFIG_MAX_ITEMS];
	char		m_szLastError [CONFIG_ITEM_MAX_LEN];
public:
	ConfigOptions ();
public:
//---- reading and parsing -----------------------
	int	Read			(const char* szFileName);
	int	RegisterInt		(const char* szItemName, int nDefaultValue, int nItemID = -1);
	int	RegisterString	(const char* szItemName, const char* szDefaultValue, int nItemID = -1);
//---- accessing ---------------------------------
	int			GetInt			(int nItemID, int* pnValue);
	const char* GetString		(int nItemID);
	int			FindItem		(const char* szItemName);
	int			GetInt			(const char* szItemName, int* pnValue);
	const char* GetString		(const char* szItemName);

public:
	virtual	int	OnReadDone	();
};







#endif // _CONFIG_OPTIONS_H_