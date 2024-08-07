#include <cstdint>
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
  using ST = std::int64_t;

  // We build our own little stack class, to avoid having to zero out the vector. We also allocate an extra member,
  // which we set to -1. This helps avoids the problem of having to branch on the pop operation in the solution.
  class MyStack
  {
    int m_sz;
    int m_idx{ 0 };
    int* m_data{ nullptr };

  public:
    constexpr MyStack(const int n) : m_sz{ n + 1 }
    {
      m_data = new int[m_sz];
      m_data[0] = -1;
    }

    constexpr ~MyStack() { delete[] m_data; }

    constexpr void push(const int x) { m_data[++m_idx] = x; }
    constexpr int pop() { return m_data[m_idx--]; }

    [[nodiscard]] constexpr bool empty() const { return m_idx < 1; }
    [[nodiscard]] constexpr const int& back() const { return m_data[m_idx]; }
  };

public:
  static constexpr int sumSubarrayMins(const std::vector<int>& arr)
  {
    const int N = arr.size();

    ST ans = 0;
    constexpr ST MODN = 1000000007;

    MyStack st(N);

    const auto popStack = [&](const int idx) {
      const int index = st.pop();

      const int rightSpace = idx - index;
      const int leftSpace = index - st.back();

      ans += static_cast<ST>(arr[index]) * (rightSpace * leftSpace);
      ans %= MODN;
    };

    for (int i = 0; i < N; i++) {
      while (!st.empty() && arr[i] < arr[st.back()]) {
        popStack(i);
      }

      st.push(i);
    }

    while (!st.empty()) {
      popStack(N);
    }

    return ans;
  }
};
