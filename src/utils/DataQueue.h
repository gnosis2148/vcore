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
	int		Reset					();
	int		AllocateMemory			(int nSizeBytes);
	int		GetByteCount			();
	char*	GetWrittenArea			();
	int		GetFreeByteCount		();
	char*	GetFreeArea				();
	int		GetFreeContByteCount	();
	int		ReadDone				(int nByteCount);
	int		WriteDone				(int nByteCount);
};

#endif // _DATA_QUEUE_H_