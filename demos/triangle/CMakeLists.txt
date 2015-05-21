project(triangle)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-non-virtual-dtor -Wno-weak-vtables")

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common_qt.txt)
