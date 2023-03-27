//
// Created by klyms on 27.03.2023.
//

#ifndef ACO_ALGORITHMS_ANT_COLONY_TSP_H
#define ACO_ALGORITHMS_ANT_COLONY_TSP_H

#include <vector>
#include "../parsers/ants_params.h"
#include <map>
#include <string>

void ant_system(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                const std::string &output_path);

void ant_system_elitism(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                        const std::string &output_path);

#endif //ACO_ALGORITHMS_ANT_COLONY_TSP_H
