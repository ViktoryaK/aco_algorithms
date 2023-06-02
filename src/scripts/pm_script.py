import argparse
import subprocess
from math import inf
import matplotlib.pyplot as plt
import numpy as np
from statistics import stdev


def time_graph(times):
    threads = [1, 2, 4, 6, 8, 12]
    coefficient_list = [times[0] / time / threads[i] for i, time in enumerate(times)]
    bar_width = 0.25
    br1 = np.arange(len(threads))
    plt.bar(br1, coefficient_list, color='darkviolet', width=bar_width)
    plt.xlabel("Number of threads")
    plt.ylabel("Coefficient")
    plt.xticks([r for r in range(len(threads))], threads)
    plt.title(f"Effectiveness of parallelization coefficient")
    plt.legend()
    plt.savefig(f"data/efficiency.pdf")
    plt.cla()

    br1 = np.arange(len(threads))
    plt.bar(br1, times, color='darkviolet', width=bar_width)
    plt.xlabel("Number of threads")
    plt.ylabel("Time")
    plt.xticks([r for r in range(len(threads))], threads)
    plt.title(f"Time plot for function")
    plt.legend()
    plt.savefig(f"data/time.pdf")
    plt.cla()


def run_task_par(graph_path, config_path, thread, func_num):
    task_paths = "./bin/aco_algorithms_mp_par"
    process = subprocess.Popen([task_paths] + [config_path, graph_path, str(func_num), str(thread)],
                               stdout=subprocess.PIPE)
    output, error = process.communicate()
    output_str = output.decode("utf-8")
    output = output_str.split("\n")
    print(output)
    return output[:-1]


def get_res_par(graph_path, config_path, n, threads):
    results = []
    total_times = []
    for thread in threads:
        thread_results = []
        thread_times = []
        print(f"Running thread {thread}")
        for _ in range(n):
            func_res = []
            func_times = []
            for i in range(3):
                print(i)
                res = run_task_par(graph_path, config_path, thread, i)
                func_res.append(
                    [float(res[0].split(": ")[1]), float(res[1].split(": ")[1]), float(res[2].split(": ")[1])])
                func_times.append(int(res[-1].split("=")[1]))
            thread_results.append(func_res)
            thread_times.append(func_times)
        total_times.append(thread_times)
        results.append(thread_results)
    return results, total_times


def run_task(graph_path, config_path, func_num):
    task_paths = "./bin/aco_algorithms_mp"
    process = subprocess.Popen([task_paths] + [config_path, graph_path, str(func_num)],
                               stdout=subprocess.PIPE)
    output, error = process.communicate()
    output_str = output.decode("utf-8")
    output = output_str.split("\n")
    return output[:-1]


def get_res(graph_path, config_path, n):
    total_times = []
    total_res = []
    for j in range(3):
        res = []
        times = []
        for i in range(3):
            size_res = []
            size_times = []
            for _ in range(n):
                func_res = run_task(graph_path[j], config_path[j], i)
                size_res.append(
                    [float(func_res[0].split(": ")[1]), float(func_res[1].split(": ")[1]), float(func_res[2].split(": ")[1])])
                size_times.append(int(func_res[-1].split("=")[1]))
            res.append(size_res)
            times.append(size_times)
        total_res.append(res)
        total_times.append(times)
    return total_res, total_times


def build_graph(index_1):
    bar_width = 0.25
    br1 = np.arange(len(index_1[0]))
    br2 = [x + bar_width for x in br1]
    br3 = [x + 2 * bar_width for x in br1]
    plt.bar(br1, index_1[0], color='red', width=bar_width, label="10 pairs")
    plt.bar(br2, index_1[1], color='black', width=bar_width, label="100 pairs")
    plt.bar(br3, index_1[2], color='darkviolet', width=bar_width, label="1000 pairs")
    plt.xlabel("Number of pairs")
    plt.ylabel("Average man preference")
    plt.ylim(0, 500)
    plt.xticks([r + bar_width for r in range(len(index_1[0]))], threads)
    plt.title("Average man preference comparison")
    plt.legend()
    plt.savefig("./data/man.pdf")
    plt.cla()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('repetitions', type=int, help='Number of re.petitions of running functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('config', type=str, help='Path to config file')
    parser.add_argument('is_parallel', type=int, help='True or false')
    args = parser.parse_args()
    dir_path = args.dir_path
    graphs = []
    configs = []
    for i in range(3):
        graphs.append(f"./data/graph_mp{i + 1}/graph_mp{i + 1}.txt")
    for i in range(3):
        configs.append(f"./data/graph_mp{i + 1}/config_mp{i + 1}.cfg")
    config_temp = dir_path + "/config_temp.cfg"
    paths_temp = dir_path + "/path_temp.csv"
    min_path = dir_path + "/min_path.txt"
    threads = ["Gale-Shapley", "Offer", "Min"]
    if args.is_parallel:
        results, times = get_res_par(args.graph, args.config, args.repetitions,
                                     threads)
        # time_graph(times)
    else:
        results, times = get_res(graphs, configs, args.repetitions)
        res_man = []
        res_woman = []
        res_stable = []
        for i in range(3):
            file_stable = []
            file_woman = []
            file_man = []
            for j in range(3):
                stable = 0
                woman = 0
                man = 0
                for k in range(args.repetitions):
                    stable += results[i][j][k][0]
                    woman += results[i][j][k][1]
                    man += results[i][j][k][2]
                file_stable.append(stable / args.repetitions)
                file_woman.append(woman / args.repetitions)
                file_man.append(man / args.repetitions)
            res_stable.append(file_stable)
            res_woman.append(file_woman)
            res_man.append(file_man)
        print(res_man)
        print(res_woman)
        print(res_stable)
        index_1 = [s[2] for s in res_stable], [s[1] for s in res_stable], [s[0] for s in res_stable]
        index_2 = [o[1] for o in res_man], [w[1] for w in res_woman], [s[1] for s in res_stable]
        index_3 = [o[2] for o in res_man], [w[2] for w in res_woman], [s[2] for s in res_stable]
        build_graph(res_man)
