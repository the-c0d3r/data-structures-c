
cmake_minimum_required(VERSION 2.6)

# Add CMocka
FIND_PACKAGE(CMOCKA REQUIRED)
INCLUDE_DIRECTORIES(${LIBCMOCKA_INCLUDE_DIR})

PROJECT(data-structure-test)
ADD_DEFINITIONS(-Wall -Werror --std=gnu99 -Wmissing-declarations)

FILE(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../build/modules")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# Find cmocka
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../test/cmocka/include)
FIND_LIBRARY(CMOCKA_LIBRARY cmocka HINTS ../../test/cmocka/build/src)

# List of tests
LIST(APPEND tests_names "test_stack")

# Declare all tests targets
LIST(LENGTH tests_names count)
MATH(EXPR count "${count} - 1")
FOREACH(i RANGE ${count})
    LIST(GET tests_names ${i} test_name)
    ADD_EXECUTABLE(${test_name} ${test_name}.c)
    TARGET_LINK_LIBRARIES(
        ${test_name}
        ${CMOCKA_LIBRARY}
    )
    ADD_TEST(NAME ${test_name} COMMAND ${test_name})
ENDFOREACH()

