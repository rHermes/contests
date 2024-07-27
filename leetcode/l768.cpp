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
public:
  static constexpr int maxChunksToSorted(const std::vector<int>& arr)
  {
    const int N = arr.size();
    std::vector<int> st;

    st.push_back(arr[0]);
    int i = 1;
    while (i < N) {
      const auto y = arr[i];
      if (st.back() <= y) {
        st.push_back(y);
        i++;
      } else {
        // The largest we had before this small one destroys.
        const int x = st.back();

        // While things are smaller, remove the elements.
        while (!st.empty() && y < st.back()) {
          st.pop_back();
        }

        st.push_back(x);
        i++;
      }
    }

    return st.size();
  }
};
