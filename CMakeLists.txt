cmake_minimum_required(VERSION 3.0.2)

project(flatland-simulator)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/consoleHelper.hpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/consoleHelper.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})
target_link_libraries(${CMAKE_PROJECT_NAME} curses)
