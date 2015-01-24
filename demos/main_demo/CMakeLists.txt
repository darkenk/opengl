project(main_demo)
find_package(GLUT REQUIRED)

file(GLOB SRC_FILES *.cpp)
file(GLOB INC_FILES *.hpp)

add_executable(${PROJECT_NAME} ${SRC_FILES} ${SHADER_FILES} $<TARGET_OBJECTS:opengl_lib>)

target_link_libraries(${PROJECT_NAME}
    ${GLUT_LIBRARIES}
    ${USED_LIBRARIES})

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common.txt)
