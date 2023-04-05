// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "parser.h"
#include <string>
#include <fstream>

boost::program_options::variables_map parse(const std::string &config_file) {
    boost::program_options::options_description desc("Allowed options");
    boost::program_options::variables_map options;
    desc.add_options()
            ("nodes", boost::program_options::value<size_t>()->required(), "nodes")
            ("pheromone_importance", boost::program_options::value<double>()->required(), "pheromone_importance")
            ("heuristic_inf", boost::program_options::value<double>()->required(), "heuristic_inf")
            ("deposition", boost::program_options::value<double>()->required(), "deposition")
            ("evaporation_rate", boost::program_options::value<double>()->default_value(0), "evaporation_rate")
            ("init_pheromone", boost::program_options::value<double>()->default_value(0), "init_pheromone")
            ("ants_n", boost::program_options::value<size_t>()->required(), "ants_n")
            ("termination", boost::program_options::value<double>()->default_value(0.8), "termination")
            ("elitism_n", boost::program_options::value<size_t>()->default_value(0), "elitism_n")
            ("pheromone_decay", boost::program_options::value<double>()->default_value(0), "pheromone_decay")
            ("explore_const", boost::program_options::value<double>()->default_value(0), "explore_const")
            ("min_pheromone", boost::program_options::value<double>()->default_value(0), "min_pheromone")
            ("max_pheromone",
             boost::program_options::value<double>()->default_value(std::numeric_limits<double>::max()),
             "max_pheromone")
            ("mutation_rate", boost::program_options::value<double>()->default_value(0), "mutation_rate");
    std::ifstream file(config_file);
    boost::program_options::store(boost::program_options::parse_config_file(file, desc), options);
    boost::program_options::notify(options);
    file.close();
    return options;
}