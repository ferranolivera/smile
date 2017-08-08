#include_directories(${SPA_BENCH_INCLUDE_DIR})
#include_directories(${Boost_INCLUDE_DIR})

add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

add_library(data STATIC 
  graph.cpp
  graph_template_defs.inl
  graph.h
  immutable_table.h
  immutable_table.cpp
  index.h
  types.h
  types.cpp
  types_traits.h
  types_traits.cpp
)

target_link_libraries(data base ${Boost_LIBRARIES})

