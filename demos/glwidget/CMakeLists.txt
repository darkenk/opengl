find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(GLAD REQUIRED)

aux_source_directory(. SRC)
set(LIB_NAME glwidget)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_library(${LIB_NAME} STATIC ${SRC})
target_link_libraries(${LIB_NAME} Qt5::Widgets Qt5::OpenGL ${GLAD_LIBRARY})
target_include_directories(${LIB_NAME} SYSTEM PRIVATE ${GLAD_INCLUDE_DIR})
target_include_directories(${LIB_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
