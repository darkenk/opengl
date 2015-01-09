project(light_demo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# show only file name instead of absolute path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_CURRENT_SOURCE_DIR}/,,$(abspath \$<))\"'")

set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

qt5_wrap_ui(UI_HEADERS mainwindow.ui)
qt5_add_resources(QRC_SRC QDarkStyleSheet/qdarkstyle/style.qrc)
set_source_files_properties(${QRC_SRC} PROPERTIES COMPILE_FLAGS "-Wno-error -Wno-everything")
aux_source_directory(. SRC_FILES)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${UI_HEADERS} ${QRC_SRC} $<TARGET_OBJECTS:opengl_lib>)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    ${USED_LIBRARIES})
