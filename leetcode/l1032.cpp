#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

struct TrieNode
{
  bool m_here{ false };
  std::array<std::unique_ptr<TrieNode>, 26> m_data{};

  TrieNode* next(char c) { return m_data[c - 'a'].get(); }

  void insert(const std::string& s, int i)
  {
    if (i == static_cast<int>(s.size())) {
      m_here = true;
      return;
    }

    auto idx = s[i] - 'a';

    if (!m_data[idx]) {
      m_data[idx] = std::make_unique<TrieNode>();
    }

    m_data[idx]->insert(s, i + 1);
  }
};

class StreamChecker
{
  TrieNode m_root;
  std::vector<TrieNode*> m_alive;

public:
  StreamChecker(const std::vector<std::string>& words)
  {
    // We build a trie, and then we maintain a bunch of pointers to it.
    for (const auto& word : words)
      m_root.insert(word, 0);
  }

  bool query(char letter)
  {
    m_alive.emplace_back(&m_root);
    bool ret = false;
    for (auto& ptr : m_alive) {
      ptr = ptr->next(letter);
      if (ptr && ptr->m_here)
        ret = true;
    }

    auto e = std::ranges::remove(m_alive, nullptr);
    m_alive.erase(e.begin(), e.end());

    return ret;
  }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */
