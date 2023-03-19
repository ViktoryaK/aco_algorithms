#include "ant_system_tsp.h"

void
ant_system(const std::vector<std::vector<std::pair<int, int>>> &graph, boost::program_options::variables_map &options) {
    int nodes = options["nodes"].as<int>();
    int ants_n = options["ants_n"].as<int>();
    int alpha = options["pheromone_importance"].as<int>();
    int betta = options["heuristic_inf"].as<int>();
    int deposition = options["depositions"].as<int>();
    double evaporation_rate =  options["evaporation_rate"].as<double>();
    double init_pheromone = options["init_pheromone"].as<double>();
    while (true) {
        for (int i = 0; i < nodes; i++) {
            for (int ant = 0; ant < ants_n; ant++) {
                int start = 0;
                std::vector<int> visited;
                std::vector<double> probabilities_i;
                for (std::vector<std::pair<int, int>> neighbors : graph){

                }
            }
        }
    }
}