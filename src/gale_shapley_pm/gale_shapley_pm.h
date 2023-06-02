#ifndef ACO_ALGORITHMS_GALE_SHAPLEY_PM_H
#define ACO_ALGORITHMS_GALE_SHAPLEY_PM_H

#include <vector>
#include <unordered_map>
#include "../parsers/ants_params.h"


bool new_is_worse(const std::vector<std::unordered_map<size_t, size_t>> &graph, size_t woman, size_t current_partner,
                  size_t man, const AntsParams &config);

void gale_shapley_pm(const std::vector<std::unordered_map<size_t, size_t>> &graph,
                     const std::vector<std::unordered_map<size_t, size_t>> &graph1, const AntsParams &config);

#endif //ACO_ALGORITHMS_GALE_SHAPLEY_PM_H
