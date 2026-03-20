cmake_minimum_required(VERSION 3.10)
project(Projeto1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
        conference_tool.cpp
        parser.cpp
        Data.cpp
        max_flow.cpp
        build_graph.cpp
        menu.cpp
)

add_executable(myProg ${SOURCE_FILES})