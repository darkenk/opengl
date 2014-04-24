enable_testing()

function(compile_tests test_sources additional_sources additional_libs file_postfix)
    foreach(test_source ${test_sources})
        string(REPLACE "${file_postfix}.cpp" "" test_name ${test_source})
        set(test_name "${test_name}_test")
        string(REPLACE ${file_postfix} "" source_file ${test_source})
        add_executable(${test_name} ${test_source} ../src/${source_file} ${additional_sources})
        target_link_libraries(${test_name} gtest ${additional_libs} pthread )
        add_test(NAME ${test_name} COMMAND ${test_name})
        set(target "run_${test_name}")
        add_custom_target(${target}
            COMMAND ${test_name}
            COMMENT "Run with ${CMAKE_BUILD_TYPE} configuration"
        )
    endforeach()
endfunction()

file(GLOB test_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cpp)
compile_tests("${test_SOURCES}" "" "gtest_main" "_test")

include_directories(${CMAKE_SOURCE_DIR}/../glmock)
link_directories(${CMAKE_SOURCE_DIR}/../glmock)

file(GLOB mock_test_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test_mock.cpp)
compile_tests("${mock_test_SOURCES}" "../src/exceptions.cpp" "gmock;gmock_main;glmock" "_test_mock")
