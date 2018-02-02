add_definitions(${DEFAULT_DEFINES})

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
