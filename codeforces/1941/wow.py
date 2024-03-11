import random



def smart_solve(arr):
    wow = [x for x in arr]

    for i in range(1,len(wow)-1):
        if wow[i] < 0:
            return False

        timesNeeded = wow[i-1]
        wow[i-1] -= timesNeeded
        wow[i] -= 2*timesNeeded
        wow[i+1] -= timesNeeded

        if wow[i] < 0:
            return False
    
    return wow[-2] == 0 and wow[-1] == 0


def brute_it(arr):
    if all(0 == x for x in arr):
        return True

    if any(x < 0 for x in arr):
        return False

    for i in range(1,len(arr)-1):
        a = arr[i-1] - 1
        b = arr[i] - 2
        c = arr[i+1] - 1

        if (a < 0 or b < 0 or c < 0):
            continue

        arr[i-1] = a
        arr[i] = b
        arr[i+1] = c
        kl = brute_it(arr)
        arr[i-1] += 1
        arr[i] += 2
        arr[i+1] += 1

        if kl:
            return True

    return False

def genRange(l, upper):
    return [random.randint(0, upper) for _ in range(l)]

for _ in range(10000):
    # arr = genRange(8, 10)
    arr = [4, 10, 9, 5, 1]
    print(arr)
    sm = smart_solve(arr)
    db = brute_it(arr)
    if sm != db:
        print(sm, db, arr)
        break


