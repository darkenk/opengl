find_package(GLAD REQUIRED)

file(GLOB SRC *.cpp units/*.cpp models/*.cpp utils/*.cpp)
file(GLOB INC *.hpp units/*.hpp models/*.hpp utils/*.hpp)

add_library(opengl_lib STATIC ${SRC})
target_include_directories(opengl_lib SYSTEM PRIVATE ${GLAD_INCLUDE_DIR})
