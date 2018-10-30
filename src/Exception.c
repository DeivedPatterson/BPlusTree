#include "../include/Exception.h"

jmp_buf exception_buffer; 						
unsigned long  exception_code;
enum ObjExceptionType ExceptionType;

struct ObjException Exception = {.message = "An Exception", .code = 254};
struct ObjException NullPointerException = {.message = "Null Pointer Exception", .code = __NullPointerException__};
struct ObjException FileWriteException = {.message = "An exception occurred in file recording", .code = __FileWriteException__};
struct ObjException FileReadException = {.message = "An exception occurred in file reading", .code = __FileReadException__};
struct ObjException ReWindExeption = {.message = "An exception occurred in Rewind operating", .code = __ReWindException__};
struct ObjException FileSeekException = {.message = "An exception occurred in Seek operating", .code = __FileSeekException__};
struct ObjException ClearErrorsException = {.message = "An exception occurred in clear errors operating", .code = __ClearErrorsException__};
struct ObjException FileCloseException = {.message = "An exception occurred in close operating", .code = __FileCloseException__};
struct ObjException FileOpenException = {.message = "An exception occurred in Open operating", .code = __FileOpenException__};
struct ObjException MemoryAllocationException  = {.message = "Exception: Memory allocation returned null pointer", .code = __MemoryAllocationException__};
struct ObjException ListRemoveException = {.message = "Exception in list removal operation.", .code = __ListRemoveException__};
struct ObjException ListInsertTopException = {.message = "Exception in the insert operation at the beginning of the list. List with Limited Property.", .code = __ListInsertTopException__};
struct ObjException ListInsertBottomException = {.message = "Exception in the insert operation at the end of the list. List with Limited Property.", .code = __ListInsertBottomException__};
struct ObjException ListInsertException = {.message = "Exception in the insert operation in the list. List with Limited Property.", .code = __ListInsertException__};
