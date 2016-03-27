cmake_minimum_required(VERSION 3.3)
project(Project1_trees)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp AVL_Tree/AVL.h RedBlack_Tree/RedBlack.h BST_Tree/BST.h Tree Timer.h )
add_executable(Project1_trees ${SOURCE_FILES})