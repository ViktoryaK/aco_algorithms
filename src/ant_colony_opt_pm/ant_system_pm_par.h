//
// Created by klyms on 01.06.2023.
//

#ifndef ACO_ALGORITHMS_ANT_SYSTEM_PM_PAR_H
#define ACO_ALGORITHMS_ANT_SYSTEM_PM_PAR_H

#include <vector>
#include <unordered_map>
#include "../parsers/ants_params.h"

void ant_run_pm(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
                const std::vector<std::unordered_map<size_t, size_t>> &graph,
                std::vector<std::pair<size_t, size_t>> &ant_path, size_t i);

void ant_run_pm_min(const std::vector<std::unordered_map<size_t, size_t>> &graph,
                const std::vector<std::unordered_map<size_t, size_t>> &graph_2, const AntsParams &config,
                std::vector<std::pair<size_t, size_t>> &ant_path);

void ant_system_pm_min_par(size_t number_of_threads, const std::vector<std::unordered_map<size_t, size_t>> &graph,
                           const std::vector<std::unordered_map<size_t, size_t>> &graph_2, const AntsParams &config);

void ant_system_pm_par(size_t number_of_threads, const std::vector<std::unordered_map<size_t, size_t>> &graph,
                       const AntsParams &config);

#endif //ACO_ALGORITHMS_ANT_SYSTEM_PM_PAR_H
