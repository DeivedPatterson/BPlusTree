/*
	Author: Deived William da silva Azevedo
	Date: 01/03/2018
	File: Exception.h
	Dependencies: stdlib.h, setjmp.h
*/

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>


#define try    										\
													\
	exception_code = setjmp(exception_buffer);		\
	if(!exception_code)								


#define catch(ObjException)	else if(ObjException.code == exception_code)
#define throw(code) longjmp(exception_buffer, code)
#define finally else


#define PrintExceptionStdOut(Obj) printf("File: %s Funçao: %s %d %s, Exception Code: %lu\n",__FILE__, __FUNCTION__, __LINE__, Obj.message, Obj.code)



#define FileOpen(ptr, filename, mode)				\
													\
	try												\
	{												\
		ptr = fopen(filename, mode);				\
		if(ptr == NULL)								\
		{											\
			throw(__FileOpenException__);			\
		}											\
	}catch(FileOpenException)						\
	{												\
		PrintExceptionStdOut(FileOpenException);	\
	}


#define FileWrite(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fwrite(ptr, size, count, file);		\
			if(ferror(file) != 0)						\
			{											\
				ExceptionType = __FileWriteException__;	\
				throw(__FileWriteException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileWriteException)							\
	{													\
		PrintExceptionStdOut(FileWriteException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define FileRead(ptr, size, count, file, res)			\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			res = fread(ptr, size, count, file);		\
			if(ferror(file) != 0)						\
			{											\
				ExceptionType = __FileReadException__;	\
				throw(__FileReadException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileReadException)							\
	{													\
		PrintExceptionStdOut(FileReadException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}													

#define ReWind(file)									\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			rewind(file);								\
			if(ferror(file))							\
			{											\
				ExceptionType = __ReWindException__;	\
				throw(__ReWindException__);				\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(ReWindExeption)								\
	{													\
		PrintExceptionStdOut(ReWindExeption);			\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define FileSeek(file, offset, origin)					\
														\
	try													\
	{													\
		if(file != NULL)								\
		{												\
			fseek(file, offset, origin);				\
			if(ferror(file))							\
			{											\
				ExceptionType =__FileSeekException__; 	\
				throw(__FileSeekException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileSeekException)							\
	{													\
		PrintExceptionStdOut(FileSeekException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
	}

#define ClearErr(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			clearerr(file);								\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
		exit(-1);										\
	}



#define FileClose(file)									\
														\
	try													\
	{													\
		if(file !=  NULL)								\
		{												\
			if(fclose(file))							\
			{											\
				throw(__FileCloseException__);			\
			}											\
		}												\
		else											\
		{												\
			ExceptionType = __NullPointerException__;	\
			throw(__NullPointerException__);			\
		}												\
	}													\
	catch(FileCloseException)							\
	{													\
		PrintExceptionStdOut(FileCloseException);		\
	}													\
	catch(NullPointerException)							\
	{													\
		PrintExceptionStdOut(NullPointerException);		\
		abort();										\
	}



extern struct ObjException
{
	const char* message;
	unsigned long code; 
}Exception;



extern enum ObjExceptionType
{
	__NoExceptionsOccurred = 255,
	__FileOpenException__ = 1,
	__FileReadException__,
	__FileFlushException__,		
	__MemoryAllocationException__,
	__FileWriteException__,
	__NullPointerException__,
	__EndOfFileException__,
	__FileReOpenException__,
	__FileSeekException__,
	__PrintException__,
	__ReWindException__,
	__ClearErrorsException__,
	__FileCloseException__,
	__ListRemoveException__,
	__ListInsertTopException__,
	__ListInsertBottomException__,
	__ListInsertException__
}ExceptionType;


extern jmp_buf exception_buffer; 						
extern unsigned long  exception_code;
			
extern enum ObjExceptionType ExceptionType;
extern struct ObjException NullPointerException;
extern struct ObjException FileOpenException;
extern struct ObjException Exception;
extern struct ObjException FileWriteException;
extern struct ObjException FileReadException;
extern struct ObjException ReWindExeption;
extern struct ObjException FileSeekException;
extern struct ObjException ClearErrorsException;
extern struct ObjException FileCloseException;
extern struct ObjException MemoryAllocationException;
extern struct ObjException ListRemoveException;
extern struct ObjException ListInsertTopException;
extern struct ObjException ListInsertBottomException;
extern struct ObjException ListInsertException;

#endif