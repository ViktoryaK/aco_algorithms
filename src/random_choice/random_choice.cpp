#include "random_choice.h"
#include <random>

size_t random_choice(const std::vector<double> &probabilities, const std::vector<size_t> &choose_from) {
    std::mt19937 gen(std::random_device{}());
    std::discrete_distribution<std::size_t> distribution{probabilities.begin(), probabilities.end()};
    return choose_from[distribution(gen)];
}