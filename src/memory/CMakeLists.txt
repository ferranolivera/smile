
add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

if (UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-rtti -fno-exceptions")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-rtti -fno-exceptions")
endif (UNIX)

add_library(memory STATIC
  types.h
  buffer.h
  buffer.cpp
  buffer_pool.h
  buffer_pool.cpp
)

target_link_libraries(memory storage base)

#add_subdirectory(tests)
