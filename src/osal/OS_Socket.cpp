/*----------------------------------------------------------*

	OS_Socket.cpp
	Socket base class implementation - common for all 
	platforms
	

*-----------------------------------------------------------*/

//-------------------- Include files -------------------------
#include <string.h>
#include <OS_Socket.h>

OS_Socket::OS_Socket	()
{
	ResetState ();
}

int	OS_Socket::Init	(const char* szHostAddr, int nPortNum)
{
	strncpy (m_szHostName, szHostAddr, SOCKET_MAX_HOSTNAME_LEN);
	m_nDestPortNum = nPortNum;
	
	return 0;
}

void	OS_Socket::ResetState		()
{
	m_nDestPortNum = -1;
	m_bIsValid = false;
}



OS_Socket::~OS_Socket	()
{
}
