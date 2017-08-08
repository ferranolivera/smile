


#ifndef _BASE_TYPES_UTILS_H_
#define _BASE_TYPES_UTILS_H_ value

#include <base/types.h>

SMILE_NS_BEGIN

bool parseBool( const std::string& value );
int32_t parseInt32( const std::string& value );
int64_t parseInt64( const std::string& value );
uint32_t parseUInt32( const std::string& value );
uint64_t parseUInt64( const std::string& value );
float parseFloat(const std::string& value );
double parseDouble(const std::string& value );
timestamp parseTimestamp(const std::string& value);

template<typename T>
struct parser {
  static T parse( const std::string& str );
};

template<>
struct parser<bool> {
  static bool parse( const std::string& str ) {
    return parseBool(str);
  }
};

template<>
struct parser<uint32_t> {
  static uint32_t parse( const std::string& str ) {
    return parseUInt32(str);
  }
};

template<>
struct parser<int32_t> {
  static int32_t parse( const std::string& str ) {
    return parseInt32(str);
  }
};

template<>
struct parser<uint64_t> {
  static uint64_t parse( const std::string& str ) {
    return parseUInt64(str);
  }
};

template<>
struct parser<int64_t> {
  static int64_t parse( const std::string& str ) {
    return parseInt64(str);
  }
};

template<>
struct parser<float> {
  static float parse( const std::string& str ) {
    return parseFloat(str);
  }
};

template<>
struct parser<double> {
  static double parse( const std::string& str ) {
    return parseDouble(str);
  }
};

template<>
struct parser<std::string> {
  static std::string parse( const std::string& str ) {
    return str;
  }
};

template<>
struct parser<timestamp> {
  static timestamp parse( const std::string& str ) {
    return parseTimestamp(str);
  }
};

SMILE_NS_END

#endif /* ifndef _BASE_TYPES_UTILS_H_ */
