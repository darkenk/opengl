enable_testing()
file(GLOB test_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *_test.cpp)
foreach(test_source ${test_SOURCES})
	string(REPLACE ".cpp" "" test_name ${test_source})
	string(REPLACE "_test" "" source_file ${test_source})
	add_executable(${test_name} ${test_source} ../src/${source_file})
	target_link_libraries(${test_name} gtest gtest_main pthread)
	add_test(NAME ${test_name} COMMAND ${test_name})
	set(target "run_${test_name}")
	add_custom_target(${target}
	        COMMAND ${test_name}
	        COMMENT "Run with ${CMAKE_BUILD_TYPE} configuration"
	)
endforeach()
