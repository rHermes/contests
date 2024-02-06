# observation: if c is prime, there are only ever 3 answers.

def prime_factors(n):
    i = 2
    factors = {}
    while i * i <= n:
        if n % i:
            i += 1
        else:
            n //= i
            factors[i] = factors.get(i, 0) + 1
            # factors.append(i)
    if n > 1:
        factors[n] = 1

    return factors


def divisors(n):
    facs = prime_factors(n)
    ans = 1
    for k in facs.values():
        ans *= (k+1)

    return ans

def solve(c):
    sols = []
    for a in range(c+1, 2*c):
        b, res = divmod(a*c, a-c)
        if res == 0:
            sols.append((a,b))

    sols.append((2*c, 2*c))

    # for a,b in list(sols)[:-1]:
    #     sols.append((b,a))

    return sols

c = 54
sol = solve(c)
real_ans = (len(sol)-1)*2 + 1
print("C", c)
print("REAL ANS", real_ans)
print("solutions", sol[:-1])



# for c in range(1, 70):
#     sol = solve(c)
#     primFac = prime_factors(c)
#     ans = 1
#     for k in primFac.values():
#         ans *= (k+1)

#     print("{:3} = {:3} = {} = {} = {}".format(
#         c, 
#         len(sol),
#         sum(primFac.values()),
#         ans,
#         sol))

# T = int(input())
# for _ in range(T):
#     c = int(input())
#     sol = solve(c)

#     print("{} = {}".format(c, sol))
