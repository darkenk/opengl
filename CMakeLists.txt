project(opengl)

cmake_minimum_required(VERSION 2.8.11)

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${opengl_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# determine which compiler is used
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # using Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} "-Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors -Wno-implicit-fallthrough")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces -Wno-padded")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # using GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")

endif()

# Common lib dependencies
find_package(OpenGL REQUIRED)
if (UNIX)
    find_package(GLEW 1.10.0 REQUIRED)
    find_package(GLM 0.9.5.3 REQUIRED)
elseif(WIN32)
    include(${CMAKE_SOURCE_DIR}/external/CMakeLists.txt)
endif()

# cpp style checker
find_package(vera++ QUIET)
if(vera++_FOUND)
    include(${VERA++_USE_FILE})
endif()

set(USED_LIBRARIES "${OPENGL_LIBRARIES};${GLEW_LIBRARIES};pthread")
set(USED_INCLUDES "${GLM_INCLUDES};${GLEW_INCLUDE_DIRS}")

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
