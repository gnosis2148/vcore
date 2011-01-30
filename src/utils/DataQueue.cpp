/*----------------------------------------------------------*

	DataQueue.cpp
	A cyclic buffer implementing a FIFO - implementation
	Not thread-safe

*-----------------------------------------------------------*/


//-------------------- Include files -------------------------
#include <DataQueue.h>

//-------------------- Class Definition ----------------------
DataQueue::DataQueue	()
{
}

DataQueue::~DataQueue	()
{
}

int		DataQueue::AllocateMemory		(int nSizeBytes)
{
	return 0;
}

int		DataQueue::Write				(void* pData, int nDataSizeBytes)
{
	return 0;
}

void*	DataQueue::Read					(int nBytes)
{
	return 0;
}

int		DataQueue::GetTakenSizeBytes	()
{
	return 0;
}

int		DataQueue::GetFreeSizeBytes		()
{
	return 0;
}
