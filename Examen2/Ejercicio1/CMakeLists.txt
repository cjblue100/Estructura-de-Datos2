cmake_minimum_required(VERSION 3.8)
project(test_checksum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} test_checksum.cpp checksum.cpp)
