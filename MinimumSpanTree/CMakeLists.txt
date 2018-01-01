cmake_minimum_required(VERSION 3.9)
project(MinimumSpanTree)

set(CMAKE_CXX_STANDARD 11)
add_executable(MinimumSpanTree main.cpp Edge.h LazyPrimMST.h PrimMst.h KruskalMST.h)