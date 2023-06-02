//
// Created by klyms on 27.03.2023.
//

#include "write_to_csv.h"
#include <fstream>
#include <iostream>

void write_to_csv(const std::string &output_path,
                  const std::vector<std::vector<std::pair<size_t, size_t>>> &most_popular_paths,
                  const std::vector<std::pair<size_t, size_t>> &min_path, size_t nodes, size_t iterations) {
    std::ofstream file_csv;
    file_csv.open(output_path);
    for (size_t i = 0; i < iterations - 1; ++i) {
        file_csv << "path_" << i << ",";
        for (size_t elem = 0; elem < nodes - 2; ++elem) {
            file_csv << most_popular_paths[i][elem].first << " " << most_popular_paths[i][elem].second << ",";
        }
        file_csv << most_popular_paths[i][nodes - 2].first << " "
                 << most_popular_paths[i][nodes - 2].second << "\n";
    }
    file_csv << "min_path,";
    for (size_t elem = 0; elem < nodes - 2; ++elem) {
        file_csv << min_path[elem].first << " " << min_path[elem].second << ",";
    }
    file_csv << min_path[nodes - 2].first << " "
             << min_path[nodes - 2].second << "\n";


    file_csv.close();
}


void write_to_csv_mp(const std::string &output_path,
                  const std::vector<std::vector<std::pair<size_t, size_t>>> &most_popular_paths,
                  const std::vector<std::pair<size_t, size_t>> &min_path, size_t nodes, size_t iterations) {
    std::ofstream file_csv;
    file_csv.open(output_path);
    for (size_t i = 0; i < iterations - 1; ++i) {
        file_csv << "path_" << i << ",";
        for (size_t elem = 0; elem < nodes - 1; ++elem) {
            file_csv << most_popular_paths[i][elem].first << " " << most_popular_paths[i][elem].second << ",";
        }
        file_csv << most_popular_paths[i][nodes - 1].first << " "
                 << most_popular_paths[i][nodes - 1].second << "\n";
    }
    std::cout << 1 << std::endl;
    file_csv << "min_path,";
    for (size_t elem = 0; elem < nodes - 1; ++elem) {
        file_csv << min_path[elem].first << " " << min_path[elem].second << ",";
    }
    file_csv << min_path[nodes - 1].first << " "
             << min_path[nodes - 1].second << "\n";


    file_csv.close();
}