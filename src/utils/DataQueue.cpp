/*----------------------------------------------------------*

	DataQueue.cpp
	A cyclic buffer implementing a FIFO - implementation
	Not thread-safe

*-----------------------------------------------------------*/


//-------------------- Include files -------------------------
#include <stdio.h>
#include <stdlib.h>
#include <DataQueue.h>
#include <OS_Assert.h>

//-------------------- Class Definition ----------------------
DataQueue::DataQueue	()
{
	m_pData = NULL;
}

DataQueue::~DataQueue	()
{
	if (m_pData != NULL)
	{
		free (m_pData);
	}
}

int		DataQueue::AllocateMemory		(int nSizeBytes)
{
	m_pData = (char*)(malloc (nSizeBytes));
	OS_AssertMsg ((m_pData!=NULL), "Could not allocate queue memory");
	return 0;
}


int		DataQueue::GetByteCount			()
{
	return 0;
}

char*	DataQueue::GetWrittenArea		()
{
	return NULL;
}

int		DataQueue::GetFreeByteCount		()
{
	return 0;
}

char*	DataQueue::GetFreeArea			()
{
	return NULL;
}

int		DataQueue::GetFreeContByteCount	()
{
	return 0;
}

int		DataQueue::ReadDone				(int nByteCount)
{
	return 0;
}

int		DataQueue::WriteDone			(int nByteCount)
{
	return 0;
}


int		DataQueue::Reset				()
{
	return 0;
}
