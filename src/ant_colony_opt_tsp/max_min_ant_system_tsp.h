#ifndef ACO_ALGORITHMS_MAX_MIN_ANT_SYSTEM_TSP_H
#define ACO_ALGORITHMS_MAX_MIN_ANT_SYSTEM_TSP_H

#include <vector>
#include "../parsers/ants_params.h"
#include <map>
#include <string>

void max_min_ant_system(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                        const std::string &output_path);

#endif //ACO_ALGORITHMS_MAX_MIN_ANT_SYSTEM_TSP_H
