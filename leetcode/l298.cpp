#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

/**
 * Definition for a binary tree node.
 */
struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Codec
{
  static void encode(std::string& out, const TreeNode* root)
  {
    // ok, so there are 4 types of nodes.
    // no children, children left, children right.

    if (root == nullptr) {
      std::uint16_t enc = 0xFFFF;
      auto beforeSize = out.size();
      out.resize(out.size() + sizeof(enc));
      std::memcpy(out.data() + beforeSize, &enc, sizeof(enc));
      return;
    }

    std::uint16_t enc = root->val + 1000;
    if (root->left)
      enc |= (1 << 15);

    if (root->right)
      enc |= (1 << 14);

    auto beforeSize = out.size();
    out.resize(out.size() + sizeof(enc));
    std::memcpy(out.data() + beforeSize, &enc, sizeof(enc));

    if (root->left)
      encode(out, root->left);

    if (root->right)
      encode(out, root->right);
  }

  static TreeNode* decode(std::string_view& data)
  {
    std::uint16_t dec = 0;
    std::memcpy(&dec, data.data(), sizeof(dec));
    data.remove_prefix(sizeof(dec));

    if (dec == 0xFFFF)
      return nullptr;

    bool hasLeft = dec & (1 << 15);
    bool hasRight = dec & (1 << 14);

    dec &= 0x3FFF;
    auto node = new TreeNode(static_cast<int>(dec) - 1000);

    if (hasLeft) {
      node->left = decode(data);
    }

    if (hasRight) {
      node->right = decode(data);
    }

    return node;
  }

public:
  // Encodes a tree to a single string.
  static std::string serialize(const TreeNode* root)
  {
    std::string out;
    out.reserve(16);
    encode(out, root);
    return out;
  }

  // Decodes your encoded data to tree.
  static TreeNode* deserialize(const std::string& data)
  {
    std::string_view view = data;
    return decode(view);
  }
};

int
main()
{
  return 0;
}
