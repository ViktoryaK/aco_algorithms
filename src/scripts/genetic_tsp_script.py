import argparse
import subprocess
from math import inf
import matplotlib.pyplot as plt
import numpy as np
from statistics import stdev

def run_genetic(graph_path, config_path, paths_path, repetitions):
    task_paths = "./bin/genetic_algorithm"
    process = subprocess.Popen([task_paths] + [config_path, graph_path, paths_path, str(repetitions)],
                               stdout=subprocess.PIPE)
    output, error = process.communicate()
    output_str = output.decode("utf-8")
    output = output_str.split("\n")
    return output[:-1]


def get_res(graph_path, config_path, paths_path, repetitions):
    repetitions = int(repetitions)
    funcs_res = []
    total_times = []
    funcs_res.append([])
    cur_times = []
    for i in range(repetitions):
        func_res = run_genetic(graph_path, config_path, paths_path, i)
        res_n = []
        for j in range(0, len(func_res) - 1, 2):
            res_n.append((float(func_res[j].split(":")[1])))
        funcs_res[-1].append(res_n)
        cur_times.append(int(func_res[-1].split("=")[1]))
    total_times.append(cur_times)
    return funcs_res, total_times



def build_graph(res, path_to_save, min_value):
    x = res
    y = [i for i, j in enumerate(res)]
    plt.plot(y, x)
    plt.axhline(y=min_value)
    plt.xlabel('Number of generations')
    plt.ylabel('Path length')
    title = "Genetic algorithm graph"
    # plt.ylim(min_value, 8000)
    # plt.yticks(np.arange(min_value // 100 * 100, 8000, 250))
    plt.title(title)
    plt.legend()
    plt.savefig(path_to_save)
    plt.cla()





if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('config', type=str, help='Path to config file')
    args = parser.parse_args()
    dir_path = args.dir_path
    config_temp = dir_path + "/config_temp.cfg"
    paths_temp = dir_path + "/path_temp.csv"
    min_path = dir_path + "/min_path.txt"
    with open(min_path, "r") as min_v:
        for line in min_v:
            minimum_value = float(line.strip())
    results, times = get_res(args.graph, args.config, paths_temp, 500)
    results_new = [result[0] for result in results[0]]
    build_graph(results_new, dir_path + "/gen.pdf", minimum_value)