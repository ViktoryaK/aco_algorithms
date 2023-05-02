#ifndef ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H
#define ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H

#include <vector>
#include <unordered_map>
#include "../parsers/ants_params.h"

void ant_colony_system_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                       const std::string &output_path);

#endif //ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H
