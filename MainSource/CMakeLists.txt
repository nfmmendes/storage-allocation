cmake_minimum_required(VERSION 3.13.14)

set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
add_library(GTest::GMock INTERFACE IMPORTED)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


enable_testing()

### MAIN CODE
project(SLAP)
file(GLOB SOURCE_CODE "*.cpp" "*.h")
add_executable(${PROJECT_NAME} ${SOURCE_CODE} )

### TEST CODE
set(TESTS_SOURCE_DIRECTORY "${CMAKE_SOURCE_DIR}/tests/")
file(GLOB TESTS_SOURCE_CODE "${TESTS_SOURCE_DIRECTORY}/*.cpp")
list(REMOVE_ITEM SOURCE_CODE "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp")

add_executable(tests ${TESTS_SOURCE_CODE}  ${SOURCE_CODE})
target_link_libraries(tests GTest::gtest_main  GTest::gmock_main)
