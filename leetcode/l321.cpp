#include <iostream>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  static constexpr void mergeTwo(const int k,
                                 const std::vector<int>& src1,
                                 const std::vector<int>& src2,
                                 std::vector<int>& out)
  {
    const int B1 = src1.size();
    const int B2 = src2.size();

    int idx = 0;

    bool better = false;

    const auto addIt = [&](const int cand) {
      if (better) {
        out[idx++] = cand;
      } else {
        if (cand == out[idx]) {
          idx++;
        } else if (out[idx] < cand) {
          better = true;
          out[idx++] = cand;
        } else {
          return false;
        }
      }

      return true;
    };

    int i1 = 0;
    int i2 = 0;

    while (idx < k && i1 != B1 && i2 != B2) {
      const int a = src1[i1];
      const int b = src2[i2];

      const int cand = std::max(a, b);
      if (!addIt(cand))
        return;

      if (a < b) {
        i2++;
      } else if (b < a) {
        i1++;
      } else {
        int i = 1;
        while (i1 + i < B1 && i2 + i < B2) {
          if (src1[i1 + i] == src2[i2 + i]) {
            i++;
          } else {
            break;
          }
        }

        int* one = nullptr;
        const std::vector<int>* arr = nullptr;

        if (i1 + i == B1) {
          one = &i2;
          arr = &src2;
        } else if (i2 + i == B2) {
          one = &i1;
          arr = &src1;
        } else if (src1[i1 + i] < src2[i2 + i]) {
          one = &i2;
          arr = &src2;
        } else {
          one = &i1;
          arr = &src1;
        }

        const auto& hey = *arr;
        auto& ww = *one;

        ww++;

        // We remove the common prefix
        for (int z = 1; z < i; z++) {
          if (idx == k)
            break;

          if (hey[ww] != a) {
            break;
          }

          ww++;

          if (!addIt(a))
            return;
        }
      }
    }

    while (idx < k && i1 < B1) {
      if (!addIt(src1[i1++]))
        return;
    }

    while (idx < k && i2 < B2) {
      if (!addIt(src2[i2++]))
        return;
    }

    return;
  }

public:
  static constexpr std::vector<int> maxNumber(const std::vector<int>& nums1, const std::vector<int>& nums2, const int k)
  {

    const int N1 = nums1.size();
    const int N2 = nums2.size();

    // Find the most competative array of at least size K
    constexpr auto getBestK = [](const std::vector<int>& src, const int K) {
      const int SN = src.size();

      std::vector<int> st;
      for (int i = 0; i < SN; i++) {
        const auto x = src[i];
        while (!st.empty() && st.back() < x) {
          // ok, how many elements are left
          const int left = SN - i;
          const int sz = st.size();
          if ((left + sz) <= K)
            break;

          st.pop_back();
        }

        st.push_back(x);
      }
      return st;
    };

    std::vector<int> out(k, 0);

    int neededK1 = k - N2;
    while (neededK1 <= N1) {
      const auto bestHere1 = getBestK(nums1, neededK1);
      const int neededK2 = k - bestHere1.size();
      const auto bestHere2 = getBestK(nums2, neededK2);

      neededK1 = std::max(neededK1, static_cast<int>(bestHere1.size())) + 1;
      mergeTwo(k, bestHere1, bestHere2, out);
    }

    return out;
  }
};
