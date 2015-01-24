include_directories(SYSTEM ${OPENGL_INCLUDE_DIRS})
include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
include_directories(SYSTEM ${GLM_INCLUDE_DIRS})

file(GLOB SRC_FILES *.cpp units/*.cpp)
file(GLOB INC_FILES *.hpp units/*.hpp)
file(GLOB SHADER_FILES shaders/*.glsl)
set_source_files_properties(buffer-impl.cpp PROPERTIES COMPILE_FLAGS -Wno-header-hygiene)
set_source_files_properties(utils.cpp PROPERTIES COMPILE_FLAGS -Wno-global-constructors)

add_library(opengl_lib OBJECT ${SRC_FILES})

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common.txt)
