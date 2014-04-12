set(CMAKE_INCLUDE_CURRENT_DIR ON)
file(GLOB opengl_SOURCES *.cpp)
add_executable(opengl ${opengl_SOURCES})
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Look for the header file.
find_path(FREEGLUT_INCLUDE_DIRS NAMES GL)

# Look for the library.
find_library(FREEGLUT_LIBRARIES NAMES glut)

include_directories( ${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${FREEGLUT_INCLUDE_DIRS})
target_link_libraries(opengl ${OPENGL_LIBRARIES} ${FREEGLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLUT_LIBRARIES} pthread)

file(GLOB shader_SOURCES shaders/*)

file(COPY ${shader_SOURCES} DESTINATION ${EXECUTABLE_OUTPUT_PATH})

add_custom_target(run
	COMMAND opengl
	COMMENT "Run with ${CMAKE_BUILD_TYPE} configuration"
)
