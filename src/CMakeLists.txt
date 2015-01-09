set(CMAKE_INCLUDE_CURRENT_DIR ON)

# show only file name instead of absolute path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_CURRENT_SOURCE_DIR}/,,$(abspath \$<))\"'")

find_package(GLUT REQUIRED)

include_directories(SYSTEM ${OPENGL_INCLUDE_DIRS})
include_directories(SYSTEM ${GLEW_INCLUDE_DIRS})
include_directories(SYSTEM ${GLUT_INCLUDE_DIRS})
include_directories(SYSTEM ${GLM_INCLUDE_DIRS})

file(GLOB SRC_FILES *.cpp)
file(GLOB MAIN_FILE "main.cpp")
file(GLOB SHADER_FILES shaders/*.glsl)
set_source_files_properties(buffer-impl.cpp PROPERTIES COMPILE_FLAGS -Wno-header-hygiene)
set_source_files_properties(utils.cpp PROPERTIES COMPILE_FLAGS -Wno-global-constructors)

list(REMOVE_ITEM SRC_FILES ${MAIN_FILE})
add_library(opengl_lib OBJECT ${SRC_FILES})

add_executable(${PROJECT_NAME} ${MAIN_FILE} ${SHADER_FILES} $<TARGET_OBJECTS:opengl_lib>)

target_link_libraries(${PROJECT_NAME}
    ${GLUT_LIBRARIES}
    ${USED_LIBRARIES})

add_custom_target(
    copy_shaders ALL
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/shaders/* ${EXECUTABLE_OUTPUT_PATH}/
)

add_custom_target(run
    COMMAND opengl
    COMMENT "Run with ${CMAKE_BUILD_TYPE} configuration"
)
