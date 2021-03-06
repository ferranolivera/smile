



#ifndef _ERROR_KEYWORD
#include "../base/macros.h"
#include "../base/types.h"

#ifndef _ERROR_CODES_H_
#define _ERROR_CODES_H_

SMILE_NS_BEGIN

#define _MAKE_KEYWORD_ENUM
#define _ERROR_KEYWORD(symbol, text) symbol 

enum class ErrorCode : uint8_t {
#endif

  _ERROR_KEYWORD(E_NO_ERROR = 0, "No error"),
  _ERROR_KEYWORD(E_UNEXPECTED_ERROR, "SMILE Unexpected error"),

  // STORAGE ERRORS
  _ERROR_KEYWORD(E_STORAGE_INVALID_PATH , "STORAGE Invalid path"),
  _ERROR_KEYWORD(E_STORAGE_PATH_ALREADY_EXISTS , "STORAGE Path already exists"),
  _ERROR_KEYWORD(E_STORAGE_INVALID_CONFIG , "STORAGE Invalid configuration"),
  _ERROR_KEYWORD(E_STORAGE_UNEXPECTED_READ_ERROR , "STORAGE Unexpected read error"),
  _ERROR_KEYWORD(E_STORAGE_UNEXPECTED_WRITE_ERROR , "STORAGE Unexpected write error"),
  _ERROR_KEYWORD(E_STORAGE_CRITICAL_ERROR , "STORAGE Critical error"),

  // BUFFER POOL ERRORS
  _ERROR_KEYWORD(E_BUFPOOL_OUT_OF_MEMORY , "BUFPOOL Out of memory"),
  _ERROR_KEYWORD(E_BUFPOOL_POOL_SIZE_NOT_MULTIPLE_OF_PAGE_SIZE , "BUFPOOL Pool size not multiple of page size "),
  _ERROR_KEYWORD(E_BUFPOOL_ALLOCATED_PAGE_IN_FREELIST , "BUFPOOL Allocated page in free list"),
  _ERROR_KEYWORD(E_BUFPOOL_PROTECTED_PAGE_IN_FREELIST , "BUFPOOL Protected page in free list"),
  _ERROR_KEYWORD(E_BUFPOOL_FREE_PAGE_NOT_IN_FREELIST , "BUFPOOL Free page in free list"),
  _ERROR_KEYWORD(E_BUFPOOL_BUFFER_DESCRIPTOR_INCORRECT_DATA , "BUFPOOL Buffer Descriptor incorrect data "),
  _ERROR_KEYWORD(E_BUFPOOL_FREE_PAGE_MAPPED_TO_BUFFER , "BUFPOOL Free page mapped to buffer"),
  _ERROR_KEYWORD(E_BUFPOOL_NO_THREADS_AVAILABLE_FOR_PREFETCHING , "BUFPOOL No threads available for prefetching"),
  _ERROR_KEYWORD(E_BUFPOOL_NUMA_API_NOT_SUPPORTED , "BUFPOOL NUMA API not supported"),

  // SCHEMA ERRORS
  
  _ERROR_KEYWORD(E_SCHEMA_PAGE_CORRUPTED , "SCHEMA page corrupted"),
  _ERROR_KEYWORD(E_SCHEMA_ELEMENT_NAME_TOO_LONG , "SCHEMA element name too long"),
  _ERROR_KEYWORD(E_SCHEMA_NODE_TYPE_ALREADY_EXISTS , "SCHEMA node type already exist"),
  _ERROR_KEYWORD(E_SCHEMA_NODE_TYPE_NOT_EXISTS , "SCHEMA node type does not exist"),
  _ERROR_KEYWORD(E_SCHEMA_INVALID_TYPE , "SCHEMA Invalid type"),
  _ERROR_KEYWORD(E_SCHEMA_EXISTING_TYPE , "SCHEMA Already existing type"),
  _ERROR_KEYWORD(E_SCHEMA_UNEXISTING_ATTRIBUTE_TYPE , "Graph Unexisting attribute type"),
  _ERROR_KEYWORD(E_SCHEMA_EXISTING_ATTRIBUTE_TYPE , "SCHEMA Already existing attribute type"),
  _ERROR_KEYWORD(E_SCHEMA_ATTRIBUTE_DATA_TYPE_MISSMATCH , "SCHEMA Attribute data type missmatch"),
  _ERROR_KEYWORD(E_SCHEMA_ATTRIUTE_MAX_NUMBER , "SCHEMA Max number of attributes achieved"),
  _ERROR_KEYWORD(E_SCHEMA_TYPE_MAX_NUMBER , "SCHEMA Max number of types achieved"),
  _ERROR_KEYWORD(E_SCHEMA_UNEXISTING_OBJECT , "SCHEMA Unexisting object"),

#ifdef _MAKE_KEYWORD_ENUM
  E_NUM_ERRORS
};

bool isError(ErrorCode err); 

const char* getErrorMesg(ErrorCode err );

SMILE_NS_END

#undef _ERROR_KEYWORD
#undef _MAKE_KEYWORD_ENUM



#endif /* ifndef _DATA_ERROR_H_ */
#endif
