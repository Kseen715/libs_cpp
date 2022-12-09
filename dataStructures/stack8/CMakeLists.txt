cmake_minimum_required(VERSION 3.0.0)
set(PROJECT_NAME stack8)
project(${PROJECT_NAME} VERSION 0.1.0)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

set(SOURCES stack8.cpp stack8mod.cpp list8.cpp list8mod.cpp)
set(HEADERS stack8.hpp stack8mod.hpp list8.hpp list8mod.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})