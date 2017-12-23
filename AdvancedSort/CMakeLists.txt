cmake_minimum_required(VERSION 3.9)
project(AdvancedSort)

set(CMAKE_CXX_STANDARD 11)

add_executable(AdvancedSort main.cpp SortTestHelper.h MergeSort.h InsertionSort.h QuickSort.h)