cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME string_form8)
project(${PROJECT_NAME} VERSION 0.1.0)

set(SOURCES form8.cpp)
set(HEADERS form8.h)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})