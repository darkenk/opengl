# GLEW
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glew)
set(GLEW_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/glew/include)
set(GLEW_LIBRARIES "glew")

if(${CMAKE_CXX_COMPILER_ID} MATCHES "Clang|GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLEW_STATIC")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /DGLEW_STATIC")
else()
    error(FATAL_ERROR "Not supported compiler, please add needed code to external CMakeLists.txt")
endif()

# GLM
set(GLM_INCLUDES ${CMAKE_SOURCE_DIR}/external/glm/)
