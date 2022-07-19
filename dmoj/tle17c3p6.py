import math
import fileinput as fi
import collections as cs

MOD = pow(10,9) + 7

class LazySegTree(object):
    def __init__(self, n):
        self.t = [0] * 4*len(arr)
        self.n = len(arr)
        self._build(arr, 1, 0, len(arr)-1)


class SegTree(object):

    def __init__(self, arr):
        self.t = [0] * 4*len(arr)
        self.n = len(arr)
        self._build(arr, 1, 0, len(arr)-1)


    def _op(self, le, re):
        return (le + re) % MOD
        # return le + re

    def _build(self, a, v, tl, tr):
        if tl == tr:
            self.t[v] = a[tl]
        else:
            tm = (tl + tr) // 2
            self._build(a, v*2, tl, tm)
            self._build(a, v*2 + 1, tm + 1, tr)
            self.t[v] = self._op(self.t[v*2], self.t[v*2+1])

    def _sum(self, v, tl, tr, l, r):
        if l == tl and r == tr:
            # print("sum called with: v={}, tl={}, tr={}, l={}, r={}".format(
            #     v, tl, tr, l, r), end="")
            # print(" and returned because l == tl and r == tr with: {}".format(self.t[v]))
            return self.t[v]

        tm = (tl + tr) // 2
        if r <= tm:
            # print("sum called with: v={}, tl={}, tr={}, l={}, r={}".format(
            #     v, tl, tr, l, r), end="")
            # print(" and since r <= tm, we go left")
            return self._sum(v*2, tl, tm, l, r)
        elif tm < l:
            # print("sum called with: v={}, tl={}, tr={}, l={}, r={}".format(
            #     v, tl, tr, l, r), end="")
            # print(" and since tm < l, we go right")
            return self._sum(v*2 + 1, tm + 1, tr, l, r)
        else:
            left = self._sum(v*2, tl, tm, l, tm)
            right = self._sum(v*2 + 1, tm +1, tr, tm +1, r)
            # print("sum called with: v={}, tl={}, tr={}, l={}, r={}".format(
            #     v, tl, tr, l, r), end="")
            # print(" and since it's a split, we return {} + {} which is {}".format(
            #     left, right, left + right))
            return self._op(left, right)

    def sum(self, l, r):
        return self._sum(1, 1, self.n, l, r)

    def _delta(self, v, tl, tr, pos, delta):
        if tl == tr:
            self.t[v] = self._op(self.t[v], delta)
        else:
            tm = (tl + tr) // 2
            if pos <= tm:
                self._delta(v*2, tl, tm, pos, delta)
            else:
                self._delta(v*2+1, tm+1, tr, pos, delta)
            
            self.t[v] = self._op(self.t[v*2], self.t[v*2+1])

    def delta(self, pos, delta):
        return self._delta(1, 1, self.n, pos, delta)


    def print_it(self):
        Q = cs.deque()
        Q.append((1, 1, self.n))

        while Q:
            v, tl, tr = Q.popleft()
            print("[{}, {}] = {}".format(tl, tr, self.t[v]))

            if tl == tr:
                continue

            tm = (tl + tr) // 2
            Q.append((v*2, tl, tm))
            Q.append((v*2 + 1, tm + 1, tr))

def solve_it(ins):
    lines = ins.splitlines()
    N, Q = map(int, lines[0].split(" "))
    wow = [0] * N
    tree = SegTree(wow)

    outs = []

    # tree.print_it()
    for i in range(Q):
        parts = lines[1+i].split(" ")

        if parts[0] == 'U':
            l, r, k = map(int, parts[1:])
            for j, x in enumerate(range(l, r+1)):
                j += 1
                dd = pow(j, k, MOD)
                # print("Adding {} to {}".format(dd, x))
                tree.delta(x, pow(j, k, MOD))

            # print("After we have")
            # tree.print_it()

            # print("After we have:")
            # for x in range(1,N+1):
            #     print("X={} has {}".format(x,
            #         tree.sum(x, x)
            #         ))

            # print("AND")
            # for x in range(1, N+1):
            #     for y in range(x, N+1):
            #         print("X-Y: {}-{} = {}".format(
            #             x, y,
            #             tree.sum(x, y)
            #             ))
                        


        else:
            # print(parts)
            outs.append(str(tree.sum( int(parts[1]), int(parts[2]))))
       
       

    return "\n".join(outs)





if __name__ == "__main__":
    task = "\n".join(x.strip() for x in fi.input())
    print(solve_it(task))
