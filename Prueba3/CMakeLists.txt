cmake_minimum_required(VERSION 3.8)
project(json2yaml)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} Jzon.cpp Yaml.cpp main.cpp)
