
#ifndef _STORAGE_FILE_STORAGE_H_
#define _STORAGE_FILE_STORAGE_H_ 

#include "base/platform.h"
#include "storage/sequential_storage.h"
#include <fstream>

SMILE_NS_BEGIN

class FileStorage : public ISequentialStorage {
  public:
    SMILE_NON_COPYABLE(FileStorage)

    FileStorage() noexcept;

    virtual ~FileStorage() noexcept;

    storageError_t open( const std::string& path ) noexcept override;

    storageError_t create( const std::string& path, const SequentialStorageConfig& config, const bool overwrite = false ) noexcept override;

    storageError_t close() noexcept override;

    storageError_t reserve( const uint32_t numExtents, extentId_t& extents ) noexcept override;

    storageError_t read( char* data, const extentId_t extent ) noexcept override;

    storageError_t write( const char* data, const extentId_t extent ) noexcept override;

    uint64_t size() const noexcept override;

    const SequentialStorageConfig& config() const noexcept override;

  private:

    /**
     * Gets the extent size in bytes
     *
     * @return The extent size in bytes
     **/
    uint32_t getExtentSize() const noexcept;

    /**
     * Converts a position in a file in bytes to their extentId counterpart
     * where this byte belongs to
     * @param bytes in bytes The bytes to convert
     * @return The extentId
     **/
    extentId_t bytesToExtent( uint64_t bytes ) const noexcept;

    /**
     * Converts an extent to its equivalent position in bytes
     * @param in extentId The extent to convert
     * @return the position in bytes equivalent to the extent.
     */
    uint64_t extentToBytes( const extentId_t extent ) const noexcept;


    // The file
    std::fstream    m_file;

    // The size of the file in extents;
    extentId_t      m_size;

    // The basic file modes
    std::ios_base::openmode m_flags;

    // A buffer used to initialize new extents in the file when it grows
    std::vector<char>       m_extentFiller;

    // The storage configuration data
    SequentialStorageConfig m_config;
};

SMILE_NS_END

#endif /* ifndef _STORAGE_FILE_STORAGE_H_ */

