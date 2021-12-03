#project
cmake_minimum_required(VERSION 3.16)

PROJECT(mywebserver)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++17)
    message(STATUS "optional:-std=c++17")   
endif(CMAKE_COMPILER_IS_GNUCXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g"
)

ADD_SUBDIRECTORY(src)

