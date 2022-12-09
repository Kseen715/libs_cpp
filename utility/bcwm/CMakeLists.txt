cmake_minimum_required(VERSION 3.0.0)
project(bcwm VERSION 0.1.0)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeTarget PROPERTY CXX_STANDARD 20)
endif()

set(SOURCES bcwm.cpp)
set(HEADERS bcwm.hpp)

add_library(bcwm STATIC ${SOURCES} ${HEADERS})
target_include_directories(bcwm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})