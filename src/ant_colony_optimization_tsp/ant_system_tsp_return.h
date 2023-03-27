#ifndef UNTITLED6_ANT_SYSTEM_H
#define UNTITLED6_ANT_SYSTEM_H

#include <vector>
#include <boost/program_options.hpp>
#include "../parsers/ants_params.h"
#include <map>
#include <string>

void ant_system_return(const std::vector<std::unordered_map<size_t, double>> &graph, const AntsParams &config,
                       const std::string &output_path);

#endif //UNTITLED6_ANT_SYSTEM_H
