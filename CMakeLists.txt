cmake_minimum_required(VERSION 3.12)

project(data-structures C)
set(CMAKE_C_STANDARD 99)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build/modules")
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

# compile modules as library for unit testing to link
ADD_LIBRARY(stack OBJECT src/stack.c)
ADD_LIBRARY(linkedlist OBJECT src/linkedlist.c)
ADD_LIBRARY(doublelinkedlist OBJECT src/doublelinkedlist.c)
ADD_LIBRARY(ring OBJECT src/ring.c)
ADD_LIBRARY(bubblesort OBJECT src/bubblesort.c)

# unit testing
FIND_PACKAGE(CMOCKA REQUIRED)
enable_testing()
ADD_SUBDIRECTORY(tests)
