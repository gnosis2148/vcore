/*----------------------------------------------------------*

	OS_Thread_win32.cpp
	An OS_Thread Interface Implemented for Win32
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <OS_Thread.h>
#include <OS_Assert.h>
#include <windows.h>
//-------------------- Implementation ------------------------

//------------ ThreadInfo class ------------------------------
class ThreadInfo
{
public:
	HANDLE	m_hThreadHandle;
	DWORD	m_dwThreadID;
};


//------------ Static thread function ------------------------
static DWORD WINAPI GlobalThreadProc (void* pParam)
{
	OS_Thread* pThread = (OS_Thread*)pParam;
	pThread->OnStart ();
	return (DWORD)(pThread->Run ());
}




int	OS_Thread::Start	()
{
	ThreadInfo* pInfo = (ThreadInfo*)(malloc (sizeof (ThreadInfo)));
	if (pInfo == NULL)
	{
		OS_Fatal ("Out of memory - could not allocate ThreadInfo");
		return -1;
	}

	m_pThreadObject = pInfo;
	pInfo->m_hThreadHandle = CreateThread (NULL, 0, GlobalThreadProc, this, 0, &pInfo->m_dwThreadID);
	if (pInfo->m_hThreadHandle == NULL)
	{
		OS_Fatal ("Could not start thread");
		return -1;
	}

	return 0;
}

int		OS_Thread::Join	()
{
	ThreadInfo* pInfo = (ThreadInfo*)(m_pThreadObject);
	return WaitForSingleObject (pInfo->m_hThreadHandle, INFINITE);
}


/*
int	OS_Thread::Stop	(bool bWait)
{
	bWait;
	return 0;
}
*/