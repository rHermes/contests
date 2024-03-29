#include <map>
#include <vector>

inline constexpr int MODN = 1000000007;

class Solution {
public:
  std::map<std::pair<int, int>, int> contribs;
  int getAnswer(const std::vector<int> &nums, const int k, const int curSum, const int curPos) {
    if (curPos == static_cast<int>(nums.size()))
      return curSum == k;

    const auto key = std::make_pair(curSum, curPos);
    if (auto it = contribs.find(key); it != contribs.end())
      return it->second;

    const auto thisVal = nums[curPos];

    auto answer = (2 * getAnswer(nums, k, curSum, curPos + 1)) % MODN;
    if (thisVal + curSum <= k)
      answer += getAnswer(nums, k, curSum + thisVal, curPos + 1);

    answer %= MODN;

    contribs[key] = answer;

    return answer;
  }

  int sumOfPower(std::vector<int> &nums, int k) { return getAnswer(nums, k, 0, 0); }
};

int main() { return 0; }
