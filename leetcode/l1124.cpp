#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

class Solution
{
public:
  static int longestWPI(const std::vector<int>& hours)
  {
    // ok, so first of what can I do here to speed this up?
    // OK, let's do something cheeky.
    const int N = hours.size();

		std::vector<int> PSA(N+1, 0);
		for (int i = 0; i < N; i++) {
			PSA[i + 1] = PSA[i];
			if (8 < hours[i]) {
				PSA[i+1]++;
			} else {
				PSA[i+1]--;
			}
		}

		// Ok, we are going to be running a

		
		std::vector<std::pair<int,int>> runs;
		for (int i = 0; i < N; i++) {
			const auto tiring = 8 < hours[i];

			if (!tiring) {
				continue;
			}

			if (!runs.empty() && runs.back().second == i) {
				runs.back().second++;
			} else {
				runs.emplace_back(i, i+1);
			}
		}

		std::cout << "We have the following runs:\n";
		for (const auto& [start, end] : runs) {
			std::cout << "- [" << start << ", " << end << ")\n";
		}

		// Now we really have a sort of graphish problem. Finding the costliest path throughout the
		// network that still works. I think this might be NP hard, but the datasets are so small here.
		// Can I view it as an act of moving the ones and zeros?
		//

		// ok, how about a monotonic queue?
		


		
		int ans = 0;
    return ans;
  }
};

constexpr int
bruteForce1(const std::vector<int>& hours)
{
  const int N = hours.size();
  std::vector<int> PSA(N + 1, 0);
  for (int i = 0; i < N; i++) {
    PSA[i + 1] = PSA[i] + (8 < hours[i]);
  }

  // Now we just need to find the largest interval for each
  int ans = 0;
  for (int l = 0; l < N; l++) {
    for (int r = N - 1; l <= r; r--) {
      int numDays = r - l + 1;
      int numGood = PSA[r + 1] - PSA[l];
      if (numDays < 2 * numGood) {
        ans = std::max(ans, numDays);
        break;
      }
    }
  }
  return ans;
}

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
  /* runBattery(rd(), defaultTimes, defaultSize, 0.00); */
  /* runBattery(rd(), defaultTimes, defaultSize, 0.05); */
  /* runBattery(rd(), defaultTimes, defaultSize, 0.10); */
  /* runBattery(rd(), defaultTimes, defaultSize, 0.15); */
  runBattery(seed, defaultTimes, defaultSize, 0.30);
  /* runBattery(rd(), defaultTimes, defaultSize, 0.50); */

  return 0;
}
