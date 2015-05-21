project(text)

find_package(ImageMagick COMPONENTS Magick++)

include(${CMAKE_SOURCE_DIR}/cmake/CMakeLists_common_qt.txt)

include_directories(SYSTEM ${ImageMagick_Magick++_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-global-constructors -Wno-missing-prototypes -Wno-sign-conversion -Wno-old-style-cast -Wno-float-equal -Wno-reserved-id-macro")

target_link_libraries(text ${ImageMagick_LIBRARIES})