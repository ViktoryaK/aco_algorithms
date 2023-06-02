import argparse
from ant_colony_tsp_script import get_res, run_task
from statistics import stdev, mean
import matplotlib.pyplot as plt
import numpy as np


def get_func_res(graph_path, config_path, paths_path, n, func):
    funcs_res = []
    total_times = []
    for _ in range(n):
        func_res = run_task(graph_path, config_path, paths_path, func)
        res_n = []
        for j in range(0, len(func_res) - 1, 2):
            res_n.append((float(func_res[j].split(": ")[1]), float(func_res[j + 1].split(": ")[1])))
        funcs_res.append(res_n)
        total_times.append(int(func_res[-1].split("=")[1]))
    return funcs_res, total_times


def build_ant_dep_table(dir, graph_path, config_path, config_path_mm, paths_path, n):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    ant_numbers = [1, 3, 5, 10, 15, 20, 25, 30, 40, 50, 100]
    depositions = [1, 5, 10, 15, 20, 25, 30, 40, 50, 100, 200]
    final_mins = [[], [], [], []]
    for ant in ant_numbers:
        print(f"Cur ant: {ant}")
        deposition_mins = [[], [], [], []]
        for deposition in depositions:
            print(f"Cur deposition: {deposition}")
            config_txt = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = {deposition}\n' \
                         f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = {ant}\nexplore_const = 0.001\n' \
                         f'pheromone_decay = 0.001\nelitism_n = {min(ant, 5)}\nmax_iter = 30\nmutation_rate = 0'
            with open(config_path, 'w') as file:
                file.write(config_txt)
            config_txt_mm = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = {deposition}\n' \
                            f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = {ant}\nexplore_const = 0.001\n' \
                            f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0.1\n' \
                            f'min_pheromone = 0.0001\nmax_pheromone = 0.01'
            with open(config_path_mm, 'w') as file:
                file.write(config_txt_mm)
            res, times = get_res(graph_path, config_path, config_path_mm, paths_path, n)
            for i in range(4):
                avg = 0
                for elem in res[i]:
                    avg += elem[-1][1]
                deposition_mins[i].append(avg / n)
        for i in range(4):
            final_mins[i].append(deposition_mins[i])
    q = 0
    for el in final_mins:
        print(methods_dirs[q])
        for i in range(len(el)):
            text = ""
            for j in range(len(el[i])):
                text += str(el[i][j]) + " "
            print(text)
        q += 1
    return final_mins


def build_imp_table(dir, graph_path, config_path, config_path_mm, paths_path, n):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    pheromones = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    heuristics = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    final_mins = [[], [], [], []]
    for pheromone in pheromones:
        print(f"Pheromones: {pheromone}")
        heuristic_mins = [[], [], [], []]
        for heuristic in heuristics:
            print(f"Cur heuristic: {heuristic}")
            config_txt = f'nodes = 50\npheromone_importance = {pheromone}\nheuristic_inf = {heuristic}\ndeposition = 10\n' \
                         f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = 0.001\n' \
                         f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0'
            with open(config_path, 'w') as file:
                file.write(config_txt)
            config_txt_mm = f'nodes = 50\npheromone_importance = {pheromone}\nheuristic_inf = {heuristic}\n' \
                            f'deposition = 10\n' \
                            f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = 0.001\n' \
                            f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0.1\n' \
                            f'min_pheromone = 0.0001\nmax_pheromone = 0.01'
            with open(config_path_mm, 'w') as file:
                file.write(config_txt_mm)
            res, times = get_res(graph_path, config_path, config_path_mm, paths_path, n)
            for i in range(4):
                avg = 0
                for elem in res[i]:
                    avg += elem[-1][1]
                heuristic_mins[i].append(avg / n)
        for i in range(4):
            final_mins[i].append(heuristic_mins[i])
    q = 0
    for el in final_mins:
        print(methods_dirs[q])
        for i in range(len(el)):
            text = ""
            for j in range(len(el[i])):
                text += str(el[i][j]) + " "
            print(text)
        q += 1
    return final_mins


def build_init_graph(dir, graph_path, config_path, config_path_mm, paths_path, n, output_path):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    pheromones = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
    final_mins = [[], [], [], []]
    min_value = 5104.525367305101
    for pheromone in pheromones:
        print(f"Pheromones: {pheromone}")
        config_txt = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                     f'evaporation_rate = 0.9\ninit_pheromone = {pheromone}\nants_n = 30\nexplore_const = 0.001\n' \
                     f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0'
        with open(config_path, 'w') as file:
            file.write(config_txt)
        config_txt_mm = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                        f'evaporation_rate = 0.9\ninit_pheromone = {pheromone}\nants_n = 30\nexplore_const = 0.001\n' \
                        f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0.1\n' \
                        f'min_pheromone = 0.0001\nmax_pheromone = 0.01'
        with open(config_path_mm, 'w') as file:
            file.write(config_txt_mm)
        res, times = get_res(graph_path, config_path, config_path_mm, paths_path, n)

        for i in range(4):
            last_min_res = []
            for elem in res[i]:
                last_min_res.append(elem[-1][1])
            final_mins[i].append(last_min_res)
    print(final_mins)
    titles = ["ACO", "Elitism", "ACS", "MMAS"]
    stdev_list = [[], [], [], []]
    avg_list = [[], [], [], []]
    for i, func_mins in enumerate(final_mins):
        for elem in func_mins:
            stdev_list[i].append(stdev(elem))
            avg_list[i].append(mean(elem))
        x = pheromones
        y = avg_list[i]
        bar_width = 0.25
        br1 = np.arange(len(x))
        plt.bar(br1, y, yerr=stdev_list[i], ecolor='red', color='darkviolet', width=bar_width)
        plt.xticks([r for r in range(len(x))], x)
        plt.axhline(y=min_value)
        plt.xlabel('Init pheromone')
        plt.ylabel('Path length')
        title = "Init pheromone dependency for " + titles[i] + " algorithm"
        plt.ylim(min_value, 6000)
        plt.yticks(np.arange(min_value // 100 * 100, 6000, 100))
        plt.title(title)
        plt.legend()
        plt.savefig(output_path + f"/init_pheromone_cl_{i}.pdf")
        plt.cla()


def build_evaropation_graph(dir, graph_path, config_path, config_path_mm, paths_path, n, output_path):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    evaropations = [x / 10 for x in range(10)]
    final_mins = [[], [], [], []]
    min_value = 5104.525367305101
    for evaropation in evaropations:
        print(f"Evaropation: {evaropation}")
        config_txt = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                     f'evaporation_rate = {evaropation}\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = 0.001\n' \
                     f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0'
        with open(config_path, 'w') as file:
            file.write(config_txt)
        config_txt_mm = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                        f'evaporation_rate = {evaropation}\ninit_pheromone = 0.000001\nants_n = 30\n' \
                        f'explore_const = 0.001\n' \
                        f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0.1\n' \
                        f'min_pheromone = 0.0001\nmax_pheromone = 0.01'
        with open(config_path_mm, 'w') as file:
            file.write(config_txt_mm)
        res, times = get_res(graph_path, config_path, config_path_mm, paths_path, n)

        for i in range(4):
            last_min_res = []
            for elem in res[i]:
                last_min_res.append(elem[-1][1])
            final_mins[i].append(last_min_res)
    print(final_mins)
    titles = ["ACO", "Elitism", "ACS", "MMAS"]
    stdev_list = [[], [], [], []]
    avg_list = [[], [], [], []]
    for i, func_mins in enumerate(final_mins):
        for elem in func_mins:
            stdev_list[i].append(stdev(elem))
            avg_list[i].append(mean(elem))
        x = evaropations
        y = avg_list[i]
        bar_width = 0.25
        br1 = np.arange(len(x))
        plt.bar(br1, y, yerr=stdev_list[i], ecolor='red', color='darkviolet', width=bar_width)
        plt.xticks([r for r in range(len(x))], x)
        plt.axhline(y=min_value)
        plt.xlabel('Evaropation rate')
        plt.ylabel('Path length')
        title = "Evaropation rate dependency for " + titles[i] + " algorithm"
        plt.ylim(min_value, 6000)
        plt.yticks(np.arange(min_value // 100 * 100, 6000, 100))
        plt.title(title)
        plt.legend()
        plt.savefig(output_path + f"/evaropation_rate_cl_{i}.pdf")
        plt.cla()


def build_explore_graph(dir, graph_path, config_path, paths_path, n, output_path):
    explorations = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 0.5, 0.9]
    final_mins = []
    min_value = 5104.525367305101
    for exploration in explorations:
        print(f"Exploration: {exploration}")
        config_txt = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                     f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = {exploration}\n' \
                     f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0'
        with open(config_path, 'w') as file:
            file.write(config_txt)
        res, times = get_func_res(graph_path, config_path, paths_path, n, 3)
        last_min_res = []
        for elem in res:
            last_min_res.append(elem[-1][1])
        final_mins.append(last_min_res)
    print(final_mins)
    stdev_list = []
    avg_list = []
    for elem in final_mins:
        stdev_list.append(stdev(elem))
        avg_list.append(mean(elem))
    x = explorations
    y = avg_list
    bar_width = 0.25
    br1 = np.arange(len(x))
    plt.bar(br1, y, yerr=stdev_list, ecolor='red', color='darkviolet', width=bar_width)
    plt.xticks([r for r in range(len(x))], x)
    plt.axhline(y=min_value)
    plt.xlabel('Exploration constant')
    plt.ylabel('Path length')
    title = "Exploration constant for ACS algorithm"
    plt.ylim(min_value, 6000)
    plt.yticks(np.arange(min_value // 100 * 100, 6000, 100))
    plt.title(title)
    plt.legend()
    plt.savefig(output_path + f"/exploration_const_cl.pdf")
    plt.cla()


def build_decay_graph(dir, graph_path, config_path, paths_path, n, output_path):
    decays = [0.000001, 0.00001, 0.0001, 0.001, 0.01, 0.1, 1]
    final_mins = []
    min_value = 5104.525367305101
    for decay in decays:
        print(f"Decay: {decay}")
        config_txt = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\ndeposition = 10\n' \
                     f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = 0.001\n' \
                     f'pheromone_decay = {decay}\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0'
        with open(config_path, 'w') as file:
            file.write(config_txt)
        res, times = get_func_res(graph_path, config_path, paths_path, n, 3)
        last_min_res = []
        for elem in res:
            last_min_res.append(elem[-1][1])
        final_mins.append(last_min_res)
    print(final_mins)
    stdev_list = []
    avg_list = []
    for elem in final_mins:
        stdev_list.append(stdev(elem))
        avg_list.append(mean(elem))
    x = decays
    y = avg_list
    bar_width = 0.25
    br1 = np.arange(len(x))
    plt.bar(br1, y, yerr=stdev_list, ecolor='red', color='darkviolet', width=bar_width)
    plt.xticks([r for r in range(len(x))], x)
    plt.axhline(y=min_value)
    plt.xlabel('Pheromone decay')
    plt.ylabel('Path length')
    title = "Pheromone decay for ACS algorithm"
    plt.ylim(min_value, 6000)
    plt.yticks(np.arange(min_value // 100 * 100, 6000, 100))
    plt.title(title)
    plt.legend()
    plt.savefig(output_path + f"/pheromone_decay_cl.pdf")
    plt.cla()


def build_min_max_table(dir, graph_path, config_path_mm, paths_path, n, output_path):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    min_ph = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
    max_ph = [0.00001, 0.0001, 0.001, 0.01, 0.1, 1, 10, 100]
    final_mins = [[], [], [], []]
    for ph_1 in min_ph:
        print(f"Min: {ph_1}")
        max_mins = []
        for ph_2 in max_ph:
            if (ph_2 <= ph_1):
                max_mins.append(0)
                continue
            print(f"Max: {ph_2}")
            config_txt_mm = f'nodes = 50\npheromone_importance = 1\nheuristic_inf = 5\n' \
                            f'deposition = 10\n' \
                            f'evaporation_rate = 0.9\ninit_pheromone = 0.000001\nants_n = 30\nexplore_const = 0.001\n' \
                            f'pheromone_decay = 0.001\nelitism_n = 5\nmax_iter = 30\nmutation_rate = 0.1\n' \
                            f'min_pheromone = {ph_1}\nmax_pheromone = {ph_2}'
            with open(config_path_mm, 'w') as file:
                file.write(config_txt_mm)
            res, times = get_func_res(graph_path, config_path_mm, paths_path, n, 4)
            avg = 0
            for elem in res:
                avg += elem[-1][1]
            max_mins.append(avg / n)
        final_mins.append(max_mins)
    for i in range(len(final_mins)):
        text = ""
        for j in range(len(final_mins[i])):
            text += str(final_mins[i][j]) + " "
        print(text)
    return final_mins


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('repetitions', type=int, help='Number of repetitions of running functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('temp_config', type=str, help='Path to temporary configuration file')
    parser.add_argument('temp_config_mm', type=str, help='Path to temporary configuration file')
    args = parser.parse_args()
    build_min_max_table(args.dir_path, args.graph, args.temp_config_mm, "./data/graph3/path_tems.csv",
                      args.repetitions, "./data/graph3/analysing/")
