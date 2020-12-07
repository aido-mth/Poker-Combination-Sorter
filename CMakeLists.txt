cmake_minimum_required(VERSION 3.17)
project(Poker_Combination_Sorter)

set(CMAKE_CXX_STANDARD 17)

add_executable(Poker_Combination_Sorter
        README.md main.cpp sorter.h parsers.h split.h getCombinations.h checkers.h toString.h)
