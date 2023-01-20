cmake_minimum_required(VERSION 3.24)
project(BigGraph)

set(CMAKE_CXX_STANDARD 17)

add_executable(BigGraph main.cpp Node.cpp Node.h Edge.cpp Edge.h Graph.cpp Graph.h Reader.cpp Reader.h Writer.cpp Writer.h Define.cpp Define.h)
