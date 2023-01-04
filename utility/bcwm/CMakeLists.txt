cmake_minimum_required(VERSION 3.0.0)
project(bcwm VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES bcwm.cpp)
set(HEADERS bcwm.hpp)

add_library(bcwm STATIC ${SOURCES} ${HEADERS})
target_include_directories(bcwm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})