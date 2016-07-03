add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})


add_subdirectory(common)

add_library(smile STATIC)

target_link_libraries(smile
    common
)
