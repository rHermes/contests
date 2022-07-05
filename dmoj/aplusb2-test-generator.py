import random

def gen_large_number_better(k):
    return random.randint(pow(10, k-1), pow(10, k) - 1)

def gen_large_number(k):
    a = random.randint(1,9)
    for _ in range(k):
        a *= 10
        a += random.randint(0,9)

    return a

def genit(N):
    print(N)
    for _ in range(N):
        a = gen_large_number_better(100000)
        b = gen_large_number_better(100000)

        print("{} {}".format(a, -b))


if __name__ == "__main__":
    genit(10)
