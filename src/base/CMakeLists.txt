add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

add_library(base STATIC
  platform.cpp
)

target_link_libraries(base)
