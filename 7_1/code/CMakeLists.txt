cmake_minimum_required(VERSION 3.30.1)

project(SIAOD_7_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(main
    "src/main.cpp"
    "src/repl.cpp"
    "src/dot.cpp"
    "src/avl_tree_functions.cpp"
)
