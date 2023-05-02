//
// Created by klyms on 02.05.2023.
//

#ifndef ACO_ALGORITHMS_ANT_SYSTEM_TSP_PAR_H
#define ACO_ALGORITHMS_ANT_SYSTEM_TSP_PAR_H

#include "../parsers/ants_params.h"

void ant_system_tsp_par(size_t number_of_threads, const AntsParams &config,
                        const std::vector<std::unordered_map<size_t, double>> &graph, const std::string &output_path);

void ant_run(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
             const std::vector<std::unordered_map<size_t, double>> &graph,
             std::vector<std::pair<size_t, size_t>> &ant_path);


void ant_system_elitism_tsp_par(size_t number_of_threads, const AntsParams &config,
                                const std::vector<std::unordered_map<size_t, double>> &graph,
                                const std::string &output_path);

void min_max_ant_system_tsp_par(size_t number_of_threads, const AntsParams &config,
                                const std::vector<std::unordered_map<size_t, double>> &graph, const std::string &output_path);
#endif //ACO_ALGORITHMS_ANT_SYSTEM_TSP_PAR_H
