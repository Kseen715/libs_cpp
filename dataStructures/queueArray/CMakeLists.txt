cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME queueArray)
project(${PROJECT_NAME} VERSION 0.1.0)

set(SOURCES queueArray.cpp queueArrayMod.cpp)
set(HEADERS queueArray.hpp queueArrayMod.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})