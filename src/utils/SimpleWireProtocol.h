/*----------------------------------------------------------*

	SimpleWireProtocol.h
	base: WireProtocol
	Given a block of data, capable to determine if 
	an entire message has been received,
	and determine its boundaries.
	Supports length-based and end-of-message based protocols

*-----------------------------------------------------------*/
#ifndef _WIRE_PROTOCOL_H_
#define _WIRE_PROTOCOL_H_

//-------------------- Include files -------------------------
#include <OS_Platform.h>


//-------------------- Class Definition ----------------------
class	SimpleWireProtocol
{
public:
	enum
	{
		WP_LENGTH,
		WP_END_OF_MESSAGE
	};
protected:
	int		m_nType;
	int		m_nLengthLengthInBytes;
	bool	m_bLengthIncludesLength;
	char*	m_endOfMessageMarker;
	int		m_nEndOfMessageMarkerLength;
public:
	void	SetModeLength	(int nLengthLengthInBytes, bool bLengthIncludesLength);
	void	SetModeEOM		(const char* eomBuffer, int nEomBufferLength);

	virtual	bool IsMessageComplete	(char* pBuffer, int** pnMessageStart, int** pnMessageLength);
};


#endif // _WIRE_PROTOCOL_H_