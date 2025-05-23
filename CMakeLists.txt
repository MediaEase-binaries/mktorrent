cmake_minimum_required(VERSION 3.20)
project(mktorrent
    VERSION 1.5.0
    DESCRIPTION "A simple command-line utility to create BitTorrent metainfo files, written in C"
    HOMEPAGE_URL "https://github.com/tomcj71/mktorrent"
    LANGUAGES C
)
include_directories(${PROJECT_SOURCE_DIR}/include)
# Default to Release if no build type is specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Options
option(MKTORRENT_OPENSSL "Use OpenSSL's SHA-1 implementation" ON)
option(MKTORRENT_PTHREADS "Enable POSIX threads for faster hashing" ON)
option(MKTORRENT_LONG_OPTIONS "Enable GNU-style long options" ON)
option(MKTORRENT_NO_HASH_CHECK "Disable hash-size consistency check" OFF)
option(MKTORRENT_USE_GITREV_VERSION "Include git commit in version string" OFF)
option(MKTORRENT_TEST "Enable test suite" OFF)
option(MKTORRENT_TEST_PERFORMANCE "Enable performance tests" OFF)

set(MKTORRENT_MAX_OPENFD 100 CACHE STRING "Max open files during scan")
set(MKTORRENT_PROGRESS_PERIOD 200000 CACHE STRING "Progress update interval in μs")

# Git revision
if(MKTORRENT_USE_GITREV_VERSION)
    find_package(Git QUIET)
    if(GIT_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE GIT_REV
            OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        set(MKTORRENT_VERSION "${PROJECT_VERSION}-${GIT_REV}")
    else()
        set(MKTORRENT_VERSION "${PROJECT_VERSION}")
    endif()
else()
    set(MKTORRENT_VERSION "${PROJECT_VERSION}")
endif()

# Dependencies
if(MKTORRENT_OPENSSL)
    find_package(OpenSSL REQUIRED)
endif()

if(MKTORRENT_PTHREADS)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

# Source files
add_executable(mktorrent
    src/main.c
    src/ftw.c
    src/init.c
    src/ll.c
    src/msg.c
    src/output.c
    $<$<BOOL:${MKTORRENT_PTHREADS}>:src/hash_pthreads.c>
    $<$<NOT:$<BOOL:${MKTORRENT_PTHREADS}>>:src/hash.c>
    $<$<NOT:$<BOOL:${MKTORRENT_OPENSSL}>>:src/sha1.c>
)

target_compile_features(mktorrent PRIVATE c_std_99)
target_compile_options(mktorrent PRIVATE -Wall -Wextra -Wpedantic)

target_compile_definitions(mktorrent PRIVATE
    _FILE_OFFSET_BITS=64
    VERSION="${MKTORRENT_VERSION}"
    BUILD_CFG="${CMAKE_BUILD_TYPE}"
    $<$<BOOL:${MKTORRENT_PTHREADS}>:USE_PTHREADS>
    $<$<BOOL:${MKTORRENT_OPENSSL}>:USE_OPENSSL>
    $<$<BOOL:${MKTORRENT_LONG_OPTIONS}>:USE_LONG_OPTIONS>
    $<$<BOOL:${MKTORRENT_NO_HASH_CHECK}>:NO_HASH_CHECK>
    MAX_OPENFD=${MKTORRENT_MAX_OPENFD}
    PROGRESS_PERIOD=${MKTORRENT_PROGRESS_PERIOD}
)

target_link_libraries(mktorrent PRIVATE
    $<$<BOOL:${MKTORRENT_OPENSSL}>:OpenSSL::Crypto>
    $<$<BOOL:${MKTORRENT_PTHREADS}>:Threads::Threads>
)

# Install
include(GNUInstallDirs)
install(TARGETS mktorrent RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(FILES man/mktorrent.1 DESTINATION ${CMAKE_INSTALL_MANDIR}/man1)

# Test suite
if(MKTORRENT_TEST)
    find_package(Python3 COMPONENTS Interpreter REQUIRED)
    set(TEST_ENV_VARS
        MKTORRENT_BINARY=$<TARGET_FILE:mktorrent>
        PERFORMANCE_TESTS=$<IF:$<BOOL:${MKTORRENT_TEST_PERFORMANCE}>,1,0>
        PERFORMANCE_LARGE_TESTS=$<IF:$<BOOL:${MKTORRENT_TEST_PERFORMANCE}>,1,0>
    )
    
    add_custom_target(test
        COMMAND ${CMAKE_COMMAND} -E env
            ${TEST_ENV_VARS}
            MKTORRENT=$<TARGET_FILE:mktorrent>
            /bin/bash ${CMAKE_SOURCE_DIR}/tests/run_tests.sh
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        DEPENDS mktorrent
        COMMENT "Running MKTorrent test suite"
    )
    
    add_custom_target(test-data
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/tests/data
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/tests/results
        COMMENT "Creating test data directories"
    )
    
    add_dependencies(test test-data)
endif()
