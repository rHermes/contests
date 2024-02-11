import random
import networkx as nx
import matplotlib.pyplot as plt
import subprocess as ps
import itertools as it
from tqdm import tqdm, trange
import math
import os
from multiprocessing import Pool
import numpy as np


BIN_PLACE = "/home/rhermes/commons/projects/contests/plz-out/bin/dmoj/yac8p5"
# BIN_PLACE = "/home/rhermes/commons/projects/contests/dmoj/yac8/p5"

plt.ion()

def hierarchy_pos2(G, root=None, width=1., vert_gap = 0.2, vert_loc = 0, xcenter = 0.5):

    '''
    From Joel's answer at https://stackoverflow.com/a/29597209/2966723.  
    Licensed under Creative Commons Attribution-Share Alike 
    
    If the graph is a tree this will return the positions to plot this in a 
    hierarchical layout.
    
    G: the graph (must be a tree)
    
    root: the root node of current branch 
    - if the tree is directed and this is not given, 
      the root will be found and used
    - if the tree is directed and this is given, then 
      the positions will be just for the descendants of this node.
    - if the tree is undirected and not given, 
      then a random choice will be used.
    
    width: horizontal space allocated for this branch - avoids overlap with other branches
    
    vert_gap: gap between levels of hierarchy
    
    vert_loc: vertical location of root
    
    xcenter: horizontal location of root
    '''
    if not nx.is_tree(G):
        raise TypeError('cannot use hierarchy_pos on a graph that is not a tree')

    if root is None:
        if isinstance(G, nx.DiGraph):
            root = next(iter(nx.topological_sort(G)))  #allows back compatibility with nx version 1.11
        else:
            root = random.choice(list(G.nodes))

    def _hierarchy_pos(G, root, width=1., vert_gap = 0.2, vert_loc = 0, xcenter = 0.5, pos = None, parent = None):
        '''
        see hierarchy_pos docstring for most arguments

        pos: a dict saying where all nodes go if they have been assigned
        parent: parent of this branch. - only affects it if non-directed

        '''
    
        if pos is None:
            pos = {root:(xcenter,vert_loc)}
        else:
            pos[root] = (xcenter, vert_loc)
        children = list(G.neighbors(root))
        if not isinstance(G, nx.DiGraph) and parent is not None:
            children.remove(parent)  
        if len(children)!=0:
            dx = width/len(children) 
            nextx = xcenter - width/2 - dx/2
            for child in children:
                nextx += dx
                pos = _hierarchy_pos(G,child, width = dx, vert_gap = vert_gap, 
                                    vert_loc = vert_loc-vert_gap, xcenter=nextx,
                                    pos=pos, parent = root)
        return pos

            
    return _hierarchy_pos(G, root, width, vert_gap, vert_loc, xcenter)


def hierarchy_pos(G, root, levels=None, width=1., height=1.):
    '''If there is a cycle that is reachable from root, then this will see infinite recursion.
       G: the graph
       root: the root node
       levels: a dictionary
               key: level number (starting from 0)
               value: number of nodes in this level
       width: horizontal space allocated for drawing
       height: vertical space allocated for drawing'''
    TOTAL = "total"
    CURRENT = "current"
    def make_levels(levels, node=root, currentLevel=0, parent=None):
        """Compute the number of nodes for each level
        """
        if not currentLevel in levels:
            levels[currentLevel] = {TOTAL : 0, CURRENT : 0}
        levels[currentLevel][TOTAL] += 1
        neighbors = G.neighbors(node)
        for neighbor in neighbors:
            if not neighbor == parent:
                levels =  make_levels(levels, neighbor, currentLevel + 1, node)
        return levels

    def make_pos(pos, node=root, currentLevel=0, parent=None, vert_loc=0):
        dx = 1/levels[currentLevel][TOTAL]
        left = dx/2
        pos[node] = ((left + dx*levels[currentLevel][CURRENT])*width, vert_loc)
        levels[currentLevel][CURRENT] += 1
        neighbors = G.neighbors(node)
        for neighbor in neighbors:
            if not neighbor == parent:
                pos = make_pos(pos, neighbor, currentLevel + 1, node, vert_loc-vert_gap)
        return pos
    if levels is None:
        levels = make_levels({})
    else:
        levels = {l:{TOTAL: levels[l], CURRENT:0} for l in levels}
    vert_gap = height / (max([l for l in levels])+1)
    return make_pos({})

def get_graph(N, seed):
    gr = nx.generators.random_labeled_tree(N, seed=seed)
    mapper = {k: k+1 for k in range(N)}
    gr = nx.relabel_nodes(gr, mapper, copy=True)

    return gr

# OK so we are going to create some tests here, but 
def to_problem_format(G):
    N = len(G)
    lines = ["1", str(N)]

    for a, b in G.edges:
        lines.append("{} {}".format(a, b))

    return "\n".join(lines)

def generate_mapping(G):
    inp = to_problem_format(G)

    gv  = ps.run(BIN_PLACE,
                 input=inp.encode("utf-8"),
                 capture_output=True,
                 )
    gv.check_returncode()
    out = [int(x) for x in gv.stdout.decode('utf-8').strip().split(" ")]
    return out

def generate_questions(G, mapping):
    N = len(G)
    questions = []
    for i in range(1,N+1):
        for j in range(i+1, N+1):
            if j in G[i]:
                continue

            questions.append((i,j))



    lines = ["2", str(len(questions))]
    for i, j in questions:
        lines.append("{} {}".format(mapping[i-1], mapping[j-1]))

    return questions, "\n".join(lines)


def get_answers(G, mapping):
    questions, inp = generate_questions(G, mapping)

    gv = ps.run(BIN_PLACE,
                input=inp.encode("utf-8"),
                capture_output=True,
                )
    gv.check_returncode()

    answers = [int(x) for x in gv.stdout.decode('utf-8').splitlines()]
    return (questions, answers)



def check_mapping(G, mapping):
    quest, ans = get_answers(G, mapping)
    p = nx.shortest_path(G)

    for (src, dst), our_ans in zip(quest, ans):
        if our_ans in (src, dst) or our_ans not in p[src][dst]:
            print("BIG EMERGENCY!!!!")
            return False

    return True


def check_prog(N, seed):
    G = get_graph(N, seed)
    mapping = generate_mapping(G)
    good = check_mapping(G, mapping)
    return (good, mapping)

def check_all_linegraphs(N):
    # This will check all linegraphs
    nums = list(range(1,N+1))
    pvs = tqdm(it.permutations(nums), total=math.perm(N))
    for per in pvs:
        G = nx.generators.path_graph(per)
        mapping = generate_mapping(G)
        good = check_mapping(G, mapping)
        if not good:
            print("We have an error with per: ", per)
            return per

    return None

def sample_alot_of_line_graphs(N):
    # This will check all linegraphs
    nums = list(range(1,N+1))
    for i in trange(1000000):
        random.shuffle(nums)
        G = nx.generators.path_graph(nums)
        mapping = generate_mapping(G)
        good = check_mapping(G, mapping)
        if not good:
            print("We have an error with per: ", nums)
            return nums

    return None

def sample_random_graphs(seeds):
    N = 100
    # print("We got seeds: {}".format(seeds))
    random.seed(seeds)
    tr = range(100000000000)
    if seeds == 0:
        tr = tqdm(tr,
                    desc=seeds,
                    position=seeds,
                    )
    for _ in tr:
        seed = random.randint(1, 10000000000000000000)
        good = check_prog(N, seed)
        if not good:
            # print("We have an error 
            print("N={} and SEED={} is a problem!".format(N, seed))
            return (N, seed)
# def sample_random_graphs():
#     # we want each graph to do something different
#     random.seed(os.getpid())

def random_in_par():
    n = 8
    with Pool(n) as pool:
        pool.map(sample_random_graphs, range(n))
        # pool.map(sample_random_graphs, range(1000), 40)

    pass

def make_sure_its_up_to_date():
    WL = "/home/rhermes/commons/projects/contests/pleasew"

    pl = ps.run([WL, "build", "//dmoj:yac8p5"], capture_output=True)
    pl.check_returncode()


if __name__ == "__main__":
    make_sure_its_up_to_date()
    # check_all_linegraphs(10)
    # sample_alot_of_line_graphs(100)
    # random_in_par()
    # w = get_graph(6, 211)
    # w = get_graph(10,75621160737553)
    N = 100
    for i in range(100000):
        seed = random.randint(1,100000000000000)
        # print(N, seed)
        good, mapping = check_prog(N, seed)
        print(N, seed, max(mapping))
        if not good:
            print("N={} and SEED={} is a problem!".format(N, seed))
            w = get_graph(N, seed)
            mapping = generate_mapping(w)
            quest, ans = get_answers(w, mapping)
            break
