project(opengl)

cmake_minimum_required(VERSION 2.8.11)

# Appends the cmake/modules path inside the MAKE_MODULE_PATH variable which stores the
# directories of additional CMake modules (ie. MacroOutOfSourceBuild.cmake):
set(CMAKE_MODULE_PATH ${opengl_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

# determine which compiler is used
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    # using Clang
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS -D__cplusplus=201103L")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-exit-time-destructors -Wno-implicit-fallthrough")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-missing-braces -Wno-padded")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    # using GCC
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion -Wctor-dtor-privacy -Wdisabled-optimization")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wdouble-promotion -Wfloat-equal -Wformat=2 -Winit-self")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winvalid-pch -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5 -Wtrampolines -Wundef -Wunsafe-loop-optimizations")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wvector-operation-performance -Wzero-as-null-pointer-constant")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")

endif()

# Common lib dependencies
find_package(OpenGL REQUIRED)
option(INTERNAL_LIBS "use glm and glew from source" OFF)
if (WIN32)
    set(INTERNAL_LIBS 1)
endif()
if (INTERNAL_LIBS)
    include(${CMAKE_SOURCE_DIR}/external/CMakeLists.txt)
elseif (UNIX)
    find_package(GLEW 1.10.0 REQUIRED)
    find_package(GLM 0.9.5.3 REQUIRED)
endif()

# cpp style checker
find_package(vera++ QUIET)
if(vera++_FOUND)
    include(${VERA++_USE_FILE})
endif()

set(USED_LIBRARIES "${OPENGL_LIBRARIES};${GLEW_LIBRARIES};pthread")
set(USED_INCLUDES "${GLM_INCLUDE_DIRS};${GLEW_INCLUDE_DIRS}")

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
