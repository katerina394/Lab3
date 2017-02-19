cmake_minimum_required(VERSION 2.8)

file(GLOB_RECURSE CPPS "*.cpp")
file(GLOB_RECURSE HPPS "../include/*.h")

include_directories(../include)

add_library(code ${CPPS} ${HPPS})

