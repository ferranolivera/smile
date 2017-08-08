add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

add_library(base STATIC
  platform.h
  platform.cpp
  base.h
  error.h
  error.cpp
  macros.h
  types.h
  types_traits.h
  types_utils.h
  types_utils.cpp
)

target_link_libraries(base)
