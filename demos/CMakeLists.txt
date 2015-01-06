project(light_demo)

set(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt5_wrap_ui(UI_HEADERS mainwindow.ui)
qt5_add_resources(QRC_SRC QDarkStyleSheet/qdarkstyle/style.qrc)
set_source_files_properties(${QRC_SRC} PROPERTIES COMPILE_FLAGS "-Wno-error -Wno-everything")
add_executable(${PROJECT_NAME} light_demo.cpp mainwindow.cpp ${UI_HEADERS} ${QRC_SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
