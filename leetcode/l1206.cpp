#include <iostream>
#include <random>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Skiplist
{
  using T = int;

  struct Node
  {
    int val{ -1 };

    T next{ -1 };
    T prev{ -1 };
    T child{ -1 };
  };

  // ok, I'm going to be fancy here. and use a memory pool
  std::vector<Node> m_pool;
  T m_freeList{ -1 };

  T m_root{ -1 };

  std::ranlux48 m_gen{ 0 };
  std::bernoulli_distribution m_dist{ 0.5 };

  constexpr T getNode(int val)
  {
    T ourNode = -1;
    if (m_freeList != -1) {
      ourNode = m_freeList;
      m_freeList = m_pool[ourNode].next;
    } else {
      m_pool.emplace_back();
      ourNode = m_pool.size() - 1;
    }

    // Reset the node
    m_pool[ourNode] = { val, -1, -1, -1 };
    return ourNode;
  }

  constexpr T insertNodeAfter(const T cur, const int num)
  {
    auto us = getNode(num);
    auto& node = m_pool[cur];
    auto& newNode = m_pool[us];

    newNode.next = node.next;
    newNode.prev = cur;
    if (node.next != -1) {
      m_pool[node.next].prev = us;
    }
    node.next = us;

    return us;
  }

  constexpr T insertInLevel(const T cur, const int num)
  {
    auto node = &m_pool[cur];

    if (node->next != -1 && m_pool[node->next].val <= num)
      return insertInLevel(node->next, num);

    // Ok, so we are not going forward. Now there are two choices.
    // either we are going down or we are inserting it here.

    if (node->child == -1) {
      return insertNodeAfter(cur, num);
    }

    auto childNode = insertInLevel(node->child, num);
    if (childNode == -1 || !m_dist(m_gen))
      return -1;

    auto us = insertNodeAfter(cur, num);
    m_pool[us].child = childNode;
    return us;
  }

  constexpr T internalSearch(int target) const
  {
    auto cur = m_root;

    while (cur != -1) {
      const auto& node = m_pool[cur];
      if (node.val == target)
        return cur;

      if (node.next != -1 && m_pool[node.next].val <= target) {
        cur = node.next;
        continue;
      }

      cur = node.child;
    }

    return -1;
  }

public:
  Skiplist()
  {
    m_pool.reserve(1000);
    for (int i = 0; i < 10; i++) {
      T newRoot = getNode(-1);
      m_pool[newRoot].child = m_root;
      m_root = newRoot;
    }
  }

  constexpr bool search(int target) const { return internalSearch(target) != -1; }

  constexpr void add(int num) { insertInLevel(m_root, num); }

  constexpr bool erase(int num)
  {
    auto cur = internalSearch(num);
    if (cur == -1) {
      return false;
    }

    // ok, now we are going to remove parent and then the child
    while (cur != -1) {
      auto& node = m_pool[cur];
      const auto next = node.next;
      const auto prev = node.prev;

      if (next != -1)
        m_pool[next].prev = prev;

      if (prev != -1)
        m_pool[prev].next = next;

      // Place the node into the freelist
      node.next = m_freeList;
      m_freeList = cur;

      cur = node.child;
    }
    return true;
  }
};
