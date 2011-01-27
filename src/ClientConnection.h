/*----------------------------------------------------------*

	ClientConnection.h
	A ClientConnection holds all info relevant to an 
	open socket, including a two-way data queue

*-----------------------------------------------------------*/
#ifndef _CLIENT_CONNECTION_H_
#define _CLIENT_CONNECTION_H_


class ClientConnection
{
protected:
	int	fd; // socket descriptor
public:
	ClientConnection	();
	~ClientConnection	();
public:
	
};




#endif // _CLIENT_CONNECTION_H_