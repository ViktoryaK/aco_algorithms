#ifndef ACO_ALGORITHMS_ANTS_PARAMS_H
#define ACO_ALGORITHMS_ANTS_PARAMS_H

#include <boost/program_options.hpp>

struct AntsParams {
public:
    size_t nodes;
    size_t ants_n;
    double alpha;
    double betta;
    double deposition;
    double evaporation_rate;
    double init_pheromone;
    double termination;
    size_t elitism_n;
    double pheromone_decay;
    double explore_const;
    double min_pheromone;
    double max_pheromone;
    double mutation_rate;


    explicit AntsParams(boost::program_options::variables_map &options);
};

#endif //ACO_ALGORITHMS_ANTS_PARAMS_H
