#include "graph_parser.h"
#include <fstream>

std::vector<std::unordered_map<size_t, double>> parse_graph(const std::string &graph_path, size_t n) {
    std::vector<std::unordered_map<size_t, double>> edges(n);
    std::ifstream filestream(graph_path);
    size_t start;
    size_t end;
    double weight;
    while (filestream >> start) {
        filestream >> end;
        filestream >> weight;
        edges[start][end] = weight;
        edges[end][start] = weight;
    }
    return edges;
}