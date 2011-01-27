/*----------------------------------------------------------*

	vcore.h
	The main include file for dynamic/static linking

*-----------------------------------------------------------*/
#ifndef _VCORE_H_
#define _VCORE_H_

/*--------------------- win32 defs for dll linking ---------*/
#ifdef _WIN32
#ifdef DLL_EXPORT
#define VCORE_EXPORT __declspec(dllexport)
#else
#define VCORE_EXPORT __declspec(dllimport)
#endif
#else /* not win32 */
#define VCORE_EXPORT
#endif
/*--------------------- end of win32 defs for dll linking ---------*/


VCORE_EXPORT	int			vcore_init			(const char* szFileName);
VCORE_EXPORT	int			vcore_get_int_opt	(const char* item_name, int* opt_value);
VCORE_EXPORT	const char*	vcore_get_str_opt	(const char* item_name);
VCORE_EXPORT	int			vcore_start			();
VCORE_EXPORT	int			vcore_stop			();
VCORE_EXPORT	int			vcore_get_version	(int* pver_major, int* pver_minor);

#endif // _VCORE_H_