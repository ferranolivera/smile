

#ifndef _BASE_TYPES_TRAITS_H_
#define _BASE_TYPES_TRAITS_H_ 

#include <base/platform.h>

SPA_BENCH_NS_BEGIN

/**
 * Trait for supported types 
 **/
template <typename T>
struct is_supported {
  static const bool value = false;
};

template <>
struct is_supported<float> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_FLOAT;
};

template <>
struct is_supported<double> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_DOUBLE;
};

template <>
struct is_supported<bool> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_BOOL;
};

template <>
struct is_supported<uint32_t> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_UNSIGNED_INT;
};

template <>
struct is_supported<uint64_t> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_UNSIGNED_LONG;
};

template <>
struct is_supported<int32_t> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_INT;
};

template <>
struct is_supported<int64_t> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_LONG;
};

template <>
struct is_supported<std::string> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_STRING;
};

template <>
struct is_supported<const char*> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_STRING;
};

template <>
struct is_supported<timestamp> {
  static const bool value = true;
  static const AttributeDataType type = AttributeDataType::E_TIMESTAMP;
};

SPA_BENCH_NS_END

#endif /* ifndef _TYPES_UTILS_H_H */
