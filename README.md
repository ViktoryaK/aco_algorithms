# aco_algorithms

### Authors: Yaroslav Klym, Viktoria Kocherkevych

The Ant Colony Optimization algorithms are based on the ways ants choose their
pathes in nature. The algorithm's main point lies in the simulation of ants and their pheromones,
for ants to choose shorter path since there is larger pheromone deposition.

We already implemented several ways to solve the Travelling Salesman Problem using different variations of ACO algorithm.

### Compilation

```
chmod +x
./compile.sh
```

### Installation
Install matplotlib and numpy
```
pip install matplotlib
pip install numpy
```

### Usage

```
./bin/aco_algorithms ./data/config2_mm.cfg ./data/graph3/graph3.txt ./data/graph3/acs/paths3.csv 4 0

./bin/aco_algorithms_par ./data/config2.cfg ./data/graph3/graph3.txt ./data/graph3/default/par/paths3.csv 4 4

python3 ./src/scripts/ant_colony_tsp_script.py 5 ./data/graph3/graph3.txt ./data/graph3 ./data/config2.cfg ./data/config2_mm.cfg
```
