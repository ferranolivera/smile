add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

add_subdirectory(base)
add_subdirectory(storage)
add_subdirectory(memory)

add_library(smile STATIC)

target_link_libraries(smile
    base
    storage
    memory
)
