cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME list8)
project(${PROJECT_NAME} VERSION 0.1.0)

set(SOURCES list8.cpp list8mod.cpp)
set(HEADERS list8.hpp list8mod.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})