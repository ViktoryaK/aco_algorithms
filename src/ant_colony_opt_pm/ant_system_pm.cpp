#include "ant_system_pm.h"
#include <iostream>
#include "../random_choice/random_choice.h"
#include "../graph_generation/write_to_csv.h"
#include <random>
#include "../gale_shapley_pm/tests.h"


void ant_system_pm_min(const std::vector<std::unordered_map<size_t, size_t>> &graph,
                         const std::vector<std::unordered_map<size_t, size_t>> &graph_2, const AntsParams &config) {
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }

    size_t min_length = std::numeric_limits<size_t>::max();
    std::vector<std::pair<size_t, size_t>> min_path;
    size_t iteration = 0;
    while (iteration < config.max_iter) {
        std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);

        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<bool> visited(config.nodes, false);
            size_t node = 0;
            size_t chosen = config.nodes;
            for (size_t created_edge = 0; created_edge < config.nodes; ++created_edge) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key]) {
                        probabilities.push_back(pow(pheromones[node][key], config.alpha) /
                                                pow(val, config.betta));
                        free_neighbours.push_back(key);
                    }
                }
                chosen = random_choice(probabilities, free_neighbours);
                paths[ant].emplace_back(node, chosen);
                node++;
                visited[chosen] = true;
            }
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key][node] *= 1 - config.evaporation_rate;
            }
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            size_t total_length = 0;
            for (std::pair<size_t, size_t> path: paths[ant]) {
                total_length += graph[path.first].at(path.second);
            }
            if (total_length < min_length) {
                min_length = total_length;
                min_path = paths[ant];
            }
            for (std::pair<size_t, size_t> path: paths[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
        }
        iteration++;
    }
    std::cout << "Percent of stable matchings: " << percent_of_stable_m(graph_2, min_path, config.nodes) << std::endl;
    std::cout << "Average women preference: " << average_preference(graph_2, min_path, config.nodes, true) << std::endl;
    std::cout << "Average men preference: " << average_preference(graph_2, min_path, config.nodes, false) << std::endl;
}

void ant_system_pm(const std::vector<std::unordered_map<size_t, size_t>> &graph, const AntsParams &config) {

    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes * 2; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }
    size_t iteration = 0;
    std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);
    while (iteration < config.max_iter) {
        paths.clear();
        for (size_t i = 0; i < 2; ++i) {
            for (size_t ant = 0; ant < config.ants_n; ++ant) {
                std::vector<bool> visited(config.nodes, false);
                size_t node = 0;
                size_t chosen = config.nodes;
                for (size_t created_edge = 0; created_edge < config.nodes; ++created_edge) {
                    std::vector<size_t> free_neighbours;
                    std::vector<double> probabilities;
                    for (auto const &[key, val]: graph[config.nodes * i + node]) {
                        if (!visited[key]) {
                            probabilities.push_back(pow(pheromones[config.nodes * i + node][key], config.alpha) /
                                                    pow(val, config.betta));
                            free_neighbours.push_back(key);
                        }
                    }
                    chosen = random_choice(probabilities, free_neighbours);
                    paths[ant].emplace_back(node, chosen);
                    node++;
                    visited[chosen] = true;
                }
            }
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key + config.nodes][node] *= 1 - config.evaporation_rate;
            }
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            for (size_t person = 0; person < config.nodes; ++person) {
                pheromones[paths[ant][person].first].at(
                        paths[ant][person].second) += config.deposition;
                pheromones[paths[ant][person].second + config.nodes].at(
                        paths[ant][person].first) += config.deposition;
            }
        }
        iteration++;
    }
    double max_pheromone = 0;
    size_t final_path = 0;
    for (size_t ant = 0; ant < config.ants_n; ++ant) {
        double pheromone = 0;
        for (size_t pair = 0; pair < config.nodes; ++pair) {
            pheromone += pheromones[paths[ant][pair + config.nodes].first][paths[ant][pair + config.nodes].second];
        }
        if (max_pheromone < pheromone){
            final_path = ant;
        }
    }
    std::cout << "Percent of stable matchings: " << percent_of_stable_m(graph, paths[final_path], config.nodes) << std::endl;
    std::cout << "Average women preference: " << average_preference(graph, paths[final_path], config.nodes, true) << std::endl;
    std::cout << "Average men preference: " << average_preference(graph, paths[final_path], config.nodes, false) << std::endl;
}