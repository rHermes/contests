#include <iostream>
#include <queue>
#include <tuple>
#include <unordered_map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class FreqStack
{

  int m_seq = 0;

  std::unordered_map<int, int> m_freq;

  // Freq, seq, val
  std::priority_queue<std::tuple<int, int, int>> m_q;

public:
  void push(int val)
  {
    auto goodFreq = ++m_freq[val];
    m_q.emplace(goodFreq, m_seq++, val);
  }

  int pop()
  {
    auto [freq, seq, val] = m_q.top();
    m_q.pop();
    m_freq[val]--;
    return val;
  }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */
