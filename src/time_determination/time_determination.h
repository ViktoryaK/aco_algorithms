// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#ifndef ACO_ALGORITHMS_TIME_DETERMINATION_H
#define ACO_ALGORITHMS_TIME_DETERMINATION_H


#include <chrono>

template<class D>
inline long long to_us(const D &d) {
    return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
}

std::chrono::high_resolution_clock::time_point get_current_time_fenced();


#endif //ACO_ALGORITHMS_TIME_DETERMINATION_H
