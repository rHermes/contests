
class Solution
{

public:
  static constexpr long long distributeCandies(const int N, const int limit)
  {
    // Ok, we are in a fun position here. We are going to use the
    // inclusion-exclusion principle here.'

    constexpr auto combo = [](long long n) { return ((n + 2) * (n + 1)) / 2LL; };

    long long ans = combo(N);
    auto left1 = N - (limit + 1);
    if (left1 < 0) {
      return ans;
    } else {
      ans -= 3 * combo(left1);
    }

    auto left2 = N - 2 * (limit + 1);
    if (left2 < 0) {
      return ans;
    } else {
      ans += 3 * combo(left2);
    }

    auto left3 = N - 3 * (limit + 1);
    if (left3 < 0) {
      return ans;
    } else {
      ans -= combo(left3);
    }

    return ans;
  }
};
