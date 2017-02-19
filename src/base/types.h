
#ifndef _SMILE_BASE_TYPES_H_
#define _SMILE_BASE_TYPES_H_

#include "base/macros.h"
#include <cstdint>

SMILE_NS_BEGIN
    /// Unsigned short integer (8 bits)
    using uint8_t = std::uint8_t;
    /// Signed short integer (8 bits)
    using int8_t  = std::int8_t;
    /// Unsigned short integer (16 bits)
    using uint16_t = std::uint16_t;
    /// Signed short integer (16 bits)
    using int16_t  = std::int16_t;
    /// Unsigned integer (32 bits)
    using uint32_t = std::uint32_t;
    /// Signed short integer (32 bits)
    using int32_t  = std::int32_t;
    /// Signed long integer (64 bits)
    using int64_t  = std::int64_t;
    /// Unsigned long integer (64 bits)
    using uint64_t = std::uint64_t;
SMILE_NS_END

#endif
