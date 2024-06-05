#include <deque>
#include <iostream>
#include <string>
#include <unordered_map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class AuthenticationManager
{
  std::unordered_map<std::string, int> m_data;
  using PT = std::pair<std::string, int>;
  std::deque<PT> m_expiry;

  int m_ttl;

  void processBackground(const int currentTime)
  {
    while (!m_expiry.empty()) {
      auto& [hit, exp] = m_expiry.front();
      if (currentTime < exp)
        break;

      auto it = m_data.find(hit);
      if (it->second == exp) {
        m_data.erase(it);
      }

      m_expiry.pop_front();
    }
  }

public:
  AuthenticationManager(int timeToLive) : m_ttl{ timeToLive } {}

  void generate(std::string tokenId, int currentTime)
  {
    m_data.emplace(tokenId, currentTime + m_ttl);
    m_expiry.emplace_back(std::move(tokenId), currentTime + m_ttl);
  }

  void renew(const std::string& tokenId, int currentTime)
  {
    processBackground(currentTime);

    auto it = m_data.find(tokenId);
    if (it != m_data.end()) {
      it->second = currentTime + m_ttl;
      m_expiry.emplace_back(tokenId, currentTime + m_ttl);
    }
  }

  int countUnexpiredTokens(int currentTime)
  {
    processBackground(currentTime);

    return m_data.size();
  }
};

int
main()
{
  return 0;
}
