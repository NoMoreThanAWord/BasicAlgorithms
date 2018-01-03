cmake_minimum_required(VERSION 3.9)
project(ShortestPath)

set(CMAKE_CXX_STANDARD 11)

add_executable(ShortestPath main.cpp Dijkstra.h BellmanFord.h)