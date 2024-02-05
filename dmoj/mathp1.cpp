/**
 * mathp1 - A Math Contest P1 - Arrays
 *
 * This is a really cool task, where we are given a set of integers and we should find the
 * minimum possible positive linear combination of these integers.
 *
 * I learned a lot about the GCD function while doing this. I solved this in a different way
 * initially, but after looking at some other submissions, I saw they where all using the GCD.
 *
 * It took me some time to figure out why it works, but I've done it now.
 *
 * We start by using a and b as our two first numbers. If we define:
 *
 * gcd(a, b) = d
 *
 * then we have two integers e and f, which fullfill:
 *
 * a = d * e
 * b = d * f
 *
 * So a combination of a and b can be written as:
 *
 * a*x + b*y = d*e*x + d*f*y = d * (e*x + f*y)
 *
 * Since e and f are coprime, their gcd(e, f) = 1, and so using Bezout's identity, we know
 * that there are a way to combine them to get 1. This means that the least positive integer
 * we can make with a and b, is d.
 *
 * We can extend this to more than two integers, by repeatedly applying the GCD to the next
 * integer. This will produce the correct answer, but to speed things up, we can stop reading
 * numbers, if the answer ever becomes 1.
 */

#include <cmath>
#include <cstdint>
#include <cstdio>

using UT = std::uint64_t;
using ST = std::int64_t;

ST gcd(ST a, ST b) {
  while (b != 0) {
    a %= b;
    std::swap(a, b);
  }

  return std::abs(a);
}

int main(void) {
  UT N = 0;
  scanf("%lu", &N);

  ST ans = 0;
  for (UT i = 0; i < N; i++) {
    ST x = 0;
    scanf("%ld", &x);

    ans = gcd(x, ans);

    // We terminate early, if the gcd is 1. It is the lowest answer we can ever get.
    if (ans == 1)
      break;
  }

  printf("%ld\n", ans);
  return 0;
}
