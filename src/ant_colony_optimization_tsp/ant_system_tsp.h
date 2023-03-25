#ifndef UNTITLED6_ANT_SYSTEM_H
#define UNTITLED6_ANT_SYSTEM_H

#include <vector>
#include <boost/program_options.hpp>
#include "../parsers/ants_params.h"
#include <map>

void ant_system(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config);

#endif //UNTITLED6_ANT_SYSTEM_H
