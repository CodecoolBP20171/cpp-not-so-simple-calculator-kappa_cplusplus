cmake_minimum_required(VERSION 3.8)
project(cpp_not_so_simple_calculator_kappa_cplusplus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Calculator.cpp
        Tester.hpp)

add_executable(cpp_not_so_simple_calculator_kappa_cplusplus ${SOURCE_FILES})