#include "graph_parser_mp.h"
#include <fstream>
#include <iostream>



std::vector<std::unordered_map<size_t, size_t>> parse_graph_mp(const std::string &graph_path, size_t n) {
    std::vector<std::unordered_map<size_t, size_t>> edges(n * 2);
    std::ifstream filestream(graph_path);
    size_t weight;
    for (size_t i = 0; i < n * 2; ++i) {
        for (size_t j = 0; j < n; ++j) {
            filestream >> weight;
            edges[i][j] = weight;
        }
    }
    return edges;
}


std::vector<std::unordered_map<size_t, size_t>> parse_graph_mp_wrong(const std::string &graph_path, size_t n) {
    std::vector<std::unordered_map<size_t, size_t>> edges(n);
    std::ifstream filestream(graph_path);
    size_t weight;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            filestream >> weight;
            edges[i][j] = weight;
        }
    }
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            filestream >> weight;
            edges[j][i] += weight;
        }
    }
    return edges;
}


std::vector<std::unordered_map<size_t, size_t>> parse_graph_gale_mp(const std::string &graph_path, size_t n) {
    std::vector<std::unordered_map<size_t, size_t>> edges(n * 2);
    std::ifstream filestream(graph_path);
    size_t weight;
    for (size_t i = 0; i < n * 2; ++i) {
        edges[i].reserve(n);
        for (size_t j = 0; j < n; ++j) {
            filestream >> weight;
            edges[i][weight - 1] = j;
        }
    }
    return edges;
}