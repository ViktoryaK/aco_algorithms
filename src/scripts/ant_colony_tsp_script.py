import argparse
import subprocess
from math import inf
import matplotlib.pyplot as plt
import numpy as np


def run_task(graph_path, config_path, paths_path, func_num):
    task_paths = "./bin/aco_algorithms"
    process = subprocess.Popen([task_paths] + [config_path, graph_path, paths_path, str(func_num), "0"],
                               stdout=subprocess.PIPE)
    output, error = process.communicate()
    output_str = output.decode("utf-8")
    output = output_str.split("\n")
    return output[:-1]


def get_res(graph_path, config_path, config_path_mm, paths_path, n):
    funcs_res = []
    for i in range(1, 5):
        funcs_res.append([])
        for _ in range(n):
            if i == 4:
                config_path = config_path_mm
            func_res = run_task(graph_path, config_path, paths_path, i)
            res_n = []
            for j in range(0, len(func_res), 2):
                res_n.append((float(func_res[j].split(": ")[1]), float(func_res[j + 1].split(": ")[1])))
            funcs_res[-1].append(res_n)
    return funcs_res

def build_graph_min(min_res, min_value, number_of_f, path_to_save_min):
    titles = ["ACO", "Elitism", "ACS", "MMAS"]
    x = [elem[0] for elem in min_res[number_of_f]]
    y = [i for i, j in enumerate(min_res[number_of_f])]
    plt.plot(y, x, label='Most popular')
    x_1 = [elem[1] for elem in min_res[number_of_f]]
    plt.plot(y, x_1, label='Minimum')
    plt.axhline(y=min_value)
    plt.xlabel('Number of iterations')
    plt.ylabel('Path length')
    title = "Min graph for " + titles[number_of_f] + " algorithm"
    plt.title(title)
    plt.legend()
    plt.savefig(path_to_save_min)
    plt.cla()


def build_graph_avg(avg_res, min_value, number_of_f,  path_to_save_avg):
    titles = ["ACO", "Elitism", "ACS", "MMAS"]
    x = [elem[0] for elem in avg_res[number_of_f]]
    y = [i for i, j in enumerate(avg_res[number_of_f])]
    plt.plot(y, x, label='Most popular')
    x_1 = [elem[1] for elem in avg_res[number_of_f]]
    plt.plot(y,x_1, label='Minimum')
    plt.axhline(y=min_value)
    plt.xlabel('Number of iterations')
    plt.ylabel('Path length')
    title = "Average graph for " + titles[number_of_f] + " algorithm"
    plt.title(title)
    plt.legend()
    plt.savefig(path_to_save_avg)
    plt.cla()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('repetitions', type=int, help='Number of repetitions of running functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('config', type=str, help='Path to config file')
    parser.add_argument('config_min_max', type=str, help='Path to min max config file')
    args = parser.parse_args()
    config_temp = args.dir_path + "/config_temp.cfg"
    paths_temp = args.dir_path + "/path_temp.csv"
    min_path = args.dir_path + "/min_path.txt"
    results = get_res(args.graph, args.config, args.config_min_max, paths_temp, args.repetitions)
    min_res = []
    avg_res = []
    for res_i in results:
        minimum = inf
        min_res_i = res_i[0]
        avg_res_i = []
        for _ in range(len(res_i[0])):
            avg_res_i.append([0, 0])
        for res in res_i:
            if res[-1][0] < minimum:
                min_res_i = res
                minimum = res[-1][0]
            for edge in range(len(res_i[0])):
                avg_res_i[edge][0] += res[edge][0]
                avg_res_i[edge][1] += res[edge][1]
        for edge in range(len(res_i[0])):
            avg_res_i[edge][0] /= len(res_i)
            avg_res_i[edge][1] /= len(res_i)
        min_res.append(min_res_i)
        avg_res.append(avg_res_i)

    with open(min_path, "r") as min_v:
        for line in min_v:
            minimum_value = float(line.strip())
    build_graph_min(min_res, minimum_value, 0, "./min_0.jpg")
    build_graph_avg(avg_res, minimum_value, 0, "./avg_0.jpg")
    build_graph_min(min_res, minimum_value, 1, "./min_1.jpg")
    build_graph_avg(avg_res, minimum_value, 1, "./avg_1.jpg")
    build_graph_min(min_res, minimum_value, 2, "./min_2.jpg")
    build_graph_avg(avg_res, minimum_value, 2, "./avg_2.jpg")
    build_graph_min(min_res, minimum_value, 3, "./min_3.jpg")
    build_graph_avg(avg_res, minimum_value, 3, "./avg_3.jpg")
