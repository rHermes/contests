def solve(digs):
    ans = 0
    accum = 0
    for c in digs:
        pv = int(c)
        accum = accum*10 + pv
        ans += accum

    return ans

def solve2(digs):
    digs = digs.lstrip("0")
    ds = [int(x) for x in list(digs)]
    accumArr = sum(ds)
    accumOver = 0
    outp = []
    for curD in reversed(ds):
        thisSpot = accumOver + accumArr
        outp.append(thisSpot%10)

        accumOver = thisSpot // 10
        accumArr -= curD

    while 0 < accumOver:
        outp.append(accumOver%10)
        accumOver = accumOver // 10


    return "".join([str(x) for x in reversed(outp)])


T = int(input())
for _ in range(T):
    N = int(input())
    digs = input()
    print(solve2(digs))
