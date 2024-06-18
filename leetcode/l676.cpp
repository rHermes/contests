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
  bool has{ false };
  std::array<std::unique_ptr<TrieNode>, 26> children;

  constexpr void insert(const std::string& str, const int idx)
  {
    if (idx == static_cast<int>(str.size())) {
      has = true;
      return;
    }

    const int cidx = str[idx] - 'a';
    if (!children[cidx]) {
      children[cidx] = std::make_unique<TrieNode>();
    }

    children[cidx]->insert(str, idx + 1);
  }

  constexpr bool query(const std::string& str, const int idx, bool deviated) const
  {
    if (idx == static_cast<int>(str.size())) {
      return has && deviated;
    }

    const int cidx = str[idx] - 'a';
    if (!deviated) {
      for (int i = 0; i < 26; i++) {
        if (i == cidx)
          continue;

        if (children[i] && children[i]->query(str, idx + 1, true))
          return true;
      }
    }

    if (children[cidx] && children[cidx]->query(str, idx + 1, deviated))
      return true;

    return false;
  }
};

class MagicDictionary
{
  TrieNode root;

public:
  void buildDict(const std::vector<std::string>& dictionary)
  {
    for (const auto& word : dictionary) {
      root.insert(word, 0);
    }
  }

  bool search(const std::string& searchWord) const { return root.query(searchWord, 0, false); }
};

/**
 * Your MagicDictionary object will be instantiated and called as such:
 * MagicDictionary* obj = new MagicDictionary();
 * obj->buildDict(dictionary);
 * bool param_2 = obj->search(searchWord);
 */
