

add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

add_library(common STATIC
  platform.cpp
)

target_link_libraries(common)
