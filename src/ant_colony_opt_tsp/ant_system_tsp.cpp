#include "ant_system_tsp.h"
#include <iostream>
#include <random>
#include "../random_choice/random_choice.h"
#include "../graph_generation/write_to_csv.h"
#include "../time_determination/time_determination.h"


void ant_system_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
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
            double mutation = rand() / double(RAND_MAX);
            for (size_t created_edge = 0; created_edge < config.nodes - 1; ++created_edge) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key] && key != prev) {
                        probabilities.push_back(pow(pheromones[node][key], config.alpha) /
                                                pow(val, config.betta));
                        free_neighbours.push_back(key);
                    }
                }
                if (free_neighbours.empty()) { //for case if graph isn't full
                    chosen = config.nodes;
                    break;
                }
                if (mutation < config.mutation_rate) {
                    std::random_device rd;
                    std::mt19937 rng(rd());
                    std::uniform_int_distribution<size_t> uni(0, free_neighbours.size() - 1);
                    auto random_integer = uni(rng);
                    chosen = free_neighbours[random_integer];
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

void ant_system_elitism_tsp(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
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
    size_t elite_ant = 0;
    std::vector<std::vector<std::pair<size_t, size_t>>> paths(config.ants_n);
    while ((double) choose_most_popular / (double) config.ants_n < config.termination & iteration < config.max_iter) {
        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;

        for (size_t ant = elite_ant; ant < config.ants_n; ++ant) {
            std::vector<bool> visited(config.nodes, false);
            visited[0] = true;
            size_t node = 0;
            size_t chosen = config.nodes;
            size_t prev = config.nodes;
            double mutation = rand() / double(RAND_MAX);
            for (size_t created_edge = 0; created_edge < config.nodes - 1; ++created_edge) {
                std::vector<size_t> free_neighbours;
                std::vector<double> probabilities;
                for (auto const &[key, val]: graph[node]) {
                    if (!visited[key] && key != prev) {
                        probabilities.push_back(pow(pheromones[node][key], config.alpha) /
                                                pow(val, config.betta));
                        free_neighbours.push_back(key);
                    }
                }
                if (free_neighbours.empty()) { //for case if graph isn't full
                    chosen = config.nodes;
                    break;
                }
                if (mutation < config.mutation_rate) {
                    std::random_device rd;
                    std::mt19937 rng(rd());
                    std::uniform_int_distribution<size_t> uni(0, free_neighbours.size() - 1);
                    auto random_integer = uni(rng);
                    chosen = free_neighbours[random_integer];
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
            for (std::pair<size_t, size_t> path: paths[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
        }
        choose_most_popular = 0;
        std::vector<double> all_paths;
        for (auto const &[key, val]: path_popularity) {
            all_paths.push_back(key);
            if (val > choose_most_popular) {
                choose_most_popular = val;
                most_popular_length = key;
            }
        }
        most_popular_paths.push_back(paths[path_by_length[most_popular_length]]);
        sort(all_paths.begin(), all_paths.end());

        if (min_length > all_paths[0]) {
            min_length = all_paths[0];
        }
        min_path = paths[path_by_length[min_length]];
        size_t elite = 0;
        size_t path_n = 0;
        std::vector<std::vector<std::pair<size_t, size_t>>> elite_paths(config.elitism_n);
        while (elite < config.elitism_n) {
            size_t cur_path = 0;
            while (cur_path < path_popularity[all_paths[path_n]] && cur_path + elite < config.elitism_n) {
                elite_paths[elite + cur_path] = paths[path_by_length[all_paths[path_n]]];
                cur_path++;
            }
            elite += cur_path;
            path_n++;
        }
        paths = elite_paths;
        paths.resize(config.ants_n);
        elite_ant = config.elitism_n;
        iteration++;
        std::cout << "Most popular " << iteration << ": " << most_popular_length << std::endl;
        std::cout << "Min length " << iteration << ": " << min_length << std::endl;
    }

    write_to_csv(output_path, most_popular_paths, min_path, config
            .nodes, iteration);
}