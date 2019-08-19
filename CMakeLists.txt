cmake_minimum_required(VERSION 3.0)
project( CWGE )
file(GLOB CPPS "*.cpp")
add_library(CWGE STATIC src/${CPPS})
