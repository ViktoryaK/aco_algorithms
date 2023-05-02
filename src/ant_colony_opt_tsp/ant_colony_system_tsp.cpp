#include "ant_colony_system_tsp.h"
#include <iostream>
#include "../random_choice/random_choice.h"
#include "../random_choice/max_choice.h"
#include "../graph_generation/write_to_csv.h"
#include <random>

void ant_colony_system_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                       const std::string &output_path) {
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }

    double min_length = std::numeric_limits<double>::max();
    size_t choose_most_popular = 0;
    double most_popular_length;

    std::vector<std::vector<std::pair<size_t, size_t>>> most_popular_paths;
    std::vector<std::pair<size_t, size_t>> min_path;
    size_t iteration = 0;

    while ((double) choose_most_popular / (double) config.ants_n < config.termination & iteration < config.max_iter) {
        std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);

        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;

        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<bool> visited(config.nodes, false);
            visited[0] = true;
            size_t node = 0;
            size_t chosen = config.nodes;
            size_t prev = config.nodes;
            for (size_t created_edge = 0; created_edge < config.nodes - 1; ++created_edge) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key] && key != prev) {
                        probabilities.push_back(pow(pheromones[node][key], config.alpha) /
                                                pow(val, config.betta));
                        free_neighbours.push_back(key);
                        pheromones[node][key] = (1 - config.pheromone_decay) * pheromones[node][key] +
                                config.pheromone_decay * config.init_pheromone;
                    }
                }
                if (free_neighbours.empty()) { //for case if graph isn't full
                    chosen = config.nodes;
                    break;
                }

                double explore_rv = rand() / double(RAND_MAX);
                if (explore_rv < config.explore_const) {
                    chosen = max_choice(probabilities, free_neighbours);
                } else {
                    chosen = random_choice(probabilities, free_neighbours);
                }
                paths[ant].emplace_back(node, chosen);
                prev = node;
                node = chosen;
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
            if (paths[ant].size() != config.nodes - 1) {
                continue;
            }
            double total_length = 0;
            for (std::pair<size_t, size_t> path: paths[ant]) {
                total_length += graph[path.first].at(path.second);
            }
            path_popularity[total_length]++;
            path_by_length[total_length] = ant;
            if (total_length < min_length) {
                min_length = total_length;
                min_path = paths[ant];
            }
            for (std::pair<size_t, size_t> path: paths[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
        }
        choose_most_popular = 0;
        for (auto const &[key, val]: path_popularity) {
            if (val > choose_most_popular) {
                choose_most_popular = val;
                most_popular_length = key;
            }
        }
        most_popular_paths.push_back(paths[path_by_length[most_popular_length]]);
        std::cout << "Most popular " << iteration << ": " << most_popular_length << std::endl;
        std::cout << "Min length " << iteration << ": " << min_length << std::endl;
        iteration++;
    }
    write_to_csv(output_path, most_popular_paths, min_path, config.nodes, iteration);
}
