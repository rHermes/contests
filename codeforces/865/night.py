import itertools as it

def tc3():
    N = 300000
    print(N)
    pl = it.islice(it.cycle(["1", "1000000"]), N)
    print(" ".join(pl))
    
if __name__ == "__main__":
    tc3()
