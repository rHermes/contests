# This program creates the context weights used in each case
import fileinput as fi
import collections as cs
import itertools as it

def build_tables(input):
    freq = {}
    valid_num = [10] + list(range(32,126+1))
    valid = [chr(v) for v in valid_num]
    for c in valid:
        tbl = {k: 0 for k in valid}
        freq[c] = tbl

    totfreq = {k: 0 for k in valid}
    for a, b in it.pairwise(input):
        if a  not in valid or b not in valid:
            continue
        freq[a][b] += 1
        totfreq[a] += 1
    
    # Now we just need to create the tables that we will use.

    # Newline = 10 = 0
    # 32 = 1
    
    tables = []
    mm = 0

    totfreq_tbl = [totfreq[nxt] for nxt in valid]
    max_tot = max(totfreq_tbl)
    for i, ctx in enumerate(valid):
        tbl = []
        for j, nxt in enumerate(valid):
            tbl.append(freq[ctx][nxt])
            # tbl.append(totfreq[nxt])

        max_r = max(tbl)
        mm = max(max_r, mm)

        # We have a problem here, if there are too few rows, we want to replace it.
        num_not_zero = sum(x != 0 for x in tbl)
        if num_not_zero < 1:
            c = 31 + i
            if c == 31:
                c = 10

            # c = chr(c)
            print("We are boosting row [{}] with identity".format(c))
            # print("We are replacing row [{}] with identity".format(c))

            for j, p in enumerate(tbl):
                if p != 0:
                    tbl[j] += max_tot + p
                else:
                    tbl[j] = totfreq_tbl[j]

            # tbl = totfreq_tbl


        
        # tbl = [x+10 for x in tbl]
        tables.append(tbl)

    print("MAX ELEMENT IS {} Which as a bit length of {}".format(mm, mm.bit_length()))

    # print(tables)
    # N = len(valid_num)
    # print(N*N)
    return tables


def format_tables(tables):
    N = len(tables)
    ans = ""
    ans += "constexpr std::array<std::array<std::uint64_t, {}>, {}> FREQ{{{{\n".format(N, N)
                                                                        # }}}}
    
    for row in tables:
        ans += "{" + ",".join([str(x) for x in row]) + "},\n"

    ans += "}};\n";


    return ans
    




if __name__ == "__main__":
    import sys
    files = sys.argv[1:]

    inp = ""
    for file in files:
        with open(file, encoding="ascii", errors="replace") as f:
            inp += f.read()

    # print(inp)
    tables = build_tables(inp)
    outp = format_tables(tables)
    with open("weights.h", "w") as f:
        print(outp, file=f)
