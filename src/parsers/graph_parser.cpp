#include "graph_parser.h"
#include <fstream>

std::vector<std::unordered_map<size_t, size_t>> parse_graph(const std::string &graph_path, size_t n) {
    std::vector<std::unordered_map<size_t, size_t>> edges(n);
    std::ifstream filestream(graph_path);
    size_t start;
    size_t end;
    size_t weight;
    while (filestream >> start) {
        filestream >> end;
        filestream >> weight;
        edges[start][end] = weight;
        edges[end][start] = weight;
    }
    return edges;
}