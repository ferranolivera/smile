cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(SMILE)
#
# SPARKSEE version (major.minor.release)
#
set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_RELEASE "1")

#
# RELEASE is the default build type
#
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RELEASE)
endif(NOT CMAKE_BUILD_TYPE)

#
# Check 64bits architecture
#
if(CMAKE_SIZEOF_VOID_P MATCHES "4")
    set(ARCHTYPE "32")
else(CMAKE_SIZEOF_VOID_P MATCHES "4")
    set(ARCHTYPE "64")
endif(CMAKE_SIZEOF_VOID_P MATCHES "4")

#
# Set default definitions
#
set(DEFAULT_DEFINES
)


#
# Set default platform definitions
#
if(UNIX)
  set(LINUX 1)
  set(SO "linux")
  set(UUID_LIB "uuid")
  set(RUNTIME_LIB "rt")
else(WIN32)
    set(SO "OTHER")
endif(WIN32)

#
# Set project paths
#
set(SMILE_DIR "${SMILE_SOURCE_DIR}/sparksee")
set(SMILE_INCLUDE_DIR "${SMILE_SOURCE_DIR}/")

if (UNIX)
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g -gdb -O3 -NDEBUG -fPIC")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -g -gdb -fPIC")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -gdb -fPIC")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -gdb -O3 -fPIC")
endif (UNIX)



#
# Summary messages
#
message(STATUS "SMILE v" ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_RELEASE})
message(STATUS "PLATFORM ${SO} ${ARCHTYPE}bits")
message(STATUS "BUILD_TYPE ${CMAKE_BUILD_TYPE}")
message(STATUS "DEFAULT DEFINES: " ${DEFAULT_DEFINES})
if(CMAKE_BUILD_TYPE STREQUAL RELEASE)
    message(STATUS "CXX: " ${CMAKE_CXX_FLAGS_RELEASE})
else(CMAKE_BUILD_TYPE STREQUAL RELEASE)
    message(STATUS "CXX: " ${CMAKE_CXX_FLAGS_DEBUG})
endif(CMAKE_BUILD_TYPE STREQUAL RELEASE)
message(STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME})
message(STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR})

add_subdirectory(src)
