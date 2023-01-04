cmake_minimum_required(VERSION 3.0.0)
project(workTimeLib VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES workTimeLib.cpp)
set(HEADERS workTimeLib.hpp)

add_library(workTimeLib STATIC ${SOURCES} ${HEADERS})
target_include_directories(workTimeLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})