
#include "../base/error.h"

SMILE_NS_BEGIN

bool isError(const ErrorCode& e) {
  return e != ErrorCode::E_NO_ERROR;
}

SMILE_NS_END

