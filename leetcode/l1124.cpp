#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

#ifdef DEBUG
#include <iomanip>
#endif

class Solution
{
public:
  static int longestWPI(const std::vector<int>& hours)
  {
    // ok, so first of what can I do here to speed this up?
    // OK, let's do something cheeky.
    const int N = hours.size();

    std::vector<int> PSA(N + 1, 0);
    for (int i = 0; i < N; i++) {
      PSA[i + 1] = PSA[i];
      if (8 < hours[i]) {
        PSA[i + 1]++;
      } else {
        PSA[i + 1]--;
      }
    }

    // ok, so by definition, we are now just trying to find the largest pair of
    // l, r in PSA, where l < r and PSA[l] < PSA[r]. Now how do we find that
    // interval.
    //
    // We do this in the following, by exploiting that if l1 < l2 and PSA[l1] < PSA[l2],
    // then if l2 < r and PSA[l2] < PSA[r], then we will also have l1 < r and PSA[l1] < PSA[r].
    // This means that we first just build up a montonic decreasing stack, of all the lowest points
    // in the series, going from left to right. We can then go from right to left and just pop elements
    // as long as They are smaller than the current element. This will by definition be the biggest interval
    // where PSA[l] < PSA[r].

    std::vector<int> stk;
    for (int l = 0; l <= N; l++) {
      if (stk.empty() || PSA[l] < PSA[stk.back()]) {
        stk.push_back(l);
      }
    }

    int ans = 0;
    for (int r = N; 0 <= r; r--) {
      while (!stk.empty() && PSA[stk.back()] < PSA[r]) {
        // ok, so now we are in a spot where the PSA overall is growing.
        // meaning that from stk.back() to r there was an increase.
        ans = std::max(ans, r - stk.back());
        stk.pop_back();
      }
    }

    return ans;
  }
};

constexpr int
bruteForce2(const std::vector<int>& hours)
{
  // ok, so first of what can I do here to speed this up?
  // OK, let's do something cheeky.
  const int N = hours.size();
  std::vector<int> PSA(N + 1, 0);
  for (int i = 0; i < N; i++) {
    PSA[i + 1] = PSA[i] + (8 < hours[i]);
  }

  //
  int ans = 0 < PSA.back();
  for (int l = 0; l < N; l++) {
    int r = N - 1;

    while (l < r) {
      // ok, so
      const int numDays = r - l + 1;
      const int numGood = PSA[r + 1] - PSA[l];
      const int numBad = numDays - numGood;

      if (numBad < numGood) {
        ans = std::max(ans, numDays);
        break;
      } else {
        // ok, so we need to delete at least the imbalance number of days.
        const int jump = numBad - numGood + 1;
        r -= jump;
      }
    }
  }

  return ans;
}

constexpr int
bruteForce(const std::vector<int>& hours)
{
  return bruteForce2(hours);
}

template<typename Gen>
std::vector<int>
generateTest(Gen&& gen, const int n, const double ratio)
{
  std::bernoulli_distribution bp(ratio);
  std::uniform_int_distribution<int> lowerHours(0, 8);
  std::uniform_int_distribution<int> upperHours(9, 16);

  std::vector<int> out(n);

  for (int i = 0; i < n; i++) {
    if (bp(gen)) {
      out[i] = upperHours(gen);
    } else {
      out[i] = lowerHours(gen);
    }
  }

  return out;
}

bool
runBattery(int seed, const int times, const int size, const double ratio)
{
  std::ranlux48 rng(seed);

  for (int i = 0; i < times; i++) {
    const auto testData = generateTest(rng, size, ratio);
    const auto calculated = Solution::longestWPI(testData);
    const auto expected = bruteForce(testData);

    if (calculated != expected) {
      std::cout << "We have a wrong here!\n";
      std::cout << "Hours: [";
      for (const auto x : testData) {
        if (8 < x)
          std::cout << "1 ";
        else
          std::cout << "_ ";
      }
      std::cout << "]\n";
      std::cout << "Expected = " << expected << ", calculated = " << calculated << "\n";

      return false;
    }
  }

  return true;
}

int
main()
{
  constexpr int defaultSize = 100;
  constexpr int defaultTimes = 1000;

  std::random_device rd;
  const auto seed = rd();
  std::cout << "My seed is: " << seed << "\n";
  runBattery(rd(), defaultTimes, defaultSize, 0.00);
  runBattery(rd(), defaultTimes, defaultSize, 0.05);
  runBattery(rd(), defaultTimes, defaultSize, 0.10);
  runBattery(rd(), defaultTimes, defaultSize, 0.15);
  runBattery(seed, defaultTimes, defaultSize, 0.30);
  runBattery(rd(), defaultTimes, defaultSize, 0.50);

  return 0;
}
