

#ifndef _TABLE_H_
#define _TABLE_H_

#include <base/platform.h>
#include <vector>
#include <memory>
#include <functional>
#include <array>
#include <cassert>
#include <iostream>

SMILE_NS_BEGIN 

/** 
 * Base case for all tables regardless of their type
 * */
class IBaseTable {
  public:
    virtual ~IBaseTable() noexcept = default;
};

/** 
 * Interface representing a statically typed table
 * */
template<typename T>
class ITypedTable : public IBaseTable {
  public:
    ITypedTable() = default;
    virtual ~ITypedTable() noexcept = default;

    /**
     * Appends an element to the table
     * */
    virtual void append(const T& val) noexcept = 0;

    /**
     * Applies a function to each element of the ImmutableTable 
     * @param[in] f The function to apply
     **/
    virtual void foreach( std::function<void(const T&)> f ) const noexcept = 0;

    /** 
     * Gets the size of the table
     * */
    virtual uint64_t size() const noexcept = 0;

    /**
     * Gets the capacity of the table
     **/
    virtual uint64_t getCapacity() const noexcept = 0;

    /** 
     * Gets the nth element of the table
     **/
    virtual T get(const uint64_t index) const noexcept = 0;
};

/**
 * Minimum capacity of a table block. This will be the size of a
 * FixedLengthTable, thus tables must be at least these size.  
 **/
constexpr uint32_t minCapacity = 8192;

/**
 * The arity of the tree used to store a table. That is, each level of 
 * the tree can hold kArity tables.
 **/
constexpr uint32_t kArity = 1024;

template<typename T>
class FixedLengthTable : public ITypedTable<T> {
    SMILE_NON_COPYABLE(FixedLengthTable);
  public:
    FixedLengthTable() {};
    virtual ~FixedLengthTable() noexcept = default;

    FixedLengthTable( FixedLengthTable &&  ) = default;
    FixedLengthTable& operator=( FixedLengthTable && ) = default;

    void append(const T& val) noexcept override {
      m_data[m_size] = val;
      m_size+=1;
    }

    void foreach( std::function<void(const T&)> f ) const noexcept override {
      for(uint32_t i = 0; i < m_size; ++i) {
        f(m_data[i]);
      }
    }

    uint64_t size() const noexcept override {
      return m_size;
    }

    uint64_t getCapacity() const noexcept override {
      return minCapacity;
    }

    T get(const uint64_t index) const noexcept override {
      return m_data[index];
    }

  private:
    uint32_t                    m_size = 0;
    std::array<T,minCapacity>   m_data;
};

template<typename T>
class OneElementTable : public ITypedTable<T> {
    SMILE_NON_COPYABLE(OneElementTable);
  public:
    OneElementTable( T val ) : m_val(val) {};
    virtual ~OneElementTable() noexcept = default;

    OneElementTable( OneElementTable &&  ) = default;
    OneElementTable& operator=( OneElementTable && ) = default;

    void append(const T& val) noexcept override {
      std::cerr << "WARNING: append on a OneElementTable should never be called" << std::endl; 
    }

    void foreach( std::function<void(const T&)> f ) const noexcept override {
      f(m_val);
    }

    uint64_t size() const noexcept override {
      return 1;
    }

    uint64_t getCapacity() const noexcept override {
      return 1;
    }

    T get(const uint64_t index) const noexcept override {
      if( index != 0) {
        std::cerr << "WARNING: calling get on a OneElementTable with index != 0 " << std::endl; 
      }
      return m_val;
    }

  private:
    T m_val;
};

/**
 * Typed Table of dynamic size. 
 * It is implemented as a k-tree, where at each level there are
 * k subtables. The leafs of the tree are FixedLengthTables of the same data
 * type. When more rows are needed, a new level of the tree is created.
 * Initially, a single level with a single FixedLength table is created.
 * */
template<typename T>
class Table : public ITypedTable<T> {
    SMILE_NON_COPYABLE(Table);
  public:
    Table() {
      for(uint32_t i = 0; i < kArity; ++i) {
        m_blocks[i] = nullptr;
      }
      m_blocks[0] = std::shared_ptr<ITypedTable<T>>( new FixedLengthTable<T>() );
    };

    Table( uint64_t capacity ) : 
      m_size(0),
      m_capacity(capacity), 
      m_blockCapacity(m_capacity / kArity),
      m_currentBlock(0) {

      assert(capacity % minCapacity == 0);
      for(uint32_t i = 0; i < kArity; ++i) {
        m_blocks[i] = nullptr;
      }
      m_blocks[0] = createTable(m_blockCapacity);
    };

    virtual ~Table() noexcept = default;

    Table( Table &&  ) = default;
    Table& operator=( Table && ) = default;

    void append(const T& val) noexcept override {
      if(m_blocks[m_currentBlock]->size() < m_blocks[m_currentBlock]->getCapacity()) {
        m_blocks[m_currentBlock]->append(val);
        m_size+=1;
      } else {
        if(m_currentBlock+1 < kArity) {
          m_currentBlock+=1;
          m_blocks[m_currentBlock] = createTable(m_blockCapacity);
        } else {
          grow();
        }
        append(val);
      }
    }

    void foreach( std::function<void(const T&)> f ) const noexcept override {
      for(uint32_t i = 0; i <= m_currentBlock; ++i) {
        m_blocks[i]->foreach(f);
      }
    }

    uint64_t size() const noexcept override {
      return m_size;
    }

    uint64_t getCapacity() const noexcept override {
      return m_capacity;
    }

    T get(const uint64_t index) const noexcept override {
      uint32_t block = index / m_blockCapacity;
      uint32_t offset = index % m_blockCapacity;
      return m_blocks[block]->get( offset );
    }

  private:

    /**
     * Creates a table of a given capacity. If the capacity is smaller or equal
     * to minCapacity, then we create a FixedLengthTable. Otherwise, we create a
     * dynamic table.
     * */
    static std::shared_ptr<ITypedTable<T>> createTable( uint64_t capacity ) noexcept {
      if(capacity == minCapacity) {
        return std::shared_ptr<ITypedTable<T>>( new FixedLengthTable<T>() );
      } 
      return std::shared_ptr<ITypedTable<T>>( new Table<T>(capacity) );
    }

    /**
     * Grows the current table. We move-construct another new dynamic table from
     * "this", and put it at the first position of "this" table (which is
     * conceptually equivalent as creating a new tree level).
     * */
    void grow() noexcept {
      Table* t = new Table(std::move(*this));
      for(uint32_t i = 0; i < kArity; ++i) {
        m_blocks[i];
      }
      m_blocks[0] = std::shared_ptr<ITypedTable<T>>(t);
      m_size = m_blocks[0]->size();
      m_blockCapacity = m_blocks[0]->getCapacity();
      m_capacity = m_blockCapacity*kArity;
      m_currentBlock = 0;
    }

    /** 
     * Represents the current size of the table (the number of elements it
     * contains)*/
    uint64_t  m_size = 0;

    /**
     * The total capacity of the table (the number of elements it can contain)
     **/
    uint64_t  m_capacity = kArity*minCapacity;

    /**
     * The capacity of each of the sub tables 
     **/
    uint64_t  m_blockCapacity = minCapacity;

    /**
     * The current subtable where elements are being appended
     **/
    uint32_t  m_currentBlock = 0;

    /**
     * The array holding the subtables 
     **/
    std::array<std::shared_ptr<ITypedTable<T>>,kArity>  m_blocks;
};
SMILE_NS_END
#endif
