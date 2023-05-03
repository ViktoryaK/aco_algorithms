//
// Created by klyms on 02.05.2023.
//

#include "ant_system_tsp_par.h"
#include <boost/asio/thread_pool.hpp>
#include <boost/asio.hpp>
#include <future>
#include "../random_choice/random_choice.h"
#include <random>
#include <iostream>
#include "../time_determination/time_determination.h"
#include "../graph_generation/write_to_csv.h"


void ant_run(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
             const std::vector<std::unordered_map<size_t, double>> &graph,
             std::vector<std::pair<size_t, size_t>> &ant_path) {
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
        ant_path.emplace_back(node, chosen);
        prev = node;
        node = chosen;
        visited[chosen] = true;
    }
}


void ant_run_min_max(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
             const std::vector<std::unordered_map<size_t, double>> &graph,
             std::vector<std::pair<size_t, size_t>> &ant_path) {
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
        ant_path.emplace_back(node, chosen);
        prev = node;
        node = chosen;
        visited[chosen] = true;
    }
}

void ant_system_tsp_par(size_t number_of_threads, const AntsParams &config,
                        const std::vector<std::unordered_map<size_t, double>> &graph, const std::string &output_path) {
    boost::asio::thread_pool pool(number_of_threads);
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
        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;
        std::vector<std::promise<std::vector<std::pair<size_t, size_t>>>> paths(config.ants_n);
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
//            std::cout << 1 << std::endl;
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run(pheromones, config, graph, ant_path);
                paths[ant].set_value(ant_path);
            });
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key][node] *= 1 - config.evaporation_rate;
            }
        }
        std::vector<std::vector<std::pair<size_t, size_t>>> paths_std;
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            auto cur_path = paths[ant].get_future().get();
            paths_std.push_back(cur_path);
            if (cur_path.size() != config.nodes - 1) {
                continue;
            }
            double total_length = 0;
            for (std::pair<size_t, size_t> path: cur_path) {
                total_length += graph[path.first].at(path.second);
            }
            path_popularity[total_length]++;
            path_by_length[total_length] = ant;
            if (total_length < min_length) {
                min_length = total_length;
                min_path = cur_path;
            }
            for (std::pair<size_t, size_t> path: cur_path) {
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
        most_popular_paths.push_back(paths_std[path_by_length[most_popular_length]]);
        std::cout << "Most popular " << iteration << ": " << most_popular_length << std::endl;
        std::cout << "Min length " << iteration << ": " << min_length << std::endl;
        iteration++;
    }
    write_to_csv(output_path, most_popular_paths, min_path, config.nodes, iteration);
}


void ant_system_elitism_tsp_par(size_t number_of_threads, const AntsParams &config,
                                const std::vector<std::unordered_map<size_t, double>> &graph,
                                const std::string &output_path) {
    boost::asio::thread_pool pool(number_of_threads);
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
    std::vector<std::vector<std::pair<size_t, size_t>>> paths_std;
    while ((double) choose_most_popular / (double) config.ants_n < config.termination & iteration < config.max_iter) {
        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;
        std::vector<std::promise<std::vector<std::pair<size_t, size_t>>>> paths(config.ants_n);
        for (size_t ant = elite_ant; ant < config.ants_n; ++ant) {
//            std::cout << 1 << std::endl;
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run(pheromones, config, graph, ant_path);
                paths[ant].set_value(ant_path);
            });
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key][node] *= 1 - config.evaporation_rate;
            }
        }
        size_t ant_number = 0;
        for (const std::vector<std::pair<size_t, size_t>>& elite_path: paths_std) {
            double total_length = 0;
            for (std::pair<size_t, size_t> path: elite_path) {
                total_length += graph[path.first].at(path.second);
            }
            path_popularity[total_length]++;
            path_by_length[total_length] = ant_number;
            for (std::pair<size_t, size_t> path: elite_path) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
            ant_number++;
        }
        for (size_t ant = elite_ant; ant < config.ants_n; ++ant) {
            auto cur_path = paths[ant].get_future().get();
            paths_std.push_back(cur_path);
            double total_length = 0;
            for (std::pair<size_t, size_t> path: paths_std[ant]) {
                total_length += graph[path.first].at(path.second);
            }
            path_popularity[total_length]++;
            path_by_length[total_length] = ant;
            for (std::pair<size_t, size_t> path: paths_std[ant]) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
        }
        std::vector<double> all_paths;
        choose_most_popular = 0;
        for (auto const &[key, val]: path_popularity) {
            all_paths.push_back(key);
            if (val > choose_most_popular) {
                choose_most_popular = val;
                most_popular_length = key;
            }
        }
        most_popular_paths.push_back(paths_std[path_by_length[most_popular_length]]);
        sort(all_paths.begin(), all_paths.end());

        if (min_length > all_paths[0]) {
            min_length = all_paths[0];
        }
        min_path = paths_std[path_by_length[min_length]];
        size_t elite = 0;
        size_t path_n = 0;
        std::vector<std::vector<std::pair<size_t, size_t>>> elite_paths(config.elitism_n);
        while (elite < config.elitism_n) {
            size_t cur_path = 0;
            while (cur_path < path_popularity[all_paths[path_n]] && cur_path + elite < config.elitism_n) {
                elite_paths[elite + cur_path] = paths_std[path_by_length[all_paths[path_n]]];
                cur_path++;
            }
            elite += cur_path;
            path_n++;
        }
        paths_std = elite_paths;
        paths.resize(config.ants_n);
        elite_ant = config.elitism_n;
        iteration++;
        std::cout << "Most popular " << iteration << ": " << most_popular_length << std::endl;
        std::cout << "Min length " << iteration << ": " << min_length << std::endl;
    }

    write_to_csv(output_path, most_popular_paths, min_path, config
            .nodes, iteration);
}



void min_max_ant_system_tsp_par(size_t number_of_threads, const AntsParams &config,
                        const std::vector<std::unordered_map<size_t, double>> &graph, const std::string &output_path) {
    boost::asio::thread_pool pool(number_of_threads);
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
        std::unordered_map<double, size_t> path_popularity;
        std::unordered_map<double, size_t> path_by_length;
        std::vector<std::promise<std::vector<std::pair<size_t, size_t>>>> paths(config.ants_n);
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
//            std::cout << 1 << std::endl;
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run_min_max(pheromones, config, graph, ant_path);
                paths[ant].set_value(ant_path);
            });
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key][node] *= 1 - config.evaporation_rate;
            }
        }
        std::vector<std::vector<std::pair<size_t, size_t>>> paths_std;
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            auto cur_path = paths[ant].get_future().get();
            paths_std.push_back(cur_path);
            if (cur_path.size() != config.nodes - 1) {
                continue;
            }
            double total_length = 0;
            for (std::pair<size_t, size_t> path: cur_path) {
                total_length += graph[path.first].at(path.second);
            }
            path_popularity[total_length]++;
            path_by_length[total_length] = ant;
            if (total_length < min_length) {
                min_length = total_length;
                min_path = cur_path;
            }
        }
        choose_most_popular = 0;
        for (std::pair<size_t, size_t> path: min_path) {
            pheromones[path.first].at(path.second) += config.deposition / min_length;
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] = std::max(pheromones[node][key], config.min_pheromone);
                pheromones[key][node] = std::max(pheromones[key][node], config.min_pheromone);
                pheromones[node][key] = std::min(pheromones[node][key], config.max_pheromone);
                pheromones[key][node] = std::min(pheromones[key][node], config.max_pheromone);
            }
        }
        for (auto const &[key, val]: path_popularity) {
            if (val > choose_most_popular) {
                choose_most_popular = val;
                most_popular_length = key;
            }
        }
        most_popular_paths.push_back(paths_std[path_by_length[most_popular_length]]);
        std::cout << "Most popular " << iteration << ": " << most_popular_length << std::endl;
        std::cout << "Min length " << iteration << ": " << min_length << std::endl;
        iteration++;
    }
    write_to_csv(output_path, most_popular_paths, min_path, config.nodes, iteration);
}
