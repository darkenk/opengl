enable_testing()
find_package(GTest REQUIRED)
find_package(GLAD REQUIRED)
find_package(EGL REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    SYSTEM ${GLAD_INCLUDE_DIR}
    ${DK_UTILS_INCLUDE_DIRS})

set(GL_LIBS ${GLAD_LIBRARY} ${EGL_LIBRARIES} ${OPENGL_LIBRARIES})

add_gtest(shaderprogram_test SRC ../src/shaderprogram.cpp ../src/utils/exceptions.cpp LIBS ${GL_LIBS})
add_gtest(buffer_test LIBS ${GL_LIBS})
add_gtest(vertex_test)
add_gtest(camera_test SRC ../src/camera.cpp)
