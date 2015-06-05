project(opengl)

cmake_minimum_required(VERSION 3.2.1)

# set build type to debug as it is in development phase
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE DEBUG CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

# enable verbose building
if (NOT CMAKE_VERBOSE_MAKEFILE)
    set(CMAKE_VERBOSE_MAKEFILE ON CACHE STRING "Enable compile verbose mode by default" FORCE)
endif()

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${opengl_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# Common lib dependencies
find_package(OpenGL REQUIRED)
option(INTERNAL_LIBS "use glm and glew from external folder" OFF)
if (WIN32)
    set(INTERNAL_LIBS 1)
endif()

include(${CMAKE_SOURCE_DIR}/external/CMakeLists.txt)
if (NOT GLEW_FOUND)
    find_package(GLEW 1.10.0 REQUIRED)
endif()
if (NOT GLM_FOUND)
    find_package(GLM 0.9.5.3 REQUIRED)
endif()
if (NOT ASSIMP_FOUND)
    find_package(ASSIMP REQUIRED)
endif()

set(USED_LIBRARIES "${OPENGL_LIBRARIES};${GLEW_LIBRARIES};${ASSIMP_LIBRARIES};pthread")
set(USED_INCLUDES "${GLM_INCLUDE_DIRS};${GLEW_INCLUDE_DIRS};${ASSIMP_INCLUDE_DIRS}")

# cpp style checker
find_package(vera++ QUIET)
if(vera++_FOUND)
    include(${VERA++_USE_FILE})
endif()

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(src)

option(ENABLE_DEMOS "enable demos" ON)
if(ENABLE_DEMOS)
    add_subdirectory(demos)
endif()

option(ENABLE_TESTS "enable tests" OFF)
if(ENABLE_TESTS)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin_tests)
    add_subdirectory(tests)
endif()
