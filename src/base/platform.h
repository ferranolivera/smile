

#ifndef _BASE_PLATFORM_H_
#define _BASE_PLATFORM_H_ 

#include <base/macros.h>
#include <base/types.h>
#include <memory>


SMILE_NS_BEGIN

class Platform {
    public:
        const Platform& getInstance() const noexcept; 
};

SMILE_NS_END

#endif /* ifndef _BASE_PLATFORM_H_ */
