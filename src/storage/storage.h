
#ifndef _SMILE_STORAGE_STORAGE_H
#define _SMILE_STORAGE_STORAGE_H 

#include "base/platform.h"

SMILE_NS_BEGIN

#include "base/platform.h"
#include "storage/types.h"
#include <vector>

class IStorage {

    public:
        IStorage() = default;
        virtual ~IStorage() = default;

        /**
         * Initializes the file storage
         * @return fale if there was an error. true otherwise
         */
        virtual bool Init() noexcept = 0;

        /**
         * Reserve an extent 
         * @param extent The reserved extent id
         * @return false if there was an error. true otherwise
         */
        virtual bool Reserve( extentId& extent ) noexcept = 0;

        /**
         * Reserve a set of extents
         * @param numExtents The number of extent to reserve
         * @param extents The reserved extents
         * @return false if there was an error. true otherwise
         **/
        virtual bool Reserve( uint32_t numExtents, std::vector& extents ) noexcept = 0;

        /**
         * Releases the given extent
         * @param extent The id of the extent to release
         * @return false if the release was not successful. true otherwise
         **/
        virtual bool Release( const extentId extent ) noexcept = 0;


        /**
         * Releases a set of extents
         * @param exetents The extents to release
         * @return false if release was unsuccessful. true otherwise.
         * */
        virtual bool Release( std::vector& extents ) noexcept = 0;

        /**
         * Locks an extent into a buffer
         * @param data The buffer where the extent will be locked
         * @param extent The extent to lock
         * @return false if the lock was not successful. true otherwise
         * */
        virtual bool Lock( char* data, extentId extent ) noexcept = 0;

        /**
         * Unlocks the given extent
         * @param data The buffer where the extent was locked
         * @param extent The extent to unlock
         * @param drity Whether to write the extent to disk or not.
         * @return false if the unlock was unsuccessful. true otherwise.
         **/
        virtual bool Unlock( char* data, extentId extent, bool dirty ) noexcept = 0;

};

SMILE_NS_END

#endif /* ifndef _SMILE_STORAGE_STORAGE_H */

