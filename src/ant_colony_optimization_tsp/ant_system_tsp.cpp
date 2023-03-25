#include <iostream>
#include "ant_system_tsp.h"
#include "../random_choice/random_choice.h"

void ant_system(const std::vector<std::unordered_map<size_t, size_t>> &graph, const AntsParams &config) {
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }
    size_t min_length = std::numeric_limits<size_t>::max();
    for (size_t bob = 0; bob < 20; ++bob) {
        std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<bool> visited(config.nodes, false);
            visited[0] = true;
            size_t chosen;
            for (size_t node = 0; node < config.nodes - 1; ++node) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key]) {
                        probabilities.push_back(pow(pheromones[node][key], config.alpha) /
                                                pow(val, config.betta));
                        free_neighbours.push_back(key);
                    }
                }
                if (free_neighbours.empty()) {
                    chosen = config.nodes;
                    break;
                }
                chosen = random_choice(probabilities, free_neighbours);
                visited[chosen] = true;
                paths[ant].emplace_back(node, chosen);
            }
            visited[0] = false;
            if (chosen != config.nodes) {
                if (graph[ant].find(0) != graph[ant].end()) {
                    paths[ant].emplace_back(chosen, 0);
                }
            }
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key][node] *= 1 - config.evaporation_rate;
            }
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            if (paths[ant].size() != config.nodes) {
                continue;
            }
            size_t total_length = 0;
            for (std::pair<size_t, size_t> path: paths[ant]) {
                total_length += graph[path.first].at(path.second);
            }
            std::cout << "Ant " << ant << ": " << total_length << std::endl;
            if (total_length < min_length){
                min_length = total_length;
            }
            for (std::pair<size_t, size_t> path: paths[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / (double) total_length;
            }
        }
        std::cout << "Min length" << bob << ": " << min_length << std::endl;
    }
}