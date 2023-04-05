#include "max_choice.h"

size_t max_choice(const std::vector<double> &probabilities, const std::vector<size_t> &choose_from) {
    double max = 0;
    size_t max_iter = 0;
    size_t length = probabilities.size();
    for (size_t i = 0; i < length; ++i){
        if (max < probabilities[i]){
            max_iter = i;
            max = probabilities[i];
        }
    }
    return choose_from[max_iter];
}