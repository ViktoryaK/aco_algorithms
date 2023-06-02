#ifndef ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H
#define ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H

#include <vector>
#include <unordered_map>
#include "../parsers/ants_params.h"

void ant_system_pm_min(const std::vector<std::unordered_map<size_t, size_t>> &graph,
                       const std::vector<std::unordered_map<size_t, size_t>> &graph_2, const AntsParams &config);

void ant_system_pm(const std::vector<std::unordered_map<size_t, size_t>> &graph, const AntsParams &config);

#endif //ACO_ALGORITHMS_ANT_COLONY_SYSTEM_H
