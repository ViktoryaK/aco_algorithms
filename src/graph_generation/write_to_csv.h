//
// Created by klyms on 27.03.2023.
//

#ifndef ACO_ALGORITHMS_WRITE_TO_CSV_H
#define ACO_ALGORITHMS_WRITE_TO_CSV_H

#include <vector>
#include "../parsers/ants_params.h"
#include <string>

void write_to_csv(const std::string &output_path,
                  const std::vector<std::vector<std::pair<size_t, size_t>>> &most_popular_paths,
                  const std::vector<std::pair<size_t, size_t>> &min_path, size_t nodes, size_t iterations);

#endif //ACO_ALGORITHMS_WRITE_TO_CSV_H
