
cmake_minimum_required(VERSION 3.13)
project(svec LANGUAGES C)

option(BUILD_TESTS "Build testing codes" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(SRCS svec/svec.c svec/list.c svec/queue.c svec/stack.c svec/vector.c)

add_library(svec ${SRCS})

if(BUILD_TESTS)
    include(test/test.cmake)
endif(BUILD_TESTS)
