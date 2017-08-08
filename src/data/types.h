

#ifndef _DATA_TYPES_H_
#define _DATA_TYPES_H_

#include <base/platform.h>
#include <cstdint>
#include <vector>
#include <string> 
#include <set>

SMILE_NS_BEGIN

class Graph;

using oid_t = uint64_t;
using typeid_t = uint8_t;
using attributeid_t = uint16_t;

enum class Condition {
  E_EQUALS,
  E_GREATER,
  E_GREATER_EQUALS,
  E_SMALLER,
  E_SMALLER_EQUALS,
  E_DIFFERENT
};

enum class Direction {
  E_UNDIRECTED,
  E_DIRECTED
};

struct IAttributeTypeInfo {

  IAttributeTypeInfo( const std::string attributeName,
                      const std::string typeName,
                      bool  isEdgeType,
                      bool  indexed,
                      attributeid_t typeId,
                      AttributeDataType dataType ) noexcept;

  virtual ~IAttributeTypeInfo() noexcept = default;

    const std::string       m_attributeName;         
    const std::string       m_typeName;
    const bool              m_isEdgeType;
    const bool              m_indexed;
    const attributeid_t     m_typeId;
    const AttributeDataType m_dataType;

    virtual void setAttribute( Graph& graph, oid_t oid, const std::string& value ) const noexcept = 0;
    virtual oid_t getOid( Graph& graph, const std::string& value ) const noexcept = 0;
};

template<typename T>
struct AttributeTypeInfo : public IAttributeTypeInfo {
    AttributeTypeInfo(const std::string attributeName,
                          const std::string typeName,
                          bool  isEdgeType,
                          bool  indexed,
                          attributeid_t typeId) noexcept : 
    IAttributeTypeInfo( attributeName,
                        typeName,
                        isEdgeType,
                        indexed,
                        typeId,
                        is_supported<T>::type) {};

    virtual ~AttributeTypeInfo() noexcept = default;
    virtual void setAttribute( Graph& graph, oid_t oid, const std::string& value ) const noexcept;
    virtual oid_t getOid( Graph& graph, const std::string& value ) const noexcept;
};


struct NodeTypeInfo {
    std::string                                                 m_name;
    typeid_t                                                    m_typeId;
    std::set<std::shared_ptr<IAttributeTypeInfo>>               m_attributes;
};

struct EdgeTypeInfo {
    std::string                                                 m_name;
    Direction                                                   m_direction;
    typeid_t                                                    m_typeId;
    std::set<std::shared_ptr<IAttributeTypeInfo>>               m_attributes;
};

struct Edge {
  oid_t m_tail;
  oid_t m_head;
};

template <typename T>
struct KeyValue {
  oid_t m_id;
  T     m_value;
};


template<typename T>
bool compareValues( const T& valueA, const T& valueB, const Condition condition ) {
  switch(condition) {
    case Condition::E_EQUALS:
      return valueA == valueB;
    case Condition::E_DIFFERENT:
      return valueA != valueB;
    case Condition::E_GREATER:
      return valueA > valueB;
    case Condition::E_GREATER_EQUALS:
      return valueA >= valueB;
    case Condition::E_SMALLER:
      return valueA < valueB;
    case Condition::E_SMALLER_EQUALS:
      return valueA <= valueB;
  }
  return false;
}

SMILE_NS_END

#endif

