#include <array>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

struct TrieNode
{
  int has{ -1 };
  std::array<std::unique_ptr<TrieNode>, 26> children{};

  void insert(std::string_view str, int wordX)
  {
    if (str.empty()) {
      has = wordX;
      return;
    }

    auto idx = str.front() - 'a';
    str.remove_prefix(1);

    if (!children[idx])
      children[idx] = std::make_unique<TrieNode>();

    children[idx]->insert(str, wordX);
  }
};

class Solution
{

  void dfs(std::unordered_set<int>& out,
           std::vector<std::vector<char>>& board,
           const int ROWS,
           const int COLS,
           int y,
           int x,
           TrieNode* root)
  {

    if (root->has != -1)
      out.emplace(root->has);

    // Now we just need to check very combo.
    std::initializer_list<std::pair<int, int>> deltas = { { 0, -1 }, { 0, 1 }, { -1, 0 }, { 1, 0 } };

    for (const auto& [dy, dx] : deltas) {
      const int ty = y + dy;
      const int tx = x + dx;

      if (ty < 0 || ROWS <= ty || tx < 0 || COLS <= tx)
        continue;

      if (board[ty][tx] == '$')
        continue;

      const int idx = board[ty][tx] - 'a';
      if (!root->children[idx])
        continue;

      board[ty][tx] = '$';
      dfs(out, board, ROWS, COLS, ty, tx, root->children[idx].get());
      board[ty][tx] = 'a' + idx;
    }
  }

public:
  std::vector<std::string> findWords(std::vector<std::vector<char>>& board, std::vector<std::string>& words)
  {
    TrieNode root;

    for (int i = 0; i < static_cast<int>(words.size()); i++)
      root.insert(words[i], i);

    const int ROWS = board.size();
    const int COLS = board[0].size();

    std::unordered_set<int> out;

    for (int row = 0; row < ROWS; row++) {
      for (int col = 0; col < COLS; col++) {

        const int idx = board[row][col] - 'a';
        if (root.children[idx]) {
          board[row][col] = '$';
          dfs(out, board, ROWS, COLS, row, col, root.children[idx].get());
          board[row][col] = 'a' + idx;
        }
      }
    }

    std::vector<std::string> output;
    for (const auto& x : out) {
      output.push_back(words[x]);
    }

    return output;
  }
};
