

#ifndef _BASE_TYPES_H_
#define _BASE_TYPES_H_ 

#include "../base/macros.h"
#include <cstdint>
#include <string>

SMILE_NS_BEGIN

using uint8_t = std::uint8_t;
using uint16_t = std::uint16_t;
using uint32_t = std::uint32_t;
using uint64_t = std::uint64_t;
using int8_t  = std::int8_t;
using int16_t = std::int16_t;
using int32_t = std::int32_t;
using int64_t = std::int64_t;

struct timestamp {
  uint64_t val;

  bool operator==(const timestamp& t)  const noexcept {
    return val == t.val;
  }

  bool operator!=(const timestamp& t)  const noexcept {
    return val != t.val;
  }

  bool operator>(const timestamp& t)  const noexcept {
    return val > t.val;
  }

  bool operator>=(const timestamp& t)  const noexcept {
    return val <= t.val;
  }

  bool operator<(const timestamp& t)  const noexcept {
    return val < t.val;
  }

  bool operator<=(const timestamp& t)  const noexcept {
    return val <= t.val;
  }
};

enum class AttributeDataType{
    E_BOOL,
    E_INT,
    E_UNSIGNED_INT,
    E_LONG,
    E_UNSIGNED_LONG,
    E_FLOAT,
    E_DOUBLE,
    E_STRING,
    E_TIMESTAMP,
};

SMILE_NS_END

#endif 




