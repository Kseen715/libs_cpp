# Lib CMakeLists version 0.1.0
# Compiler - "Visual Studio Community 2022 Release - amd64"
cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME tree8)
project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES tree8.cpp tree8mod.cpp)
set(HEADERS tree8.hpp tree8mod.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})