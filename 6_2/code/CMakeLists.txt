cmake_minimum_required(VERSION 3.30.1)

project(SIAOD_6_2)

set(CMAKE_CXX_STANDARD 23)

add_executable(ex1
    "src/ex1/main.cpp"
)

add_executable(ex2
    "src/ex2/main.cpp"
    "src/ex2/bmh.cpp"
)
