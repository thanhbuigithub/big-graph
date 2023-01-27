cmake_minimum_required(VERSION 3.24)
project(BigGraph)

set(CMAKE_CXX_STANDARD 17)
file(GLOB SOURCES *.h *.cpp)

add_executable(BigGraph ${SOURCES})
