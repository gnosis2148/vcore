/*----------------------------------------------------------*

	WireProtocol.h
	Given a block of data, capable to determine if 
	an entire message has been received,
	and determine its boundaries.
	Subclasses support length-based and end-of-message based protocols

*-----------------------------------------------------------*/
#ifndef _WIRE_PROTOCOL_H_
#define _WIRE_PROTOCOL_H_

//-------------------- Include files -------------------------
#include <OS_Platform.h>


//-------------------- Class Definition ----------------------
class	WireProtocol
{
protected:
	int	m_nMaxMessageLength; // used for sanity checks on incoming messages
public:
	virtual	bool IsMessageComplete	(char* pBuffer, int** pnMessageStart, int** pnMessageLength) = 0;
};


#endif // _WIRE_PROTOCOL_H_