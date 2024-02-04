cmake_minimum_required(VERSION 3.27)
project(2560_Projects)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories("Project 1")

add_executable(2560_Projects
        "Project 1/code.cpp"
        "Project 1/code.hpp"
        "Project 1/main.cpp"
        "Project 1/mastermind.cpp"
        "Project 1/mastermind.hpp"
        "Project 1/response.cpp"
        "Project 1/response.hpp"
        code.hpp)
