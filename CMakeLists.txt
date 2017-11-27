cmake_minimum_required(VERSION 3.5.1)
project(opengl)

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

find_package(dk_utils REQUIRED)

include(dk_compiler_flags)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLM_FORCE_RADIANS")
add_subdirectory(src)
add_subdirectory(demos)
add_subdirectory(test)
