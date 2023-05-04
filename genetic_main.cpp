#include <iostream>
#include <fstream>
#include "src/parsers/parser.h"
#include <boost/program_options.hpp>
#include <charconv>
#include "src/parsers/ants_params.h"
#include "src/parsers/graph_parser.h"
#include "src/time_determination/time_determination.h"
#include "src/genetic_tsp/genetic_tsp.h"

int main(int argc, char **argv) {
    if (argc != 5) {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }
    size_t rep;
    std::string config_path{argv[1]};
    std::string graph_path{argv[2]};
    std::string output_path{argv[3]};
    std::string repetitions{argv[4]};
    std::from_chars(repetitions.data(), repetitions.data() + repetitions.size(),
                    rep);
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
    auto start = get_current_time_fenced();
    size_t result = execute_genetic(30, opt.nodes, rep, graph);
    std::cout << "Result" << ":" << result << std::endl;
    auto end = get_current_time_fenced();
    std::cout << "Total=" << to_us(end - start) << std::endl;
    return 0;
}