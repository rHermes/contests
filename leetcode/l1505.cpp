#include <array>
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class BIT
{
private:
  int m_sz;
  std::vector<int> m_data;

public:
  explicit BIT(int size) : m_sz{ size + 1 }, m_data(m_sz) {}

  int query(int r)
  {
    int ret = 0;
    for (r++; 0 < r; r -= (r & -r)) {
      ret += m_data[r];
    }
    return ret;
  }

  void add(int r)
  {
    for (r++; r < m_sz; r += (r & -r)) {
      m_data[r]++;
    }
  }
};

class Solution
{
public:
  static std::string minInteger(const std::string& num, int k)
  {
    const int N = num.size();
    BIT moves{ N };

    std::array<std::vector<int>, 10> locations;
    std::vector<bool> moved(N);

    // We push them backwards, so that we can use them as stacks,
    // we want to grab the smallest digit first.
    for (int i = N - 1; 0 <= i; i--) {
      locations[num[i] - '0'].push_back(i);
    }

    std::string out;
    out.reserve(N);

    for (int idx = 0; idx < N && 0 < k; idx++) {
      // Ok, we are going to loop through each of the remaining digits and check if we
      // have the man power to move it.
      for (int ci = 0; ci < 10; ci++) {
        if (locations[ci].empty())
          continue;

        // now we will find the closest one.
        const int origLoc = locations[ci].back();
        const int forwardMoves = moves.query(origLoc);

        if (origLoc - forwardMoves <= k) {
          // we can place it.
          out.push_back('0' + ci);
          locations[ci].pop_back();

          moves.add(origLoc);
          moved[origLoc] = true;

          k -= (origLoc - forwardMoves);
          break;
        }
      }
    }

    // The ones we didn't visit we push
    for (int i = 0; i < N; i++) {
      if (!moved[i])
        out.push_back(num[i]);
    }

    return out;
  }
};
