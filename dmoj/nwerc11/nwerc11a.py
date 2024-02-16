import math
import sys

def find_k_range(X):
    k = 0
    while True:
        k += 1
        if (2*k + 1) * X <= pow(4, k):
            break

    return k


def find_smallest_n(X, k):
    c = math.factorial(k) * X

    # First we find an upper bound
    n = 1
    while pow(n, k) < c:
        n *= 2

    # Just a simple binary search here.
    lo = 1
    hi = n
    while 1 < hi - lo:
        mid = lo + (hi - lo) // 2
        if pow(mid, k) < c:
            lo = mid
        else:
            hi = mid

    assert(c <= pow(hi, k))
    assert(pow(hi-1, k) < c)

    return hi


def solve(X):
    ret = set()
    largest_k = find_k_range(X)
    # print("The largest K for x={} is {}".format(X, largest_k))
    for k in range(1, largest_k+1):
        smallest_n = find_smallest_n(X, k)
        # print("The smallest N for K={} is {}".format(k, smallest_n))
        nmin = max(smallest_n, 2*k)

        # We only calculate the binom from scratch once, then we iterate
        # through them after that.
        choose = math.comb(nmin, k)
        for n in range(nmin, smallest_n + k + 1):
            if choose == X:
                ret.add((n,k))
                if k < n - k:
                    ret.add((n, n-k))

            # Calculate the next binom, based on the previous
            choose *= (n+1)
            choose //= (n+1-k)

    w = " ".join("({},{})".format(n,k) for (n,k) in sorted(ret))
    return "{}\n{}".format(len(ret), w)


if __name__ == "__main__":
    all_data = [x for x in sys.stdin.read().split('\n') if x]
    for X in map(int,all_data[1:]):
        print(solve(X))


