# Lib CMakeLists version 0.1.0
# Compiler - "Visual Studio Community 2022 Release - amd64"
cmake_minimum_required(VERSION 3.20)
set(PROJECT_NAME searchAlgs)
project(${PROJECT_NAME} VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES searchAlgs.cpp)
set(HEADERS searchAlgs.hpp)

add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})