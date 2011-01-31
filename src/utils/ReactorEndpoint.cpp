/*----------------------------------------------------------*

	ReactorEndpoint.cpp
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <ReactorEndpoint.h>
#include <SimpleParser.h>
//-------------------- Constants and Definitions -------------

//-------------------- Implementation -------------------------
ReactorEndpoint::ReactorEndpoint	()
{
}

int	ReactorEndpoint::Init		(const char* szAddress, EndpointType epType) // alloc the data queue
{
	int rc = ParseAddress (szAddress, epType);
	OS_Abort_If (rc<0);

	return 0;
}

int	ReactorEndpoint::ParseAddress		(const char* szAddress, EndpointType epType)
{
	char szTransport [REACTOR_ENDPOINT_MAX_TRANSPORT_NAME_LENGTH];
	char szPortNum [REACTOR_ENDPOINT_MAX_PORT_NUM_LENGTH];

	int nCurPos = 0;
	int rc = ParseToken (szAddress, &nCurPos, '/', szTransport, REACTOR_ENDPOINT_MAX_TRANSPORT_NAME_LENGTH);
	OS_AssertMsg ((rc>=0), "No transport specified");
	OS_AssertMsg ((szAddress[nCurPos+1]=='/'), "Incorrect address format - use <transport>://<address>:<port>");

	nCurPos += 2;
	rc = ParseToken (szAddress, &nCurPos, ':', m_szHostname, REACTOR_ENDPOINT_MAX_ADDRESS_LENGTH);
	OS_AssertMsg ((rc>=0), "No port number specified");

	nCurPos ++;
	rc = ParseToken (szAddress, &nCurPos, ':', szPortNum, REACTOR_ENDPOINT_MAX_PORT_NUM_LENGTH);
	m_nPortNum = atoi (szPortNum);
	OS_AssertMsg ((m_nPortNum > 0), "Illegal port number");

	return 0;
}


