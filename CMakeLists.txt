cmake_minimum_required(VERSION 3.0.2)

project(flatland-simulator)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})
