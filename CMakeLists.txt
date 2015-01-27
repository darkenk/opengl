project(opengl)

cmake_minimum_required(VERSION 2.8.11)

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${opengl_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS")
# determine which compiler is used
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    # using Clang
    set(COMPILER_FLAGS "-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic")
    set(COMPILER_FLAGS "${COMPILER_FLAGS} -Wno-exit-time-destructors -Wno-implicit-fallthrough")
    set(COMPILER_FLAGS "${COMPILER_FLAGS} -Wno-missing-braces -Wno-padded")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    # using GCC
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILER_FLAGS}")

# Common lib dependencies
find_package(OpenGL REQUIRED)
find_package(GLEW 1.10.0 REQUIRED)
find_package(GLM 0.9.5.3 REQUIRED)
#include(FindGLM)
# cpp style checker
find_package(vera++ QUIET)
if(vera++_FOUND)
    include(${VERA++_USE_FILE})
endif()

set(USED_LIBRARIES "${OPENGL_LIBRARIES};${GLEW_LIBRARIES};pthread")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(src)

option(ENABLE_DEMOS "enable demos" ON)
if(ENABLE_DEMOS)
    add_subdirectory(demos)
endif()

option(ENABLE_DEMOS "enable tests" OFF)
if(ENABLE_TESTS)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin_tests)
    add_subdirectory(tests)
endif()
