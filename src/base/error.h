


#ifndef _DATA_ERROR_H_
#define _DATA_ERROR_H_

#include "base/platform.h"


SMILE_NS_BEGIN

enum class Error : uint8_t {
  E_NO_ERROR = 0,
  E_UNEXPECTED_ERROR,

  //GRAPH ERRORS
  E_INVALID_TYPE,
  E_EXISTING_TYPE,
  E_UNEXISTING_ATTRIBUTE_TYPE,
  E_EXISTING_ATTRIBUTE_TYPE,
  E_ATTRIBUTE_DATA_TYPE_MISSMATCH,
  E_ATTRIUTE_MAX_NUMBER,
  E_TYPE_MAX_NUMBER,
  E_UNEXISTING_OBJECT,

  //LOADER ERRORS
  E_UNEXPECTED_END_OF_STREAM
};

/** 
 * For convinience. Tells if the error is an error.
 **/
bool isError(const Error& e);


SMILE_NS_END


#endif /* ifndef _DATA_ERROR_H_ */
