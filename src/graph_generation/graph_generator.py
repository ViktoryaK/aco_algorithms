import random
import argparse


def create_full_weighted_graph(n, min, max):
    graph = []
    for i in range(n):
        graph.append([0] * n)
    for i in range(n):
        for j in range(i + 1, n):

            weight = random.randint(min, max)
            graph[i][j] = weight
            graph[j][i] = weight
    return graph


if __name__ == "__main__":

    args = parser.parse_args()
    nodes_n = args.nodes_nparser = argparse.ArgumentParser(
        description='Python script for graph generation')
    parser.add_argument('file_path', type=str,  help='Path to output file')
    parser.add_argument('nodes_n', type=int,  help='Number of nodes')
    parser.add_argument('completeness', type=int, help='0 - not complete graph, 1 - complete')
    parser.add_argument('weighting', type=int, help='0 - not weighted graph, 1 - weighted')
    parser.add_argument('-min_weight', '-min', type=int, help='Min weight of edge')
    parser.add_argument('-max_weight', '-max', type=int, help='Max weight of edge')
    completeness = args.completeness
    weighting = args.weighting
    if args.min_weight is not None:
        min_weight = args.min_weight
    else:
        min_weight = 1
    if args.max_weight is not None:
        max_weight = args.max_weight
    else:
        max_weight = 1000
    if completeness == 1 and weighting == 1:
        graph = create_full_weighted_graph(nodes_n, min_weight, max_weight)
    with open(args.file_path, "w") as file:
        for i in range(nodes_n):
            for j in range(i + 1, nodes_n):
                file.write(str(i) + " " + str(j) + " " + str(graph[i][j]) + "\n")
