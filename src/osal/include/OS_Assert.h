/*----------------------------------------------------------*

	OS_Assert.h
	An OS-Agnostic Assertion Interface
	Implementation is under either posix/ or win32/ below

*-----------------------------------------------------------*/
#ifndef _OS_ASSERT_H_
#define _OS_ASSERT_H_

//-------------------- Include files -------------------------
#include <process.h>

//-------------------- Definition ----------------------------
#define OS_ERROR_MESSAGE_LENGTH	256

#define OS_Fatal(msg)		fprintf (stderr, "%s:%d %s\n", __FILE__, __LINE__, msg); exit(0);
#define OS_Error(msg)		fprintf (stderr, "%s:%d %s\n", __FILE__, __LINE__, msg); 
#define OS_Assert(val)		if(!(val)) {OS_Fatal("Assertion failed");}
#define OS_AssertMsg(val,msg)	if(!(val)) {fprintf (stderr, "%s:%d %s\n", __FILE__, __LINE__, msg); exit(0);}
#define OS_Abort_If(val)	if((val))  {OS_Fatal("Assertion failed");}

#endif //_OS_ASSERT_H_

