import collections as cs
import itertools as it

def solve():
    N = int(input())
    TS = input()
    cards = input().split(" ")
    cards = [(x[1], int(x[0])) for x in cards]

    seen = set()

    initPlayed = tuple()
    leftToPlay = frozenset(range(len(cards)))
    
    Q = [(initPlayed, leftToPlay)]
    while Q:
        played, left = Q.pop()
        if played in seen:
            continue

        seen.add(played)
        # print(played)

        if not left:
            for (aas,aan), (bbs,bbn) in played:
                print("{}{} {}{}".format(aan,aas,bbn,bbs))

            return

        # We always play the least left
        a = min(left)
        for b in left:
            if a == b:
                continue

            ca = cards[a]
            cb = cards[b]
            if cb[0] == ca[0]:
                if cb[1] < ca[1]:
                    ca, cb = cb, ca
                    a, b = b, a
            elif ca[0] == TS:
                ca, cb = cb, ca
                a, b = b, a
            elif cb[0] == TS:
                pass
            else:
                continue

            nw = played + ((ca, cb),)
            nw = tuple(sorted(nw))
            Q.append((nw, left.difference([a, b])))

    print("IMPOSSIBLE")




    

T = int(input())
for _ in range(T):
    solve()
