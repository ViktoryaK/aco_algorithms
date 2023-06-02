#include <iostream>
#include <fstream>
#include "src/parsers/parser.h"
#include <boost/program_options.hpp>
#include "src/parsers/ants_params.h"
#include "src/parsers/graph_parser_mp.h"
#include "src/ant_colony_opt_pm/ant_system_pm.h"
#include "src/time_determination/time_determination.h"
#include "src/gale_shapley_pm/gale_shapley_pm.h"

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Wrong number of arguments" << std::endl;
        return 1;
    }

    std::string config_path{argv[1]};
    std::string graph_path{argv[2]};
    std::string number_of_algorithm{argv[3]};
    std::ifstream file(config_path);
    if (file.is_open()) {
        file.close();
    } else {
        std::cout << "Can not open configuration file" << std::endl;
        return 1;
    }
    boost::program_options::variables_map options = parse(config_path);
    AntsParams opt(options);
    std::vector<std::unordered_map<size_t, size_t>> graph_order = parse_graph_gale_mp(graph_path, opt.nodes);
    std::vector<std::unordered_map<size_t, size_t>> graph_value_sum = parse_graph_mp_wrong(graph_path, opt.nodes);
    std::vector<std::unordered_map<size_t, size_t>> graph_value = parse_graph_mp(graph_path, opt.nodes);
    auto start = get_current_time_fenced();
    if (number_of_algorithm == "0") {
        gale_shapley_pm(graph_order, graph_value, opt);
    } else if (number_of_algorithm == "1") {
        ant_system_pm(graph_value, opt);
    } else if (number_of_algorithm == "2") {
        ant_system_pm_min(graph_value_sum, graph_value,opt);
    }
    auto end = get_current_time_fenced();
    std::cout << "Total=" << to_us(end - start) << std::endl;
    return 0;
}
