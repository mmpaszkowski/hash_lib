# Works with 3.16
cmake_minimum_required(VERSION 3.16)

project(hash_lib
        VERSION 0.1.0
        DESCRIPTION "C++ implementation of hash algorithms"
        LANGUAGES CXX)

# Only do these if this is the main project, and not if it is included through
# add_subdirectory
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_STANDARD 20)
    set(BUILD_TESTING TRUE)

    # Let's ensure -std=c++xx instead of -std=g++xx
    set(CMAKE_CXX_EXTENSIONS OFF)
    add_compile_options(-Wall -Wextra -pedantic -Werror)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if (Doxygen_FOUND)
        add_subdirectory(docs)
    else ()
        message(STATUS "Doxygen not found, not building docs")
    endif ()
endif ()

# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was not added until CMake 3.14
include(FetchContent)

# Accumulator library This is header only, so could be replaced with git
# submodules or FetchContent
find_package(Boost REQUIRED)

add_subdirectory(src)
add_subdirectory(apps)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif ()
