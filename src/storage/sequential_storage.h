
#ifndef _SMILE_STORAGE_STORAGE_H
#define _SMILE_STORAGE_STORAGE_H 

#include "../base/base.h"
#include "types.h"
#include <vector>
#include <string>

SMILE_NS_BEGIN

class ISequentialStorage {
  public:

    struct SequentialStorageConfig {
      uint32_t  m_extentSizeKB = 64;
    };


    ISequentialStorage() noexcept = default;
    virtual ~ISequentialStorage() noexcept = default;

    /**
     * Opens the file storage at the given path
     * @param in the path to the storage
     * @return true if the storage was opened correctly
     **/
    virtual ErrorCode open( const std::string& path ) noexcept = 0;

    /**
     * Opens the file storage at the given path
     * @param in the path to the storage to create
     * @return in the configuration of the storage
     **/
    virtual ErrorCode create( const std::string& path, const SequentialStorageConfig& config, const bool overwrite = false) noexcept = 0;

    /**
     * Closes the storage
     * @return true if the closing was successful
     **/
    virtual ErrorCode close() noexcept = 0;

    /**
     * Reserve a set of extents
     * @param in numExtents The number of extent to reserve
     * @param out extentId The first reserved extentId
     * @return false if there was an error. true otherwise
     **/
    virtual ErrorCode reserve( const uint32_t numExtents, extentId_t& extents ) noexcept = 0;

    /**
     * Locks an extent into a buffer
     * @param in data The buffer where the extent will be locked
     * @param in extent The extent to lock
     * @return false if the lock was not successful. true otherwise
     * */
    virtual ErrorCode read( char* data, const extentId_t extent ) noexcept = 0;

    /**
     * Unlocks the given extent
     * @param in data The buffer where the extent was locked
     * @param in extent The extent to unlock
     * @param in drity Whether to write the extent to disk or not.
     * @return false if the unlock was unsuccessful. true otherwise.
     **/
    virtual ErrorCode write( const char* data, const extentId_t extent ) noexcept = 0;



    /**
     * Gets the current size of the storage in extents
     * @return The current size of the storage in extents
     **/
    virtual uint64_t size() const noexcept = 0;


    /**
     * Gets the configuration of the storage
     * @return The configuration of the storage
     * */
    virtual const SequentialStorageConfig& config() const noexcept = 0;
};

SMILE_NS_END

#endif /* ifndef _SMILE_STORAGE_STORAGE_H */

