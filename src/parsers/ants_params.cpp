#include <boost/program_options.hpp>



struct AntsParams {
    int nodes;
    int ants_n;
    int alpha;
    int betta;
    int deposition;
    double evaporation_rate;
    double init_pheromone;

    explicit AntsParams(boost::program_options::variables_map &options) {
        nodes = options["nodes"].as<int>();
        ants_n = options["ants_n"].as<int>();
        alpha = options["pheromone_importance"].as<int>();
        betta = options["heuristic_inf"].as<int>();
        deposition = options["depositions"].as<int>();
        evaporation_rate =  options["evaporation_rate"].as<double>();
        init_pheromone = options["init_pheromone"].as<double>();
    }
};
