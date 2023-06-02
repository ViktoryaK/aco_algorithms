import argparse
import random


def mp_generate_graph(file_path, n):
    llist = [x for x in range(1, n+1)]
    with open(file_path, "w") as file:
        for _ in range(2*n):
            random.shuffle(llist)
            for i in range(n):
                file.write(str(llist[i]) + " ")
            file.write("\n")




if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Python script for matching problem graph generation')
    parser.add_argument('file_path', type=str,  help='Path to output file')
    parser.add_argument('n', type=int,  help='Number of nodes on one side')
    args = parser.parse_args()
    mp_generate_graph(args.file_path, args.n)