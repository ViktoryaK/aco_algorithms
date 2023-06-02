#include "gale_shapley_pm.h"
#include <vector>
#include <unordered_map>
#include "../parsers/ants_params.h"
#include <iostream>
#include "../graph_generation/write_to_csv.h"
#include "./tests.h"

bool new_is_worse(const std::vector<std::unordered_map<size_t, size_t>> &graph, size_t woman, size_t man,
                  size_t current_partner, const AntsParams &config) {
    for (size_t i = 0; i < config.nodes; ++i) {
        if (graph[woman + config.nodes].at(i) == current_partner)
            return true;
        if (graph[woman + config.nodes].at(i) == man)
            return false;
    }
    return false;
}

void gale_shapley_pm(const std::vector<std::unordered_map<size_t, size_t>> &graph, const std::vector<std::unordered_map<size_t, size_t>> &graph1, const AntsParams &config) {
    std::vector<bool> m_is_available(config.nodes, true);
    std::vector<size_t> w_partner(config.nodes, config.nodes + 1);
    size_t free_m = config.nodes;
    while (free_m > 0) {
        size_t man;
        for (man = 0; man < config.nodes; ++man) {
            if (m_is_available[man]) break;
        }
        for (size_t i = 0; (i < config.nodes) && m_is_available[man]; ++i) {
            size_t woman = graph[man].at(i);
            if (w_partner[woman] == config.nodes + 1) { ;
                w_partner[woman] = man;
                m_is_available[man] = false;
                free_m--;
            } else {
                size_t current_partner = w_partner[woman];
                if (!new_is_worse(graph, woman, man, current_partner, config)) {
                    w_partner[woman] = man;
                    m_is_available[man] = false;
                    m_is_available[current_partner] = true;
                }
            }
        }
    }
    std::vector<std::pair<size_t, size_t>> to_write;
    size_t total_size = 0;
    for (size_t i = 0; i < config.nodes; ++i) {
        to_write.emplace_back(w_partner[i], i);
        total_size += graph1[w_partner[i]].at(i);
    }
    std::cout << "Percent of stable matchings: " << percent_of_stable_m(graph1, to_write, config.nodes) << std::endl;
    std::cout << "Average women preference: " << average_preference(graph1, to_write, config.nodes, true) << std::endl;
    std::cout << "Average men preference: " << average_preference(graph1, to_write, config.nodes, false) << std::endl;
}

