#include <array>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class WordFilter
{

  struct TrieNode
  {
    int index{ -1 };
    std::array<std::unique_ptr<TrieNode>, 27> kids{};

    constexpr TrieNode* insert(const std::string& data, int idx, int val)
    {
      index = val;
      if (idx == static_cast<int>(data.size())) {
        return this;
      }

      const int cc = data[idx] - 'a';
      if (!kids[cc])
        kids[cc] = std::make_unique<TrieNode>();

      return kids[cc]->insert(data, idx + 1, val);
    }

    constexpr const TrieNode* query(const std::string& data, int idx) const
    {
      if (idx == static_cast<int>(data.size())) {
        return this;
      }

      const int cc = data[idx] - 'a';
      if (!kids[cc])
        return nullptr;

      return kids[cc]->query(data, idx + 1);
    }
  };

  TrieNode root;

public:
  constexpr WordFilter(const std::vector<std::string>& words)
  {
    for (int i = 0; i < static_cast<int>(words.size()); i++) {
      const auto& word = words[i];
      for (int j = 0; j <= static_cast<int>(word.size()); j++) {
        auto ptr = root.insert(word, j, i);

        if (!ptr->kids[26])
          ptr->kids[26] = std::make_unique<TrieNode>();

        ptr->kids[26]->insert(word, 0, i);
      }
    }
  }

  constexpr int f(const std::string& pref, const std::string& suff) const
  {
    auto ptr = root.query(suff, 0);
    if (ptr == nullptr || !ptr->kids[26]) {
      return -1;
    }

    ptr = ptr->kids[26]->query(pref, 0);

    if (ptr)
      return ptr->index;
    else
      return -1;
  }
};

/**
 * Your WordFilter object will be instantiated and called as such:
 * WordFilter* obj = new WordFilter(words);
 * int param_1 = obj->f(pref,suff);
 */

int
main()
{
  return 0;
}
