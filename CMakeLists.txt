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
        ./src/time_determination/time_determination.cpp
        ./src/time_determination/time_determination.h
        ./src/ant_colony_opt_tsp/ant_system_tsp.cpp
        ./src/ant_colony_opt_tsp/ant_system_tsp.h
        ./src/ant_colony_opt_tsp/ant_system_tsp_return.cpp
        ./src/ant_colony_opt_tsp/ant_system_tsp_return.h .
        ./src/ant_colony_opt_tsp/ant_colony_system_tsp.cpp
        ./src/ant_colony_opt_tsp/ant_colony_system_tsp.h
        ./src/ant_colony_opt_tsp/max_min_ant_system_tsp.cpp
        ./src/ant_colony_opt_tsp/max_min_ant_system_tsp.h
        )


add_executable(genetic_algorithm genetic_main.cpp
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
        ./src/time_determination/time_determination.cpp
        ./src/time_determination/time_determination.h
        ./src/genetic_tsp/genetic_tsp.cpp
        ./src/genetic_tsp/genetic_tsp.h
        )


add_executable(aco_algorithms_par par_main.cpp
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
        ./src/time_determination/time_determination.cpp
        ./src/time_determination/time_determination.h
        ./src/ant_colony_opt_tsp_par/ant_system_tsp_par.cpp
        ./src/ant_colony_opt_tsp_par/ant_system_tsp_par.h
        )


add_executable(aco_algorithms_mp main_pm.cpp
        ./src/parsers/graph_parser_mp.cpp
        ./src/parsers/graph_parser_mp.h
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
        ./src/time_determination/time_determination.cpp
        ./src/time_determination/time_determination.h
        src/ant_colony_opt_pm/ant_system_pm.cpp
        src/ant_colony_opt_pm/ant_system_pm.h
        ./src/gale_shapley_pm/gale_shapley_pm.cpp
        ./src/gale_shapley_pm/gale_shapley_pm.h
        ./src/gale_shapley_pm/tests.cpp
        ./src/gale_shapley_pm/tests.h
        )



add_executable(aco_algorithms_mp_par par_main_pm.cpp
        ./src/parsers/graph_parser_mp.cpp
        ./src/parsers/graph_parser_mp.h
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
        ./src/time_determination/time_determination.cpp
        ./src/time_determination/time_determination.h
        ./src/gale_shapley_pm/gale_shapley_pm.cpp
        ./src/gale_shapley_pm/gale_shapley_pm.h
        ./src/gale_shapley_pm/tests.cpp
        ./src/gale_shapley_pm/tests.h
        ./src/ant_colony_opt_pm/ant_system_pm_par.cpp
        ./src/ant_colony_opt_pm/ant_system_pm_par.h
        )

find_package(Threads REQUIRED)
target_link_libraries(aco_algorithms_par Threads::Threads)

find_package(Threads REQUIRED)
target_link_libraries(aco_algorithms_mp_par Threads::Threads)

#! Put path to your project headers

#! Add external packages
# options_parser requires boost::program_options library
find_package(Boost 1.71.0 COMPONENTS program_options system REQUIRED)

target_include_directories(aco_algorithms PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(aco_algorithms Boost::program_options Boost::system)

target_include_directories(aco_algorithms_par PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(aco_algorithms_par Boost::program_options Boost::system)

target_include_directories(genetic_algorithm PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(genetic_algorithm Boost::program_options Boost::system)


target_include_directories(aco_algorithms_mp PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(aco_algorithms_mp Boost::program_options Boost::system)



target_include_directories(aco_algorithms_mp_par PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries(aco_algorithms_mp_par Boost::program_options Boost::system)


set_target_properties(aco_algorithms PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(aco_algorithms_mp PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(aco_algorithms_mp_par PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(aco_algorithms_par PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

set_target_properties(genetic_algorithm PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
        $<TARGET_FILE:aco_algorithms> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:aco_algorithms_par> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)

INSTALL(PROGRAMS
        $<TARGET_FILE:aco_algorithms_mp> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)


INSTALL(PROGRAMS
        $<TARGET_FILE:aco_algorithms_mp_par> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)


INSTALL(PROGRAMS
        $<TARGET_FILE:genetic_algorithm> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
        DESTINATION bin)
# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS aco_algorithms)

set(ALL_TARGETS aco_algorithms_par)

set(ALL_TARGETS genetic_algorithm)


set(ALL_TARGETS aco_algorithms_mp)
set(ALL_TARGETS aco_algorithms_mp_par)
# Include CMake setup
include(cmake/main-config.cmake)