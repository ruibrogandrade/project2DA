cmake_minimum_required(VERSION 3.20)
project(travel-agency)

set(CMAKE_CXX_STANDARD 14)

include_directories(Classes)

add_executable(
        travel-agency
        Classes/main.cpp
        Classes/Graph.h
        Classes/Graph.cpp
        Classes/FileReader.cpp
        Classes/FileReader.h Classes/Application.cpp Classes/Application.h Classes/maxHeap.h Classes/minHeap.h)