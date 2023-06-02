#include <iostream>
#include <fstream>
#include "src/parsers/parser.h"
#include <boost/program_options.hpp>
#include "src/parsers/ants_params.h"
#include "src/parsers/graph_parser.h"
#include "src/ant_colony_opt_tsp/ant_system_tsp_return.h"
#include "src/ant_colony_opt_tsp/ant_system_tsp.h"
#include "src/ant_colony_opt_tsp/ant_colony_system_tsp.h"
#include "src/ant_colony_opt_tsp/max_min_ant_system_tsp.h"
#include "src/time_determination/time_determination.h"

int main(int argc, char **argv) {
    if (argc != 6) {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::string config_path{argv[1]};
    std::string graph_path{argv[2]};
    std::string output_path{argv[3]};
    std::string number_of_algorithm{argv[4]};
    std::string return_to_start{argv[5]};
    std::ifstream file(config_path);
    if (file.is_open()) {
        file.close();
    } else {
        std::cout << "Can not open configuration file" << std::endl;
        return 1;
    }
    boost::program_options::variables_map options = parse(config_path);
    AntsParams opt(options);
    std::vector<std::unordered_map<size_t, double>> graph = parse_graph(graph_path, opt.nodes);
    if (number_of_algorithm == "1") {
        if (return_to_start == "0") {
            auto start = get_current_time_fenced();
            ant_system_tsp(graph, opt, output_path);
            auto end = get_current_time_fenced();
            std::cout << "Total=" << to_us(end - start) << std::endl;
        } else {
            ant_system_return_tsp(graph, opt, output_path);
        }
    } else if (number_of_algorithm == "2") {
        auto start = get_current_time_fenced();
        ant_system_elitism_tsp(graph, opt, output_path);
        auto end = get_current_time_fenced();
        std::cout << "Total=" << to_us(end - start) << std::endl;
    } else if (number_of_algorithm == "3") {
        auto start = get_current_time_fenced();
        ant_colony_system_tsp(graph, opt, output_path);
        auto end = get_current_time_fenced();
        std::cout << "Total=" << to_us(end - start) << std::endl;
    } else if (number_of_algorithm == "4") {
        auto start = get_current_time_fenced();
        max_min_ant_system(graph, opt, output_path);
        auto end = get_current_time_fenced();
        std::cout << "Total=" << to_us(end - start) << std::endl;
    }
    return 0;
}