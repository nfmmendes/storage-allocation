cmake_minimum_required(VERSION 3.13.14)

set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set (CMAKE_CXX_STANDARD 17)

project(SLAP)
file(GLOB SOURCE_CODE "*.cpp" "*.h")
add_executable(${PROJECT_NAME} ${SOURCE_CODE} )