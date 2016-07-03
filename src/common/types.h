
#ifndef _SMILE_TYPES_H_
#define _SMILE_TYPES_H_

namespace smile {
  namespace common {
    /// UNICODE character
    typedef wchar_t                 uchar_t;
    /// Logical (bit)
    typedef bool                    bool_t;
    /// Byte (tiny unsigned int)
    typedef unsigned char           byte_t;
    /// Unsigned short integer (16 bits)
    typedef unsigned short int      ushort_t;
    /// Signed short integer (16 bits)
    typedef signed short int        short_t;
    /// Unsigned integer (32 bits)
    typedef unsigned int            uint_t;
    /// Signed short integer (32 bits)
    typedef signed int              int_t;
    /// Signed long integer (64 bits)
    typedef long long               long_t;
    /// Unsigned long integer (64 bits)
    typedef unsigned long long      ulong_t;
    /// Real number (64 bits)
    typedef double                  double_t;
    /// Character
    typedef char                    char_t;
    /// Object unique identifier
    typedef ulong_t                 oid_t;
    /// Invalid object identifier
    static const oid_t INVALID_OID = static_cast<oid_t>(0);
  }
}

#endif
