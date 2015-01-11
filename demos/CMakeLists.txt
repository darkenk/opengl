project(light_demo)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# show only file name instead of absolute path
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_CURRENT_SOURCE_DIR}/,,$(abspath \$<))\"'")

# automoc generate some code which doesn't compile and thus this flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-reinterpret-cast")
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src/)

qt5_wrap_ui(UI_HEADERS mainwindow.ui valueslider.ui)
qt5_add_resources(QRC_SRC QDarkStyleSheet/qdarkstyle/style.qrc)
set_source_files_properties(${QRC_SRC} PROPERTIES COMPILE_FLAGS "-Wno-error -Wno-everything")
file(GLOB SRC_FILES *.cpp)
file(GLOB INC_FILES *.hpp)
add_executable(${PROJECT_NAME} ${SRC_FILES} ${UI_HEADERS} ${QRC_SRC} $<TARGET_OBJECTS:opengl_lib>)

target_link_libraries(${PROJECT_NAME}
    Qt5::Widgets
    Qt5::OpenGL
    ${USED_LIBRARIES})

#cpp checker
if(vera++_FOUND)
    add_vera_targets(${SRC_FILES} ${INC_FILES}
        NAME "demos"
        NAME_ALL "demos_report"
        RECURSE
        ROOT ${CMAKE_SOURCE_DIR}/vera)
endif()
