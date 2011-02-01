/*----------------------------------------------------------*

	OS_Thread.h
	An OS-Agnostic Thread Interface
	Implementation is under either posix/ or win32/ below

*-----------------------------------------------------------*/
#ifndef _OS_THREAD_H_
#define _OS_THREAD_H_

//-------------------- Include files -------------------------
#include <stdio.h>
#include <stdlib.h>

//-------------------- Class Definition ----------------------
class OS_Thread
{
protected:
	void* m_pThreadObject; // allocated by the implementation code
public:
	OS_Thread	()
	{
		m_pThreadObject = NULL;
	}

	~OS_Thread	()
	{
		if (m_pThreadObject != NULL)
		{
			free (m_pThreadObject);
		}
	}

public:
	int		Start	();
	int		Join	();
public:
	virtual	int		Run		() = 0;
	virtual	int		OnStart	() {return 0; }
	virtual int		OnStop	() {return 0; }
};


#endif // _OS_THREAD_H_

