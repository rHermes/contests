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

class Solution
{
  inline static int nodes = 0;
  struct TrieNode
  {
    bool done{ false };
    std::array<std::unique_ptr<TrieNode>, 26> kids{};

    constexpr void insert(const std::string& data, int idx)
    {
      if (done) {
        return;
      }

      if (idx == static_cast<int>(data.size())) {
        done = true;
        return;
      }

      const int cc = data[idx] - 'a';
      if (!kids[cc])
        kids[cc] = std::make_unique<TrieNode>();

      kids[cc]->insert(data, idx + 1);
    }
  };

public:
  static std::string replaceWords(const std::vector<std::string>& dictionary, const std::string& sentence)
  {
    TrieNode root;
    for (const auto& str : dictionary)
      root.insert(str, 0);

    std::string output;
    output.reserve(sentence.size());

    const int N = sentence.size();
    TrieNode* cur = &root;
    for (int i = 0; i < N; i++) {
      const char c = sentence[i];
      if (c == ' ') {
        cur = &root;
        output.push_back(' ');
      } else if (cur && cur->done) {
        continue;
      } else {
        output.push_back(c);
        if (cur) {
          cur = cur->kids[c - 'a'].get();
        }
      }
    }

    return output;
  }
};
