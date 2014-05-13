enable_testing()

function(compile_test test_source additional_sources additional_libs)
    set(file_postfix "_test")
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
endfunction()

include_directories(${CMAKE_SOURCE_DIR}/../glmock)
link_directories(${CMAKE_SOURCE_DIR}/../glmock)

compile_test(camera_test.cpp "" "gtest_main")
compile_test(shaderloader_test.cpp "../src/exceptions.cpp" "gmock;gmock_main;glmock")
compile_test(simpleobject_test.cpp "mockshaderloader.cpp;../src/exceptions.cpp" "gmock;gmock_main;glmock")
compile_test(terrain_test.cpp "" "gtest_main")
compile_test(cube_test.cpp "" "gtest_main")
