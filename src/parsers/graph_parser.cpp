#include "graph_parser.h"
#include <fstream>

std::vector<std::vector<std::pair<int, int>>> parse_graph(const std::string &graph_path, int n) {
    std::vector<std::vector<std::pair<int, int>>> edges(n);
    std::ifstream filestream(graph_path);
    int start;
    int end;
    int weight;
    while (filestream >> start) {
        filestream >> end;
        filestream >> weight;
        edges[start].emplace_back(end, weight);
        edges[end].emplace_back(start, weight);
    }
    return edges;
}