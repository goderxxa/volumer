cmake_minimum_required(VERSION 3.24)
project(volumer)

set(CMAKE_CXX_STANDARD 17)

#add resources
set(RESOURCE_FILES resources.rc)

add_executable(volumer main.cpp)
