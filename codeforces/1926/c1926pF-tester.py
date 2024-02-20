import subprocess as ps
import itertools as it
import math
from datetime import datetime

def batched(iterable, n):
    # batched('ABCDEFG', 3) --> ABC DEF G
    if n < 1:
        raise ValueError('n must be at least one')
    it2 = iter(iterable)
    while batch := tuple(it.islice(it2, n)):
        yield batch


# BIN_PLACE = "/home/rhermes/commons/projects/contests/plz-out/bin/codeforces/c1926pF"
BIN_PLACE = "./lol"
# BIN_PLACE = "/home/rhermes/commons/projects/contests/dmoj/yac8/p5"

def make_sure_its_up_to_date():
    WL = "/home/rhermes/commons/projects/contests/pleasew"

    pl = ps.run([WL, "build", "//codeforces:c1926pF"], capture_output=True)
    pl.check_returncode()

def run_sol(bin, text):

    bef = datetime.now()
    gv = ps.run(bin, input=text.encode("utf-8"),
                capture_output=True
                )
    gv.check_returncode()
    aft = datetime.now()


    return ([int(x) for x in gv.stdout.decode('utf-8').splitlines()], aft-bef)

def run_mine(text):
    return run_sol(BIN_PLACE, text)

def run_good(text):
    return run_sol("./against", text)

def generate_all_boards():
    for i in range(2**49):
        mask = "{:049b}".format(i)
        board = ["BW"[c == "1"] for c in reversed(mask)]
        board = "".join(board)
        board = ["".join(x) for x  in batched(board, 7)]
        # assert(len(board) == 7*7)
        yield "\n".join(board)


if __name__ == "__main__":
    # make_sure_its_up_to_date()
    iter2 = generate_all_boards()

    batchNo = 0
    N = 200
    for batch in batched(iter2, N):
        txt = "{}\n".format(N)
        txt += "\n".join(batch)
        # with open("lel.txt", mode="w") as f:
        #     print(txt, file=f)

        # break

        computed, mineTime = run_mine(txt)
        verified, benchTime = run_good(txt)


        for i, (mine, good) in enumerate(zip(computed, verified)):
            if mine == good:
                continue

            print("for board {} in batch {} we have two different answers {} vs {}".format(i, batchNo, mine, good))
            print(batch[i])
            break
        else:
            # print("Batch {} took {} for ver and {} for us".format(batchNo, benchTime, mineTime))
            batchNo += 1
            continue

        break





    # import sys
    # files = sys.argv[1:]
    # try:
    #     import natsort
    #     # files = natsort.natsorted(files)
    #     files = natsort.os_sorted(files)
    # except:
    #     pass

    # for file in files:
    #     eval_file(file)
