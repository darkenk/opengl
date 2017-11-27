find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(GLAD REQUIRED)

aux_source_directory(. SRC)
set(EXEC_NAME geometry)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(${EXEC_NAME} ${SRC})
target_link_libraries(${EXEC_NAME} Qt5::Widgets Qt5::OpenGL opengl_lib glwidget)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/demos/glwidget)
target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(${EXEC_NAME} SYSTEM PRIVATE ${GLAD_INCLUDE_DIR})
target_include_directories(${EXEC_NAME} PRIVATE ${DK_UTILS_INCLUDE_DIRS})
