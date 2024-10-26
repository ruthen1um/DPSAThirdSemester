cmake_minimum_required(VERSION 3.30.1)

project(SIAOD_6_1)

set(CMAKE_CXX_STANDARD 23)

add_executable(main
    "src/main.cpp"
    "src/repl.cpp"
    "src/record.cpp"
    "src/hashset.cpp"
    "src/generator.cpp"
)
