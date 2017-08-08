

#include <data/types.h>
#include <data/graph.h>
#include <data/immutable_table.h>
#include <base/types_utils.h>

SPA_BENCH_NS_BEGIN

IAttributeTypeInfo::IAttributeTypeInfo( const std::string attributeName,
                      const std::string typeName,
                      bool  isEdgeType,
                      bool  indexed,
                      attributeid_t typeId,
                      AttributeDataType dataType ) noexcept :
    m_attributeName(attributeName),
                        m_typeName(typeName),
                        m_isEdgeType(isEdgeType),
                        m_indexed(indexed),
                        m_typeId(typeId),
                        m_dataType(dataType) {};

template<typename T>
void AttributeTypeInfo<T>::setAttribute( Graph& graph, oid_t oid, const std::string& value ) const noexcept {
  graph.setAttribute(oid,m_attributeName, parser<T>::parse(value));
}

template<typename T>
oid_t AttributeTypeInfo<T>::getOid( Graph& graph, const std::string& value ) const noexcept {
  return graph.select(m_typeName, m_attributeName, Condition::E_EQUALS, parser<T>::parse(value))->get(0);
};

AttributeTypeInfo<bool> boolInfo("test","test",false,false,0);
AttributeTypeInfo<uint32_t> uint32Info("test","test",false,false,0);
AttributeTypeInfo<int32_t> int32Info("test","test",false,false,0);
AttributeTypeInfo<uint64_t> uint64Info("test","test",false,false,0);
AttributeTypeInfo<int64_t> int64Info("test","test",false,false,0);
AttributeTypeInfo<float> floatInfo("test","test",false,false,0);
AttributeTypeInfo<double> doubleInfo("test","test",false,false,0);
AttributeTypeInfo<std::string> stringInfo("test","test",false,false,0);
AttributeTypeInfo<timestamp> timestampInfo("test","test",false,false,0);

SPA_BENCH_NS_END

