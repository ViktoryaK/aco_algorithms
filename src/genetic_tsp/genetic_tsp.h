#ifndef ACO_ALGORITHMS_GENETIC_TSP_H
#define ACO_ALGORITHMS_GENETIC_TSP_H
#include <vector>
#include <unordered_map>
std::vector<size_t> create_individual(size_t number_of_cities);

std::vector<std::vector<size_t>> initialize_population(size_t size, size_t number_of_cities);

double calculate_length(const std::vector<std::unordered_map<size_t, double>> &graph, std::vector<size_t> &path);

std::vector<size_t> make_son(std::vector<size_t> &parent1, std::vector<size_t> &parent2);

std::vector<std::vector<size_t>> nextGeneration(std::vector<std::vector<size_t>> &current, const std::vector<std::unordered_map<size_t, double>> &graph, size_t size_of_population);

size_t execute_genetic(size_t size, size_t number_of_cities, size_t number_of_generations,  const std::vector<std::unordered_map<size_t, double>> &graph);
#endif //ACO_ALGORITHMS_GENETIC_TSP_H
