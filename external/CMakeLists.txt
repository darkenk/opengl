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
set(GLM_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/glm/)

# GTest
#add_subdirectory(${CMAKE_SOURCE_DIR}/external/gtest)
# gtest is built in gmock

set(GTEST_FOUND 1)
set(GTEST_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/gtest/include)
set(GTEST_LIBRARIES libgtest.a)
set(GTEST_MAIN_LIBRARIES libgtest_main.a)
set(GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})
link_directories(${CMAKE_BINARY_DIR}/external/gmock/gtest/)

# GMock
add_subdirectory(${CMAKE_SOURCE_DIR}/external/gmock)
set(GMOCK_FOUND 1)
set(GMOCK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/external/gmock/include)
set(GMOCK_LIBRARIES libgmock.a)
set(GMOCK_MAIN_LIBRARIES libgmock_main.a)
set(GMOCK_BOTH_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_MAIN_LIBRARIES})

# GlMock
add_subdirectory(${CMAKE_SOURCE_DIR}/external/glmock)

