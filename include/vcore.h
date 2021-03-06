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

#ifdef __cplusplus
extern "C"
{
#endif

VCORE_EXPORT	int			vcore_init			(const char* szConfigFileName);
VCORE_EXPORT	int			vcore_get_int_opt	(const char* item_name, int* opt_value);
VCORE_EXPORT	const char*	vcore_get_str_opt	(const char* item_name);
VCORE_EXPORT	int			vcore_start			();
VCORE_EXPORT	int			vcore_stop			();
VCORE_EXPORT	int			vcore_get_version	(int* pver_major, int* pver_minor);
VCORE_EXPORT	void*		vcore_worker_init	();
VCORE_EXPORT	void*		vcore_get_request	(void* worker);
VCORE_EXPORT	int			vcore_write			(void* worker, void* data, int data_size_bytes);
VCORE_EXPORT	int			vcore_log			(void* worker, void* data, int data_size_bytes);

#ifdef __cplusplus
}
#endif


#endif // _VCORE_H_