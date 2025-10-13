cmake_minimum_required(VERSION 4.0)
project(cp)

set(CMAKE_CXX_STANDARD 20)
#add_compile_definitions(_GLIBCXX_DEBUG)

add_executable(cp main.cpp
        gen.cpp
        gen.cpp)
