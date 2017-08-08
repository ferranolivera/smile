
#include <base/error.h>

SMILE_NS_BEGIN

bool isError(const Error& e) {
  return e != Error::E_NO_ERROR;
}

SMILE_NS_END

