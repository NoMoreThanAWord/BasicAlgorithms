cmake_minimum_required(VERSION 3.9)
project(UnionFind)

set(CMAKE_CXX_STANDARD 11)

add_executable(UnionFind main.cpp QuickFind.h UnionFindTestHelper.h QuickUnion.h OptimizeBySize.h OptmizeByRank.h RoadCompression.h)