#include "ant_system_pm_par.h"
#include <iostream>
#include "../random_choice/random_choice.h"
#include "../graph_generation/write_to_csv.h"
#include <random>
#include <future>
#include "../gale_shapley_pm/tests.h"
#include <boost/asio/thread_pool.hpp>
#include <boost/asio.hpp>


void ant_run_pm(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
                const std::vector<std::unordered_map<size_t, size_t>> &graph,
                std::vector<std::pair<size_t, size_t>> &ant_path, size_t i) {
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
        ant_path.emplace_back(node, chosen);
        node++;
        visited[chosen] = true;
    }
}

void ant_run_pm_min(const std::vector<std::vector<double>> &pheromones, const AntsParams &config,
                    const std::vector<std::unordered_map<size_t, size_t>> &graph,
                    std::vector<std::pair<size_t, size_t>> &ant_path) {
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
        ant_path.emplace_back(node, chosen);
        node++;
        visited[chosen] = true;
    }
}

void ant_system_pm_min_par(size_t number_of_threads, const std::vector<std::unordered_map<size_t, size_t>> &graph,
                           const std::vector<std::unordered_map<size_t, size_t>> &graph_2, const AntsParams &config) {
    boost::asio::thread_pool pool(number_of_threads);
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }

    size_t min_length = std::numeric_limits<size_t>::max();
    std::vector<std::pair<size_t, size_t>> min_path;
    size_t iteration = 0;
    while (iteration < config.max_iter) {
        std::vector<std::promise<std::vector<std::pair<size_t, size_t>>>> paths(config.ants_n);
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run_pm_min(pheromones, config, graph, ant_path);
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
            size_t total_length = 0;
            for (std::pair<size_t, size_t> path: cur_path) {
                total_length += graph[path.first].at(path.second);
            }
            if (total_length < min_length) {
                min_length = total_length;
                min_path = cur_path;
            }
            for (std::pair<size_t, size_t> path: cur_path) {
                pheromones[path.first].at(path.second) += config.deposition / total_length;
            }
        }
        iteration++;
    }
    std::cout << min_length << std::endl;
    std::cout << "Percent of stable matchings: " << percent_of_stable_m(graph_2, min_path, config.nodes) << std::endl;
    std::cout << "Average women preference: " << average_preference(graph_2, min_path, config.nodes, true) << std::endl;
    std::cout << "Average men preference: " << average_preference(graph_2, min_path, config.nodes, false) << std::endl;
}

void ant_system_pm_par(size_t number_of_threads, const std::vector<std::unordered_map<size_t, size_t>> &graph,
                       const AntsParams &config) {
    boost::asio::thread_pool pool(number_of_threads);
    std::vector<std::vector<double>> pheromones;
    for (size_t node = 0; node < config.nodes * 2; ++node) {
        pheromones.emplace_back(config.nodes, config.init_pheromone);
    }
    size_t iteration = 0;
    std::vector<std::vector<std::pair<size_t, size_t>>> paths_std;
    while (iteration < config.max_iter) {
        paths_std.clear();
        std::vector<std::promise<std::vector<std::pair<size_t, size_t>>>> paths(config.ants_n * 2);
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run_pm(pheromones, config, graph, ant_path, 0);
                paths[ant].set_value(ant_path);
            });
        }
        for (size_t node = 0; node < config.nodes; ++node) {
            for (auto const &[key, val]: graph[node]) {
                pheromones[node][key] *= 1 - config.evaporation_rate;
                pheromones[key + config.nodes][node] *= 1 - config.evaporation_rate;
            }
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            auto cur_path = paths[ant].get_future().get();
            paths_std.push_back(cur_path);
            for (size_t person = 0; person < config.nodes; ++person) {
                pheromones[cur_path[person].first].at(
                        cur_path[person].second) += config.deposition;
                pheromones[cur_path[person].second + config.nodes].at(
                        cur_path[person].first) += config.deposition;
            }
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            std::vector<std::pair<size_t, size_t>> ant_path;
            boost::asio::post(pool, [&paths, &pheromones, &config, &graph, ant]() {
                std::vector<std::pair<size_t, size_t>> ant_path;
                ant_run_pm(pheromones, config, graph, ant_path, 1);
                paths[config.ants_n + ant].set_value(ant_path);
            });
        }
        for (size_t ant = 0; ant < config.ants_n; ++ant) {
            auto cur_path = paths[config.ants_n + ant].get_future().get();
            paths_std.push_back(cur_path);
            for (size_t person = 0; person < config.nodes; ++person) {
                pheromones[cur_path[person].first + config.nodes].at(
                        cur_path[person].second) += config.deposition;
                pheromones[cur_path[person].second].at(
                        cur_path[person].first) += config.deposition;
            }
        }
        iteration++;
    }
    double max_pheromone = 0;
    size_t final_path = 0;
    for (size_t ant = 0; ant < config.ants_n; ++ant) {
        double pheromone = 0;
        for (size_t pair = 0; pair < config.nodes; ++pair) {
            pheromone += pheromones[paths_std[ant][pair].first][paths_std[ant][pair].second];
        }
        if (max_pheromone < pheromone) {
            final_path = ant;
        }
    }
    std::cout << "Percent of stable matchings: " << percent_of_stable_m(graph, paths_std[final_path], config.nodes)
              << std::endl;
    std::cout << "Average women preference: " << average_preference(graph, paths_std[final_path], config.nodes, true)
              << std::endl;
    std::cout << "Average men preference: " << average_preference(graph, paths_std[final_path], config.nodes, false)
              << std::endl;
}