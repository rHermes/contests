
#include <iostream>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class BrowserHistory
{
  std::vector<std::string> m_hist;
  int m_watermark{ 0 };

public:
  BrowserHistory(std::string homepage)
  {
    m_hist.reserve(5000);
    m_hist.emplace_back(std::move(homepage));
  }

  void visit(std::string url)
  {
    m_hist.resize(m_watermark + 2);
    m_hist[++m_watermark] = std::move(url);
  }

  std::string back(int steps)
  {
    m_watermark = std::max(0, m_watermark - steps);
    return m_hist[m_watermark];
  }

  std::string forward(int steps)
  {
    m_watermark = std::min(m_watermark + steps, static_cast<int>(m_hist.size()) - 1);
    return m_hist[m_watermark];
  }
};
