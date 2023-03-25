#include <iostream>
#include <charconv>
#include <fstream>
#include "src/parsers/parser.h"
#include <boost/program_options.hpp>
#include "src/parsers/ants_params.h"
#include "src/parsers/graph_parser.h"
#include "src/ant_colony_optimization_tsp/ant_system_tsp.h"

int main(int argc, char **argv) {
    if (argc!=4) {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }

    int algorithm_number;
    std::string config_path{argv[1]};
    std::string graph_path{argv[2]};
    std::string number_of_algorithm{argv[3]};
    std::from_chars(number_of_algorithm.data(), number_of_algorithm.data()+number_of_algorithm.size(), algorithm_number);
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
    ant_system(graph, opt);
    return 0;
}