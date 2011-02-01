/*----------------------------------------------------------*

	DataQueue.h
	A cyclic buffer implementing a FIFO
	Not thread-safe

*-----------------------------------------------------------*/
#ifndef _DATA_QUEUE_H_
#define _DATA_QUEUE_H_

//-------------------- Include files -------------------------


//-------------------- Class Definition ----------------------
class	DataQueue
{
protected:
	char*	m_pData;
	int		m_pTotalSize;
	int		m_nReadIndex;
	int		m_nWriteIndex;
public:
	DataQueue	();
	~DataQueue	();
public:
	int		AllocateMemory		(int nSizeBytes);
	int		Write				(void* pData, int nDataSizeBytes);
	void*	Read				(int nBytes);
	int		GetTakenSizeBytes	();
	int		GetFreeSizeBytes	();
};

#endif // _DATA_QUEUE_H_