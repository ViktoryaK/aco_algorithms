#ifndef ACO_ALGORITHMS_ANTS_PARAMS_H
#define ACO_ALGORITHMS_ANTS_PARAMS_H

struct AntsParams{
public:
    size_t nodes;
    size_t ants_n;
    double alpha;
    double betta;
    double deposition;
    double evaporation_rate;
    double init_pheromone;


    explicit AntsParams(boost::program_options::variables_map &options);
};

#endif //ACO_ALGORITHMS_ANTS_PARAMS_H
