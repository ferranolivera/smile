
#include "../base/error.h"

SMILE_NS_BEGIN

#define _ERROR_KEYWORD(symbol, test) text
char* errorMessages[static_cast<uint8_t>(ErrorCode::E_NUM_ERRORS)] = {
#include "../base/error.h"
};

bool isError(ErrorCode err) {
  return err != ErrorCode::E_NO_ERROR;
}

const char* getErrorMesg(ErrorCode err ) {
  return errorMessages[static_cast<uint8_t>(err)];
}

SMILE_NS_END

