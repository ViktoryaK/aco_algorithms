#include <iostream>
#include <fstream>
#include "ant_system_tsp.h"
#include "../random_choice/random_choice.h"

void ant_system(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config) {
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }
    double min_length = std::numeric_limits<double>::max();
    size_t choose_most_popular = 0;
    std::vector<std::vector<std::pair<size_t, size_t>>> most_popular_paths;
    size_t iteration = 0;
    std::vector<std::pair<size_t, size_t>> min_path;
    while ((double) choose_most_popular / (double) config.ants_n < 0.8) {
        std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);
        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<bool> visited(config.nodes, false);
            visited[0] = true;
            size_t chosen = config.nodes;
            size_t node = 0;
            size_t prev = config.nodes;
            for (size_t created_edge = 0; created_edge < config.nodes - 1; ++created_edge) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key] and key != prev) {
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
                prev = node;
                paths[ant].emplace_back(node, chosen);
                node = chosen;
            }
            if (chosen != config.nodes){
                if (graph[node].find(0) != graph[node].end()){
                    paths[ant].emplace_back(node, 0);
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
            double total_length = 0;
            for (std::pair<size_t, size_t> path: paths[ant]) {
                total_length += graph[path.first].at(path.second);
            }
            if (path_popularity.find(total_length) == path_popularity.end()) {
                path_popularity[total_length] = 1;
                path_by_length[total_length] = ant;
            } else {
                path_popularity[total_length] += 1;
            }
            std::cout << "Ant " << ant << ": " << total_length << std::endl;
            if (total_length < min_length) {
                min_length = total_length;
                min_path = paths[ant];
            }
            for (std::pair<size_t, size_t> path: paths[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
            choose_most_popular = 0;
        }
        for (auto const &[key, val]: path_popularity) {
            if (val > choose_most_popular) {
                choose_most_popular = val;
                most_popular_paths.push_back(paths[path_by_length[key]]);
            }
        }
        std::cout << "Min length " << iteration++ << ": " << min_length << std::endl;
    }
    std::ofstream file_csv;
    file_csv.open("./data/paths3.csv");
    for (size_t i = 0; i < iteration - 1; ++i) {
        file_csv << "path_" << i << ",";
        for (size_t elem = 0; elem < config.nodes - 1; ++elem) {
            file_csv << most_popular_paths[i][elem].first << " " << most_popular_paths[i][elem].second << ",";
        }
        file_csv << most_popular_paths[i][config.nodes - 1].first << " "
                 << most_popular_paths[i][config.nodes - 1].second << "\n";
    }
    file_csv << "min_path,";
    for (size_t elem = 0; elem < config.nodes - 1; ++elem) {
        file_csv << min_path[elem].first << " " << min_path[elem].second << ",";
    }
    file_csv << min_path[config.nodes - 1].first << " "
             << min_path[config.nodes - 1].second << "\n";


    file_csv.close();
}