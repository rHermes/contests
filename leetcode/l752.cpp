#include <algorithm>
#include <array>
#include <bitset>
#include <cstdint>
#include <queue>
#include <string>
#include <vector>

class Solution
{
public:
  int openLock(std::vector<std::string>& deadends, std::string target)
  {
    // ok, so we are going to use A* with a modification
    using AR = std::array<std::uint8_t, 4>;

    constexpr auto toNum = [](const std::string& t) {
      std::uint32_t idx = 0;
      for (const auto c : t) {
	idx *= 10;
	idx += c - '0';
      }

      return idx;
    };

    constexpr auto toNumA = [](AR t) {
      std::uint32_t idx = 0;
      for (const auto c : t) {
	idx *= 10;
	idx += c;
      }

      return idx;
    };

    constexpr auto fromNum = [](std::uint32_t c) {
      AR a{};

      for (std::size_t i = 0; i < 4; i++) {
	a[3 - i] = c % 10;
	c /= 10;
      };

      return a;
    };

    const auto nTarget = toNum(target);
    const auto aTarget = fromNum(nTarget);

    const auto distTarget = [aTarget](AR other) {
      uint8_t dist = 0;
      for (std::size_t i = 0; i < 4; i++) {
	auto [a, b] = std::minmax(aTarget[i], other[i]);
	dist += std::min(b - a, a + (10 - b));
      }
      return dist;
    };

    std::bitset<10000> seen;
    for (const auto& ded : deadends) {
      seen[toNum(ded)] = true;
    }

    // score, steps, num
    using QT = std::tuple<std::uint32_t, std::uint32_t, std::uint32_t>;

    std::priority_queue<QT, std::vector<QT>, std::greater<QT>> Q;
    auto root = toNum("0000");
    Q.emplace(distTarget(fromNum(root)), 0, root);

    while (!Q.empty()) {
      const auto [_, steps, cur] = Q.top();
      Q.pop();

      if (seen[cur])
	continue;

      seen[cur] = true;

      if (cur == nTarget)
	return steps;

      auto curA = fromNum(cur);

      for (std::size_t i = 0; i < 4; i++) {
	// we go forward or downwards.
	if (curA[i] == 0) {
	  curA[i] = 9;

	  const auto lel = toNumA(curA);
	  if (!seen[lel]) {
	    Q.emplace(steps + distTarget(curA) + 1, steps + 1, lel);
	  }

	  curA[i] = 0;
	} else {
	  curA[i]--;
	  const auto lel = toNumA(curA);
	  if (!seen[lel]) {
	    Q.emplace(steps + distTarget(curA) + 1, steps + 1, lel);
	  }
	  curA[i]++;
	}

	// we go forward or downwards.
	if (curA[i] == 9) {
	  curA[i] = 0;

	  const auto lel = toNumA(curA);
	  if (!seen[lel]) {
	    Q.emplace(steps + distTarget(curA) + 1, steps + 1, lel);
	  }

	  curA[i] = 9;
	} else {
	  curA[i]++;
	  const auto lel = toNumA(curA);
	  if (!seen[lel]) {
	    Q.emplace(steps + distTarget(curA) + 1, steps + 1, lel);
	  }
	  curA[i]--;
	}
      }
    }

    return -1;
  }
};

int
main()
{
  return 0;
}
