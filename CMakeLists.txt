cmake_minimum_required(VERSION 3.1)

project(homework_4)

set(HOMEWORK_4_SRC homework_4.cpp func.cpp Autotest.cpp)
set(HOMEWORK_4_HDR header.hpp Autotest.hpp)

add_executable(${PROJECT_NAME} ${HOMEWORK_4_SRC} ${HOMEWORK_4_HDR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 /std:c++14")