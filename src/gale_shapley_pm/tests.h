#ifndef ACO_ALGORITHMS_TESTS_H
#define ACO_ALGORITHMS_TESTS_H

#include <vector>
#include <unordered_map>

bool is_stable(size_t man, size_t woman, const std::vector<std::unordered_map<size_t, size_t>> &preferences, std::vector<std::pair<size_t, size_t>> &matchings, size_t n);

double percent_of_stable_m(const std::vector<std::unordered_map<size_t, size_t>> &preferences, std::vector<std::pair<size_t, size_t>> &matchings, size_t n);

double average_preference(const std::vector<std::unordered_map<size_t, size_t>> &preferences, std::vector<std::pair<size_t, size_t>> &matches, size_t n, bool woman);
#endif //ACO_ALGORITHMS_TESTS_H
