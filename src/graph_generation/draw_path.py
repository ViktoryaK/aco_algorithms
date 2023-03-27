import pandas as pd
import argparse
import matplotlib.pyplot as plt


def draw_full(nodes_file, output_path, path_name, paths_csv):
    nodes = get_nodes(nodes_file)
    for idx, node in enumerate(nodes):
        x = int(node[0])
        y = int(node[1])
        plt.scatter(x, y)
        plt.text(x + .03, y + .03, idx, fontsize=9)

    df = pd.read_csv(paths_csv, header=None, index_col=0)
    for i in range(1, len(nodes) + 1):
        curr_path = df.loc[path_name][i].split()
        x_values = [int(nodes[int(curr_path[0])][0]), int(nodes[int(curr_path[1])][0])]
        y_values = [int(nodes[int(curr_path[0])][1]), int(nodes[int(curr_path[1])][1])]
        plt.plot(x_values, y_values, )
    plt.savefig(output_path)


def draw(nodes_file, output_path, path_name, paths_csv):
    nodes = get_nodes(nodes_file)
    for idx, node in enumerate(nodes):
        x = int(node[0])
        y = int(node[1])
        plt.scatter(x, y)
        plt.text(x + .03, y + .03, idx, fontsize=9)

    df = pd.read_csv(paths_csv, header=None, index_col=0)
    for i in range(1, len(nodes)):
        curr_path = df.loc[path_name][i].split()
        x_values = [int(nodes[int(curr_path[0])][0]), int(nodes[int(curr_path[1])][0])]
        y_values = [int(nodes[int(curr_path[0])][1]), int(nodes[int(curr_path[1])][1])]
        plt.plot(x_values, y_values, )
    plt.savefig(output_path)


def get_nodes(path):
    dots = []
    with open(path, "r") as nodes:
        content = nodes.read()
        lines = content.split("\n")
        for line in lines:
            if line != "":
                x_y = line.split(" ")
                dots.append((x_y[0], x_y[1]))
    return dots


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for graph generation')
    parser.add_argument('graph_path', type=str, help='Path to graph file')
    parser.add_argument('paths_csv', type=str, help='Path to file paths')
    parser.add_argument('output_path', type=str, help='Path to output img file')
    parser.add_argument('path_name', type=str, help='Name of path to construct on graph')
    parser.add_argument('full', type=int, help='Draw for full path or not')
    args = parser.parse_args()
    if args.full == 0:
        draw(args.graph_path, args.output_path, args.path_name, args.paths_csv)
    else:
        draw_full(args.graph_path, args.output_path, args.path_name, args.paths_csv)
