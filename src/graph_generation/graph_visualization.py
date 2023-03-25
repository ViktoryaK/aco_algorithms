import matplotlib.pyplot as plt
import networkx as nx
import argparse


def visualize(graph_path, output_path):
    G = nx.Graph()
    with open(graph_path, 'r') as file:
        content = file.read()
        lines = content.split("\n")
        for line in lines:
            if line != "":
                start, end, weight = line.split()
                G.add_edge(start, end, weight=int(weight))

    edge_list = [(u, v) for (u, v, d) in G.edges(data=True)]
    pos = nx.shell_layout(G)
    nx.draw_networkx_nodes(G, pos, node_size=100)
    nx.draw_networkx_edges(G, pos, edgelist=edge_list, width=1)

    nx.draw_networkx_labels(G, pos, font_size=10, font_family="sans-serif")
    edge_labels = nx.get_edge_attributes(G, "weight")
    nx.draw_networkx_edge_labels(G, pos, edge_labels, font_size=5)

    ax = plt.gca()
    ax.margins(0.08)
    plt.axis("off")
    plt.tight_layout()
    plt.savefig(output_path)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Graph visualization')
    parser.add_argument('graph_path', type=str, help='Path to input file')
    parser.add_argument('output_path', type=str, help='Path to output file')
    args = parser.parse_args()
    visualize(args.graph_path, args.output_path)
