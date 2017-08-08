

#ifndef _INDEX_H_
#define _INDEX_H_

#include <base/platform.h>
#include <map>
#include <vector>
#include <utility>

SMILE_NS_BEGIN

class IBaseIndex {
  public:
    virtual ~IBaseIndex() noexcept = default;
};

// T attribute type, used to index the index
// S key type of the values returned by the index
template<typename AttributeType, typename KeyType>
class Index : public IBaseIndex {
    SMILE_NON_COPYABLE(Index);
  public:

    Index() = default;
    virtual ~Index() noexcept(true) = default;

    Index(Index&&) = default;
    Index& operator=(Index&& ) = default;

    /**
     * Gets the elements with the given attribute value
     */
    const std::vector<KeyType>& getElements( const AttributeType attribute ) const noexcept {
      return m_data[attribute];
    }

    /** 
     * Inserts an element into the index
     * */
    void insert( const AttributeType attribute, const KeyType id ) noexcept {
      m_data[attribute].push_back(id);
    }

  private:

    /**
     * A map that holds, for each attribute value, a collection of elements
     * having that attribute value
     */
    mutable std::map<AttributeType, std::vector<KeyType>> m_data;
};

SMILE_NS_END

#endif /* ifndef _INDEX_H_
*/
