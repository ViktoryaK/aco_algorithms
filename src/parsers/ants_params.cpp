#include "ants_params.h"


AntsParams::AntsParams(boost::program_options::variables_map &options) {
    nodes = options["nodes"].as<size_t>();
    ants_n = options["ants_n"].as<size_t>();
    alpha = options["pheromone_importance"].as<double>();
    betta = options["heuristic_inf"].as<double>();
    deposition = options["deposition"].as<double>();
    evaporation_rate = options["evaporation_rate"].as<double>();
    init_pheromone = options["init_pheromone"].as<double>();
    termination = options["termination"].as<double>();
    elitism_n = options["elitism_n"].as<size_t>();
    pheromone_decay = options["pheromone_decay"].as<double>();
    explore_const = options["explore_const"].as<double>();
    min_pheromone = options["min_pheromone"].as<double>();
    max_pheromone = options["max_pheromone"].as<double>();
    mutation_rate = options["mutation_rate"].as<double>();
    max_iter = options["max_iter"].as<size_t>();
}
