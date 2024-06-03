#include <random>
#include <string>
#include <unordered_map>

using namespace std::string_view_literals;

class Solution
{
  static constexpr auto keyspace = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"sv;
  static constexpr auto urlPrefix = "http://tinyurl.com/"sv;

  std::ranlux48 gen{ 0 };
  std::uniform_int_distribution<int> m_keyDist{ 0, std::size(keyspace) - 1 };
  std::unordered_map<std::string, std::string> m_data;

  std::string genKey()
  {
    std::string out(6, 'x');
    for (auto it = out.begin(); it != out.end(); it++) {
      *it = keyspace[m_keyDist(gen)];
    }
    return out;
  }

public:
  // Encodes a URL to a shortened URL.
  std::string encode(std::string longUrl)
  {
    while (true) {
      auto key = genKey();
      auto it = m_data.try_emplace(key, std::move(longUrl));
      if (it.second) {
        return std::string(urlPrefix) + key;
      }
    }
  }

  // Decodes a shortened URL to its original URL.
  std::string decode(std::string shortUrl)
  {
    shortUrl = shortUrl.substr(urlPrefix.size());
    return m_data[shortUrl];
  }
};

// Your Solution object will be instantiated and called as such:
// Solution solution;
// solution.decode(solution.encode(url));

int
main()
{
  return 0;
}
