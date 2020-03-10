# @file CMakeLists.txt
# 
# CMake files for lambda_x example

cmake_minimum_required(VERSION 3.10)

# project info
project(lambda_x)

# C++17 standard
set(CMAKE_CXX_STANDARD 17)

# lambda_x application
add_executable(lambda_x lambda_x.cpp)
