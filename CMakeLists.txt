cmake_minimum_required(VERSION 3.12)
project(ILS-MKP)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ILS-MKP
        Initialize.cpp
        Initialize.h
        Main.cpp ILS-Functions.cpp ILS-Functions.h CandidateSolution.cpp CandidateSolution.h)
