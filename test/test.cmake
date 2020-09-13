
macro(add_svec_test TEST_TARGET TEST_SRCS)
    add_executable(${TEST_TARGET} ${TEST_SRCS})
    target_link_libraries(${TEST_TARGET} svec)
endmacro(add_svec_test)

add_svec_test(test_list      "test/test_list.c")
add_svec_test(test_vector    "test/test_vector.c")
