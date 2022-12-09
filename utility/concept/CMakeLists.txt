cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME stdConcepts)
project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-std=c++2a)
add_compile_options(-fconcepts)

set(SOURCES stdConcepts.cpp)
set(HEADERS stdConcepts.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
