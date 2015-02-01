project(qt)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    # automoc generate some code which doesn't compile and thus this flag
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-undefined-reinterpret-cast -fPIC")
elseif(${CMAKE_CXX_COMPILER_ID} MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -Wno-zero-as-null-pointer-constant")
endif()
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)

include_directories(SYSTEM ${Qt5Widgets_INCLUDE_DIRS})
include_directories(SYSTEM ${Qt5OpenGL_INCLUDE_DIRS})
include_directories(SYSTEM ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
qt5_wrap_ui(UI_HEADERS ${UI_FILES})
qt5_add_resources(QRC_SRC QDarkStyleSheet/qdarkstyle/style.qrc)
file(GLOB SRC_FILES *.cpp)
file(GLOB INC_FILES *.hpp)

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|GNU")
    set_source_files_properties(${QRC_SRC} PROPERTIES COMPILE_FLAGS "-Wno-error -Wno-missing-declarations")
endif()

add_library(${PROJECT_NAME} OBJECT ${SRC_FILES} ${UI_HEADERS} ${QRC_SRC})

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common.txt)
