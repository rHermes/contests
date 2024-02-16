import random
import collections as cs


def get_message(N):
    return list(random.randbytes(N))

def encode1(M):
    out = M + M
    nk = sorted(M)

    for idx, m in enumerate(M):
        # We just test this
        mi = nk.index(m)
        digit_index = "{:06b}".format(mi)

        dia, dib, dic = digit_index[4:6], digit_index[2:4], digit_index[0:2]

        idx_index = "{:06b}".format(idx)
        # iia, iib, iic = idx_index[4:6], idx_index[2:4], idx_index[0:2]

        for i in range(0, 6, 2):
            out.append(int(idx_index + digit_index[i:i+2], 2))
            


    return out

def decode1(N, L):
    return []

def encode(M):
    return encode1(M)

# We must return M
def decode(N, L):
    return decode1(N, L)


def onepass(M):
    G = encode(M)
    print("We have M: ", M)
    print("Encoded  : ", G)
    print(cs.Counter(G))
    random.shuffle(G)
    ED = decode(len(M), G)

    return M == ED


msg = get_message(64)
msg = get_message(16)
msg = [228] * 16 #get_message(16)

for _ in range(1):
    good = onepass(msg)
    if not good:
        print("We didn't get lucky")
    else:
        print("We got it!")
