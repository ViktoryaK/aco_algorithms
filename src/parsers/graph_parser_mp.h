#ifndef ACO_ALGORITHMS_GRAPH_PARSER_MP_H
#define ACO_ALGORITHMS_GRAPH_PARSER_MP_H

#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::unordered_map<size_t, size_t>> parse_graph_mp(const std::string &graph_path, size_t n);

std::vector<std::unordered_map<size_t, size_t>> parse_graph_mp_wrong(const std::string &graph_path, size_t n);

std::vector<std::unordered_map<size_t, size_t>> parse_graph_gale_mp(const std::string &graph_path, size_t n);

#endif //ACO_ALGORITHMS_GRAPH_PARSER_MP_H
