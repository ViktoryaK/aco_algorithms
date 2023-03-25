import random
import argparse
import matplotlib.pyplot as plt

def create_map_graph(n, min, max):
    graph_edges = []
    graph_nodes = []
    for i in range(n):
        x = random.randint(min, max)
        y = random.randint(min, max)
        for j, node in enumerate(graph_nodes):
            distance = ((x - node[0]) ** 2 + (y - node[1]) ** 2) ** (1/2)
            graph_edges.append((j, len(graph_nodes), distance))
        graph_nodes.append((x, y))
    return graph_edges, graph_nodes


def visualize_nodes(graph, output_path_img, output_path_nodes):
    with open(output_path_nodes, "w") as file:
        for idx, node in enumerate(graph):
            x = node[0]
            y = node[1]
            file.write(str(x) + " " + str(y) + " " +'\n')
            plt.scatter(x, y)
            plt.text(x+.03, y+.03, idx, fontsize=9)
    plt.savefig(output_path_img)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for graph generation')
    parser.add_argument('edge_path', type=str, help='Path to output edge file')
    parser.add_argument('node_path', type=str, help='Path to output node file')
    parser.add_argument('img_path', type=str, help='Path to img output file')
    parser.add_argument('nodes_n', type=int, help='Number of nodes')
    parser.add_argument('-min_pos', '-min', type=int, help='Min x and y')
    parser.add_argument('-max_pos', '-max', type=int, help='Max x and y')
    args = parser.parse_args()
    nodes_n = args.nodes_n
    if args.min_pos is not None:
        min_pos = args.min_pos
    else:
        min_pos = 0
    if args.max_pos is not None:
        max_pos = args.max_pos
    else:
        max_pos = 1000
    graph_edges, graph_nodes = create_map_graph(nodes_n, min_pos, max_pos)
    visualize_nodes(graph_nodes, args.img_path, args.node_path)
    with open(args.edge_path, "w") as file:
        for edge in graph_edges:
            file.write(str(edge[0]) + " " + str(edge[1]) + " " + str(edge[2]) + "\n")