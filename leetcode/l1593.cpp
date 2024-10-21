#include <array>
#include <string>
#include <utility>

// OK, so I think there is a case to be made here for a trie.
// But I have to be smart about it. The good thing about it, is that
// it would allow me to quickly iterate on if a given string is in the
// system, a new hash would not have to be caluclated each time.
//
// The problem will be the deleting.
// How do I do the deleting in a way which is fast.
// Let's think about it. Since we have no overlaps, there will only
// ever be 16 end nodes.
// Now worst case scenario, those nodes don't share any ancestors,
// so there is 16 of them, plus the root.
// So lets  work with that. We allocate all 17 nodes up front, and we have a
// freelist.

class Solution
{

  struct TrieNode
  {
    bool end{ false };
    std::array<char, 26> children{ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
                                   -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
  };

  std::array<TrieNode, 17> m_nodes{};
  char m_freeList = -1;
  char m_root = 0;

  [[nodiscard]] char getNode()
  {
    auto out = m_freeList;
    m_freeList = m_nodes[out].children[0];
    m_nodes[out].children[0] = -1;
    return out;
  }

  void freeNode(char idx)
  {
    m_nodes[idx].children[0] = m_freeList;
    m_freeList = idx;
  }

  int solve(const std::string& s, const int N, const int startPos)
  {
    if (startPos == N)
      return 0;

    int ans = -1;

    // ok, first we iterate through all the ones we already have.
    char curNode = m_root;
    int i = startPos;
    for (; i < N; i++) {
      if ((N - i) <= ans) {
        return 1 + ans;
      }

      const int cIdx = s[i] - 'a';
      auto& cNode = m_nodes[curNode];
      const auto nextNodeIdx = cNode.children[cIdx];
      if (nextNodeIdx == -1) {
        break;
      }

      auto& nNode = m_nodes[nextNodeIdx];
      curNode = nextNodeIdx;

      if (!nNode.end) {
        nNode.end = true;
        ans = std::max(ans, solve(s, N, i + 1));
        nNode.end = false;
      }

      curNode = nextNodeIdx;
    }

    if (i == N) {
      return ans + 1;
    }

    // Now then, we are either at our end, or we are going to be allocating
    // new nodes. The nodes we have created, which at the end of this
    // function will need to be cleared.
    const int origI = i;
    const char oldRoot = curNode;

    for (; i < N; i++) {
      if ((N - i) <= ans) {
        break;
      }

      // We know that the next node will need a fresh one.
      const int cIdx = s[i] - 'a';
      const auto newNodeId = getNode();
      m_nodes[curNode].children[cIdx] = newNodeId;

      auto& nNode = m_nodes[newNodeId];

      nNode.end = true;
      ans = std::max(ans, solve(s, N, i + 1));
      nNode.end = false;

      curNode = newNodeId;
    }

    if (origI != i) {
      curNode = std::exchange(m_nodes[oldRoot].children[s[origI] - 'a'], -1);
      for (int j = origI + 1; j < i; j++) {
        const int cIdx = s[j] - 'a';
        // We free the current node, first when we get forward.
        auto nNodeIdx = std::exchange(m_nodes[curNode].children[cIdx], -1);

        freeNode(curNode);

        curNode = nNodeIdx;
      }
      freeNode(curNode);
    }

    return ans + 1;
  }

public:
  Solution()
  {
    // ok, we setup the freelist now. The solution ensures that this is good
    // for the rest of the solution as well.
    for (int i = 0; i < static_cast<int>(m_nodes.size()); i++) {
      m_nodes[i].children[0] = m_freeList;
      m_freeList = i;
    }

    m_root = getNode();
  }

  int maxUniqueSplit(const std::string& s)
  {
    const int N = s.size();
    return solve(s, N, 0);
  }
};
