// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#ifndef INTEGRATE_SERIAL_PARSER_H
#define INTEGRATE_SERIAL_PARSER_H

#include <string>
#include <boost/program_options.hpp>

boost::program_options::variables_map parse(const std::string &config_file);

#endif //INTEGRATE_SERIAL_PARSER_H
