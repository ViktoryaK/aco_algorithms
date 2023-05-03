import argparse
from ant_colony_tsp_script import get_res


def build_ant_dep_table(dir, graph_path, config_path, config_path_mm, paths_path, n):
    methods_dirs = ["default", "elitism", "acs", "min_max"]
    ant_numbers = [1, 3, 5, 10, 15, 20, 25, 30, 40, 50, 100]
    depositions = [1, 5, 10, 15, 20, 25, 30, 40, 50, 100, 200]
    final_mins = [[], [], [], []]
    for ant in ant_numbers:
        print(f"Cur ant: {ant}")
        deposition_mins = [[],[],[],[]]
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


def ant_n_graph(dir, graph_path, config_path, config_path_mm, paths_path, n):

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for comparison of different functions')
    parser.add_argument('repetitions', type=int, help='Number of repetitions of running functions')
    parser.add_argument('graph', type=str, help='Path to graph')
    parser.add_argument('dir_path', type=str, help='Path to directory')
    parser.add_argument('temp_config', type=str, help='Path to temporary configuration file')
    parser.add_argument('temp_config_mm', type=str, help='Path to temporary configuration file')
    args = parser.parse_args()
    build_ant_dep_table(args.dir_path, args.graph, args.temp_config, args.temp_config_mm, "./data/graph3/path_tems.csv",
                        args.repetitions)