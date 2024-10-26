cmake_minimum_required(VERSION 3.30.1)

project(SIAOD_5_2)
set(CMAKE_CXX_STANDARD 23)

add_executable(generator
    "src/generator.cpp"
    "src/record.cpp"
    "src/1.cpp"
)

add_executable(linear_search
    "src/linear_search.cpp"
    "src/record.cpp"
    "src/2.cpp"
)

add_executable(binary_search
    "src/binary_search.cpp"
    "src/record.cpp"
    "src/3.cpp"
)
