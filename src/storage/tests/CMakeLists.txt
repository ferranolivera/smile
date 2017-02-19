include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${SMILE_INCLUDE_DIR})

add_custom_target(check-storage COMMAND ${CMAKE_CTEST_COMMAND} -R "-storage")

set(TEST_PROGRAMS
  file_storage_test 
)

foreach(program ${TEST_PROGRAMS})
  add_executable(${program} 
    ${program}.cpp
    )
  target_link_libraries(${program}
    ${GTEST_LIBRARIES}
    base
    storage
    )
  set_target_properties(${program}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${SMILE_TEST_OUTPUT_DIR}/storage"
    )
  add_test(${program}-storage "${SMILE_TEST_OUTPUT_DIR}/storage/${program}")
  add_dependencies(check-storage ${program})
endforeach(program)


