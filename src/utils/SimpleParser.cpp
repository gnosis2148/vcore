/*----------------------------------------------------------*

	SimpleParser.cpp
	

*-----------------------------------------------------------*/


//-------------------- Include files -------------------------
#include <SimpleParser.h>
//-------------------- Constants and Definitions -------------

//-------------------- Class Definition ----------------------
int	ParseToken	(const char* szString, int* pnCurPos, char szSeparator, char* szToken, int nTokenMaxLength)
{
	int nDestIndex = 0;
	while ((szString[*pnCurPos] != 0) && (szString[*pnCurPos] != szSeparator))
	{
		if (nDestIndex+1 < nTokenMaxLength)
		{
			szToken[nDestIndex] = szString[*pnCurPos];
			nDestIndex ++;
		}
		*pnCurPos += 1;
	}
	szToken[nDestIndex] = 0;
	if (szString[*pnCurPos] == szSeparator)
		return 0;

	return -1;
}
