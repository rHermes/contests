from sympy import *
import math
import re
import collections

MODM = pow(10, 9) + 7
KS = 10

def isnum(s):
    if not s:
        return False

    if s.isnumeric():
        return True

    if s[0] == "-" and s[1:].isnumeric():
        return True

    return False

if __name__ == "__main__":
    n, l, r, x = symbols('n l r x', integer=True)
    print("// constexpr UT INVERSE_MAX_K = {};".format(pow(math.factorial(KS+1), -1, MODM)))

    # inv_ks = [str(pow(math.factorial(k+1), -1, MODM)) for k in range(0,KS+1)]
    # print("// constexpr std::array<UT, MAX_K> INV_KS = {{{}}};".format(",".join(inv_ks)))
    # print(inv_ks)


    print("switch (k) {")
    LK = FiniteField(MODM, symmetric=False)
    for k in range(KS+1):
        wl = (Sum((x)**k, (x, 1, r-l+1)).doit() * factorial(KS+1))
        q = wl.as_poly(r)
        # q = wl.as_poly(r, l, domain=FiniteField(MODM, symmetric=True))
        # q = q.eject(l)
        print("  case {}:".format(k))
        # print("// constexpr UT INVERSE_MAX_K = {};".format(pow(math.factorial(KS+1), -1, MODM)))
        # if k == 0:
        #     print("if (k == {}) {{".format(k))
        # else:
        #     print("else if (k == {}) {{".format(k))

        # For A[0] we have a special place, since we need to have an offset there

        # (array, pos, delta)
        hopes = collections.defaultdict(int)

        # For the zeroth we must handle a bit specialy

        # hopes.append((0, l, q.nth(0)))
        hopes[(0, r+1)] += wl
        # hopes.append((0, r+1, wl))

        for kth in range(0, KS+1+1):
            # Add the kth coefficient to subsequent elemnts
            hopes[(kth, l)] += q.nth(kth)
            # Remove it again
            hopes[(kth, r+1)] -= q.nth(kth)

        for (kt, pos), ex in hopes.items():
            if not ex:
                continue

            akl = str(ex)
            parts = akl.split(" ")
            # print(akl)
            # print(parts)
            parts = [
                    re.sub(r"(l|r)\*\*([1-9][0-9]*)", "ipow(\\1, \\2, MOD_M)".format(MODM), x)
                    for
                    x
                    in parts]
            # print(parts)

            gottem = []
            for part in parts:
                if part in "+-":
                    gottem.append(part)
                    continue 

                elems = part.split("*")
                about = []
                for elem in elems:
                    if not isnum(elem):
                        about.append(elem)
                    else:
                        about.append(str(int(elem) % MODM))

                # ok, now we join the abouts
                while 2 < len(about):
                    f, w, *about = about

                    about.insert(0, "pmod({} * {}, MOD_M)".format(f, w))

                gottem.append("*".join(about))

            # print(gottem)
            akl = " ".join(gottem)

            # akl = re.sub(r"(\S+) \+ (\S+)", "ADD(\\1, \\2)", akl)
            # akl = re.sub(r"(\S+) \- (\S+)", "SUB(\\1, \\2)", akl)
            # akl = re.sub(r"([^ ()]+)\*(\S+)", "SUB(\\1, \\2)", akl)

            print("    bits_[{}].add({}, {});".format(kt, pos, akl))


        print("    break;")

    print("}")

