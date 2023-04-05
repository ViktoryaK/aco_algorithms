cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
#  It is used as your project's main executable name.
project(aco_algorithms C CXX)

set(CMAKE_CXX_STANDARD 17)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too much problem for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing.
set(ENABLE_PVS_STUDIO OFF)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan)
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
set(ENABLE_TSan OFF)
#! MemorySanitizer detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)


#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

##########################################################
# Project files, packages, libraries and so on
##########################################################

#! Project main executable source compilation
add_executable(aco_algorithms main.cpp
        ./src/parsers/graph_parser.cpp
        ./src/parsers/graph_parser.h
        ./src/parsers/parser.cpp
        ./src/parsers/parser.h
        ./src/parsers/ants_params.cpp
        ./src/parsers/ants_params.h
        ./src/random_choice/random_choice.cpp
        ./src/random_choice/random_choice.h
        ./src/random_choice/max_choice.cpp
        ./src/random_choice/max_choice.h
        ./src/graph_generation/write_to_csv.cpp
        ./src/graph_generation/write_to_csv.h
        ./src/ant_colony_optimization_tsp/ant_system_tsp.cpp
        ./src/ant_colony_optimization_tsp/ant_system_tsp.h
        ./src/ant_colony_optimization_tsp/ant_system_tsp_return.cpp
        ./src/ant_colony_optimization_tsp/ant_system_tsp_return.h        .
        ./src/ant_colony_optimization_tsp/ant_colony_system_tsp.cpp
        ./src/ant_colony_optimization_tsp/ant_colony_system_tsp.h
        ./src/ant_colony_optimization_tsp/max_min_ant_system_tsp.cpp
        ./src/ant_colony_optimization_tsp/max_min_ant_system_tsp.h
        )

#find_package(Threads REQUIRED)
#target_link_libraries(integrate_parallel_tpool Threads::Threads)

#! Put path to your project headers

#! Add external packages
# options_parser requires boost::program_options library
find_package(Boost 1.71.0 COMPONENTS program_options system REQUIRED)
target_include_directories(aco_algorithms PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(aco_algorithms Boost::program_options Boost::system)

set_target_properties(aco_algorithms PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
        $<TARGET_FILE:aco_algorithms> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)


# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS aco_algorithms)

# Include CMake setup
include(cmake/main-config.cmake)