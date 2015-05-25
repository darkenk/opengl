include_directories(SYSTEM ${OPENGL_INCLUDE_DIRS})

file(GLOB SRC_FILES *.cpp units/*.cpp models/*.cpp utils/*.cpp)
file(GLOB INC_FILES *.hpp units/*.hpp models/*.hpp utils/*.hpp)
file(GLOB SHADER_FILES shaders/*.glsl)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    set_source_files_properties(utils/utils.cpp PROPERTIES COMPILE_FLAGS -Wno-global-constructors)
endif()

add_library(opengl_lib OBJECT ${SRC_FILES} ${INC_FILES} ${SHADER_FILES})

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common.txt)
