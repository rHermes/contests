import random
import subprocess as sp

from tle17c3p6 import solve_it

def generate_test(nmin, nmax, kmin, kmax, umin, umax, qmin, qmax):
    N = random.randint(nmin, nmax)
    U = random.randint(umin, umax)
    Q = random.randint(qmin, qmax)
    outs = []
    for _ in range(U):
        a, b = random.randint(1, N), random.randint(1, N)
        k = random.randint(kmin, kmax)
        outs.append("U {} {} {}".format(min(a, b), max(a, b), k))

    for _ in range(Q):
        a, b = random.randint(1, N), random.randint(1, N)
        outs.append("Q {} {}".format(min(a, b), max(a, b)))

    random.shuffle(outs)
    outs.insert(0, "{} {}".format(N, U + Q))
    return "\n".join(outs)

def compare_output(task):
    pyans = solve_it(task)
    prog = "../plz-out/bin/dmoj/tle17c3p6"
    prog = "../plz-out/bin/dmoj/tle17c3p6-smart"
    lel = sp.run([prog],
            input=task, 
            capture_output=True,
            encoding="UTF-8",
            )
    # lel = sp.run(["../plz-out/bin/dmoj/tle17c3p6"], input=task.encode("utf-8"))
    outs = lel.stdout.strip()
    if pyans != outs:
        print("WTF THINGS ARE WRONG")
        print(task)
        print("===")
        print(pyans)
        print("===")
        print(outs)
        return False

    return True

if __name__ == "__main__":
    while True:
        task = generate_test(
                10**4, 10**5, # N
                0, 10, # K
                3, 4, # U
                5, 9, # Q
                )
        w = compare_output(task)
        if not w:
            break
        print("WTF THINGS ARE GOOD")
