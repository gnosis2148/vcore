/*----------------------------------------------------------*

	SimpleParser.h
	

*-----------------------------------------------------------*/
#ifndef _SIMPLE_PARSER_H_
#define _SIMPLE_PARSER_H_

//-------------------- Include files -------------------------
//-------------------- Constants and Definitions -------------

//-------------------- Class Definition ----------------------

//------------------------------------------------------------
// ParseToken
// Read the string until the separator is encountered
// Place the token into the buffer
// Update position
//------------------------------------------------------------
int	ParseToken	(const char* szString, int* pnCurPos, char szSeparator, char* szToken, int nTokenMaxLength);

#endif // _SIMPLE_PARSER_H_