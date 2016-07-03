#
# sparkseecore
#
add_subdirectory(common)
#
# sparksee library
#
add_definitions(${DEFAULT_DEFINES})
include_directories(${SMILE_INCLUDE_DIR})

set(SMILE_COMMON_SOURCES

)


target_link_libraries(smile
    common
)
