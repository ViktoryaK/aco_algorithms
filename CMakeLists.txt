cmake_minimum_required(VERSION 3.16)
project(aco_algorithms)

set(CMAKE_CXX_STANDARD 17)

add_executable(aco_algorithms ./src/main.cpp ./src/parsers/graph_parser.cpp ./src/parsers/graph_parser.h
        ./src/parsers/parser.cpp ./src/parsers/parser.h ./src/ant_colony_optimization_tsp/ant_system_tsp.cpp
        ./src/ant_colony_optimization_tsp/ant_system_tsp.h ./src/parsers/ants_params.cpp ./src/parsers/ants_params.h)
