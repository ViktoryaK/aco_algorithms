#include "genetic_tsp.h"
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_map>

std::vector<size_t> create_individual(size_t number_of_cities) {
    std::vector<size_t> cities(number_of_cities);
    std::iota(cities.begin(), cities.end(), 0);
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(cities), std::end(cities), rng);
    return cities;
}

std::vector<std::vector<size_t>> initialize_population(size_t size, size_t number_of_cities) {
    std::vector<std::vector<size_t>> population;
    for (size_t i=0; i<size; ++i) {
        population.push_back(create_individual(number_of_cities));
    }
    return population;
}

double calculate_length(const std::vector<std::unordered_map<size_t, double>> &graph, std::vector<size_t> &path) {
    double length = 0;
    for (size_t i=0; i<path.size()-1; ++i) {
        length += graph[path[i]].at(path[i+1]);
    }
    return length;
}

std::vector<size_t> make_son(std::vector<size_t> &parent1, std::vector<size_t> &parent2) {
    std::vector<size_t> son;
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<size_t> dist(0, parent1.size());
    size_t index_1 = dist(mt);
    size_t index_2 = dist(mt);
    if (index_1 < index_2) {
        for (size_t i = index_1; i < index_2; ++i) {
            son.push_back(parent1[i]);
        }
    } else {
        for (size_t i = index_2; i < index_1; ++i) {
            son.push_back(parent1[i]);
        }
    }
    for (size_t elem: parent2) {
        if (std::find(son.begin(), son.end(), elem) == son.end()) {
            son.push_back(elem);
        }
    }
    return son;
}


std::vector<std::vector<size_t>> nextGeneration(std::vector<std::vector<size_t>> &current, const std::vector<std::unordered_map<size_t, double>> &graph, size_t size_of_population) {
    std::unordered_map<double, size_t> index_to_sort;
    std::vector<double> lengths;
    for (size_t i = 0; i < size_of_population; ++i) {
        double res = calculate_length(graph, current[i]);
        index_to_sort.emplace(res, i);
        lengths.push_back(res);
    }
    std::vector<std::vector<size_t>> new_population = current;
    sort(lengths.begin(), lengths.end());
    for (size_t i = 0; i < size_of_population; i+=2) {
        new_population.push_back(make_son(current[index_to_sort[lengths[i]]], current[index_to_sort[lengths[i+1]]]));
        new_population.push_back(make_son(current[index_to_sort[lengths[i]]], current[index_to_sort[lengths[i+1]]]));
    }
    std::unordered_map<double, size_t> index_to_sort2;
    std::vector<double> lengths2;
    for (size_t i = 0; i < new_population.size(); ++i) {
        double res = calculate_length(graph, new_population[i]);
        index_to_sort2.emplace(res, i);
        lengths2.push_back(res);
    }
    sort(lengths2.begin(), lengths2.end());
    std::vector<std::vector<size_t>> final;
    for (size_t i = 0; i < size_of_population; ++i) {
        final.push_back(new_population[index_to_sort2[lengths2[i]]]);
    }
    return final;
}




size_t execute_genetic(size_t size, size_t number_of_cities, size_t number_of_generations,  const std::vector<std::unordered_map<size_t, double>> &graph) {
    std::vector<std::vector<std::vector<size_t>>> generations(number_of_generations+1);
    generations[0] = initialize_population(size, number_of_cities);
    for (size_t generation = 0; generation<number_of_generations; ++generation) {
        generations[generation+1] = nextGeneration(generations[generation], graph, size);
    }
    std::unordered_map<double, size_t> index_to_sort;
    std::vector<double> lengths;
    for (size_t i = 0; i < size; ++i) {
        double res = calculate_length(graph, generations[number_of_generations][i]);
        index_to_sort.emplace(res, i);
        lengths.push_back(res);
    }
    sort(lengths.begin(), lengths.end());
    return lengths[0];
}


