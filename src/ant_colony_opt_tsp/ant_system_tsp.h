#ifndef ACO_ALGORITHMS_ANT_COLONY_TSP_H
#define ACO_ALGORITHMS_ANT_COLONY_TSP_H

#include <vector>
#include "../parsers/ants_params.h"
#include <map>
#include <string>

void ant_system_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                const std::string &output_path);

void ant_system_elitism_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                        const std::string &output_path);

#endif //ACO_ALGORITHMS_ANT_COLONY_TSP_H
