cmake_minimum_required(VERSION 3.8)
project(inv_index)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} main.cpp inv_index.cpp)
