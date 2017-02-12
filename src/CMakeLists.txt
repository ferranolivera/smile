add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})


add_subdirectory(base)
add_subdirectory(storage)

add_library(smile STATIC)

target_link_libraries(smile
    base
    storage
)
