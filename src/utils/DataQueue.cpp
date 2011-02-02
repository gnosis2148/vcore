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
	m_nTotalSize = nSizeBytes;
	Reset ();
	return 0;
}

//----------------------------------------------------------
//
//	GetByteCount
//	Return the amount of bytes written to the queue
//
int		DataQueue::GetByteCount			()
{
	return m_nWriteIndex - m_nReadIndex;
}

char*	DataQueue::GetWrittenArea		()
{
	return m_pData + m_nReadIndex;
}

int		DataQueue::GetFreeByteCount		()
{
	return (m_nReadIndex - m_nWriteIndex + m_nTotalSize) % m_nTotalSize;
}

char*	DataQueue::GetFreeArea			()
{
	return m_pData + m_nWriteIndex;
}

int		DataQueue::GetFreeContByteCount	()
{
	return m_nTotalSize - m_nWriteIndex;
}

int		DataQueue::ReadDone				(int nByteCount)
{
	m_nReadIndex = (m_nReadIndex + nByteCount) % m_nTotalSize;
	return 0;
}

int		DataQueue::WriteDone			(int nByteCount)
{
	m_nWriteIndex = (m_nWriteIndex + nByteCount) % m_nTotalSize;
	return 0;
}


int		DataQueue::Reset				()
{
	m_nReadIndex = m_nWriteIndex = 0;
	return 0;
}
