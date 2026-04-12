cmake_minimum_required(VERSION 3.20)
project(FTSClient)

set(CMAKE_CXX_STANDARD 20)

find_package(SDL3 REQUIRED)

add_executable(FTSClient src/main.cpp)
target_link_libraries(FTSClient SDL3::SDL3)