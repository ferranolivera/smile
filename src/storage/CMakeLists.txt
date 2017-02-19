

add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

if (UNIX)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-rtti -fno-exceptions")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-rtti -fno-exceptions")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-rtti -fno-exceptions")
endif (UNIX)

add_library(storage STATIC
  error.h
  file_storage.cpp
  file_storage.h
  sequential_storage.h
  types.h
)

target_link_libraries(storage)

add_subdirectory(tests)
