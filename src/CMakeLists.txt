set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB opengl_SOURCES *.cpp shaders/*.glsl)
set_source_files_properties(buffer-impl.cpp PROPERTIES COMPILE_FLAGS -Wno-header-hygiene)
set_source_files_properties(utils.cpp PROPERTIES COMPILE_FLAGS -Wno-global-constructors)
add_executable(opengl ${opengl_SOURCES})
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
include(FindGLM)

# Look for the header file.
find_path(FREEGLUT_INCLUDE_DIRS NAMES GL)

# Look for the library.
find_library(FREEGLUT_LIBRARIES NAMES glut)

# show only file name instead of absolute path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
    ${FREEGLUT_INCLUDE_DIRS}
    ${GLM_INCLUDE_DIRS})
target_link_libraries(opengl
    ${OPENGL_LIBRARIES}
    ${FREEGLUT_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${GLUT_LIBRARIES} pthread)

file(GLOB shader_SOURCES shaders/*)

add_custom_target(
    copy_shaders ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/shaders/* ${EXECUTABLE_OUTPUT_PATH}/
)

add_custom_target(run
    COMMAND opengl
    COMMENT "Run with ${CMAKE_BUILD_TYPE} configuration"
)
