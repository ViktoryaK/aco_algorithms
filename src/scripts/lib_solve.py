import argparse
import numpy as np
from python_tsp.exact import solve_tsp_dynamic_programming
from python_tsp.heuristics import solve_tsp_local_search
from math import inf


def build_matrix(path_to_graph, nodes):
    s = (nodes, nodes)
    input_matrix = np.zeros(s)
    with open(path_to_graph) as file:
        for line in file:
            l = line.split(" ")
            input_matrix[int(l[0])][int(l[1])] = float(l[2])
            input_matrix[int(l[1])][int(l[0])] = float(l[2])
    input_matrix[:, 0] = 0
    return input_matrix


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for graph generation')
    parser.add_argument('file_path', type=str, help='Path to input file')
    parser.add_argument('nodes_n', type=int, help='Number of nodes')
    parser.add_argument('output', type=str, help='Path to output file')
    parser.add_argument('heuristic', type=int, help='1 if heuristic algo, 0 otherwise')
    args = parser.parse_args()
    matrix = build_matrix(args.file_path, args.nodes_n)
    if args.heuristic == 0:
        permutation, distance = solve_tsp_dynamic_programming(matrix)
        print(distance)
    else:
        distance = inf
        for i in range(100):
            permutation, cur_distance = solve_tsp_local_search(matrix)
            distance = min(distance, cur_distance)
        print(distance)
    with open(args.output, "w") as file:
        file.write(str(distance))

