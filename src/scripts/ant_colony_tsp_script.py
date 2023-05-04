import argparse
import subprocess
from math import inf
import matplotlib.pyplot as plt
import numpy as np
from statistics import stdev

def time_graph(times, func_number):
    threads = [1, 2, 4, 6, 8, 12]
    print(times)
    coefficient_list = [times[0] / time / threads[i] for i, time in enumerate(times)]
    print(coefficient_list)

    bar_width = 0.25
    br1 = np.arange(len(threads))
    plt.bar(br1, coefficient_list, color='darkviolet', width=bar_width)
    plt.xlabel("Number of threads")
    plt.ylabel("Coefficient")
    plt.xticks([r for r in range(len(threads))], threads)
    plt.title(f"Effectiveness of parallelization coefficient for function {func_number}")
    plt.legend()
    plt.savefig(f"data/efficiency{func_number}.jpg")
    plt.cla()

    br1 = np.arange(len(threads))
    plt.bar(br1, times, color='darkviolet', width=bar_width)
    plt.xlabel("Number of threads")
    plt.ylabel("Time")
    plt.xticks([r for r in range(len(threads))], threads)
    plt.title(f"Time plot for function {func_number}")
    plt.legend()
    plt.savefig(f"data/time{func_number}.jpg")
    plt.cla()

    coefficient_list = [times[0]/time for _, time in enumerate(times)]
    br1 = np.arange(len(threads))
    plt.plot(br1, coefficient_list, color='darkviolet')
    plt.xlabel("Number of threads")
    plt.ylabel("Amdal`s curve")
    plt.xticks([r for r in range(len(threads))], threads)
    plt.title(f"Amdal`s law curve for function {func_number}")
    plt.legend()
    plt.savefig(f"data/amdal{func_number}.jpg")
    plt.cla()


def run_task_par(graph_path, config_path, paths_path, func_num, thread):
    task_paths = "./bin/aco_algorithms_par"
    process = subprocess.Popen([task_paths] + [config_path, graph_path, paths_path, str(func_num), str(thread)],
                               stdout=subprocess.PIPE)
    output, error = process.communicate()
    output_str = output.decode("utf-8")
    output = output_str.split("\n")
    return output[:-1]


def get_res_par(graph_path, config_path, config_path_mm, paths_path, n, threads):
    funcs_res = []
    total_times = []
    for i in range(1, 4):
        current_times = []
        print(f"Running func: {i}")
        funcs_res.append([])
        for thread in threads:
            thread_times = []
            print(f"Running thread {thread}")
            for k in range(n):
                print(f"Running: {k}")
                if i == 3:
                    config_path = config_path_mm
                func_res = run_task_par(graph_path, config_path, paths_path, i, thread)
                res_n = []
                for j in range(0, len(func_res) - 1, 2):
                    res_n.append((float(func_res[j].split(": ")[1]), float(func_res[j + 1].split(": ")[1])))
                funcs_res[-1].append(res_n)
                thread_times.append(int(func_res[-1].split("=")[1]))
            current_times.append(thread_times)
        total_times.append(current_times)
    return funcs_res, total_times


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
    total_times = []
    for i in range(1, 5):
        print(f"Running func: {i}")
        funcs_res.append([])
        cur_times = []
        for _ in range(n):
            if i == 4:
                config_path = config_path_mm
            func_res = run_task(graph_path, config_path, paths_path, i)
            res_n = []
            for j in range(0, len(func_res) - 1, 2):
                res_n.append((float(func_res[j].split(": ")[1]), float(func_res[j + 1].split(": ")[1])))
            funcs_res[-1].append(res_n)
            cur_times.append(int(func_res[-1].split("=")[1]))
        total_times.append(cur_times)
    return funcs_res, total_times


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
    plt.ylim(min_value, 8000)
    plt.yticks(np.arange(min_value // 100 * 100, 8000, 250))
    plt.title(title)
    plt.legend()
    plt.savefig(path_to_save_min)
    plt.cla()


def build_graph_avg(avg_res, min_value, number_of_f, path_to_save_avg, stdev_for_avg):
    print(path_to_save_avg)
    titles = ["ACO", "Elitism", "ACS", "MMAS"]
    most_popular = []
    minimum_value = []
    for elem in stdev_for_avg[number_of_f]:
        most_popular.append(stdev([el[0] for el in elem]))
        minimum_value.append(stdev([el[1] for el in elem]))
    x = [elem[0] for elem in avg_res[number_of_f]]
    y = [i for i, j in enumerate(avg_res[number_of_f])]
    plt.errorbar(y, x, yerr=most_popular, ecolor='blue', label='Most popular')
    plt.scatter(y, x, s=10)
    x_1 = [elem[1] for elem in avg_res[number_of_f]]
    plt.errorbar(y, x_1, yerr=minimum_value, ecolor='red', label='Minimum')
    plt.scatter(y, x_1, s=10)
    plt.axhline(y=min_value)
    plt.xlabel('Number of iterations')
    plt.ylabel('Path length')
    title = "Average graph for " + titles[number_of_f] + " algorithm"
    plt.ylim(min_value, 8000)
    plt.yticks(np.arange(min_value // 100 * 100, 8000, 250))
    plt.title(title)
    plt.legend()
    plt.savefig(path_to_save_avg)
    plt.cla()


def build_graph(res_list):
    x = [i // 10 + 1 for i in range(300)]
    y = []
    for algo in range(4):
        algo_list = []
        for i in range(30):
            iter_list = []
            for j in range(10):
                iter_list.append(res_list[algo][j][i][0])
            algo_list.append(iter_list)
        y.append(algo_list)
    print(x)
    print(y[0])

    plt.scatter(x, y[0], marker='o')
    plt.savefig("output.png")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('repetitions', type=int, help='Number of repetitions of running functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('config', type=str, help='Path to config file')
    parser.add_argument('config_min_max', type=str, help='Path to min max config file')
    parser.add_argument('is_parallel', type=int, help='True or false')
    args = parser.parse_args()
    dir_path = args.dir_path
    config_temp = dir_path + "/config_temp.cfg"
    paths_temp = dir_path + "/path_temp.csv"
    min_path = dir_path + "/min_path.txt"
    threads = [2, 4, 6, 8, 12]
    if args.is_parallel:
        results, times = get_res_par(args.graph, args.config, args.config_min_max, paths_temp, args.repetitions,
                                     threads)
        results_seq, times_seq = get_res(args.graph, args.config, args.config_min_max, paths_temp, args.repetitions)
        min_list = [[min(times_seq[0])], [min(times_seq[1])], [min(times_seq[2])]]
        print(times)
        for i in range(3):
            for j in range(len(threads)):
                min_list[i].append(min(times[i][j]))
        time_graph(min_list[0], '1')
        time_graph(min_list[1], '2')
        time_graph(min_list[2], '3')
    else:
        results, times = get_res(args.graph, args.config, args.config_min_max, paths_temp, args.repetitions)
        min_res = []
        avg_res = []
        dev_for = []
        for res_i in results:
            dev_for_i = []
            for i in range(len(res_i[0])):
                dev_for_i.append([r[i] for r in res_i])
            dev_for.append(dev_for_i)
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
        build_graph_min(min_res, minimum_value, 0, f"{dir_path}/min_0.jpg")
        build_graph_avg(avg_res, minimum_value, 0, f"{dir_path}/avg_0.jpg", dev_for)
        build_graph_min(min_res, minimum_value, 1, f"{dir_path}/min_1.jpg")
        build_graph_avg(avg_res, minimum_value, 1, f"{dir_path}/avg_1.jpg", dev_for)
        build_graph_min(min_res, minimum_value, 2, f"{dir_path}/min_2.jpg")
        build_graph_avg(avg_res, minimum_value, 2, f"{dir_path}/avg_2.jpg", dev_for)
        build_graph_min(min_res, minimum_value, 3, f"{dir_path}/min_3.jpg")
        build_graph_avg(avg_res, minimum_value, 3, f"{dir_path}/avg_3.jpg", dev_for)
    # print(len(results))
    # print(len(results[0]))
    # print(len(results[0][0]))
    # print(len(results[0][0][0]))
    # build_graph(results)