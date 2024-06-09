#include <iostream>
#include <memory>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class MyLinkedList
{
  struct Node
  {
    int val;

    std::unique_ptr<Node> next{ nullptr };
  };

  std::unique_ptr<Node> m_head{ nullptr };
  Node* m_tail;
  int m_sz{ 0 };

  void pop_head()
  {
    if (!m_head)
      return;

    m_head = std::move(m_head->next);
    m_sz--;
    if (m_sz == 0)
      m_tail = nullptr;
  }

public:
  int get(int index)
  {
    if (m_sz <= index)
      return -1;
    Node* cur = m_head.get();
    while (0 < index) {
      cur = cur->next.get();
      index--;
    }

    return cur->val;
  }

  void addAtHead(int val)
  {
    m_sz++;
    auto node = std::make_unique<Node>(val);
    node->next = std::move(m_head);
    m_head = std::move(node);

    if (m_sz == 1) {
      m_tail = m_head.get();
    }
  }

  void addAtTail(int val)
  {
    if (!m_tail)
      return addAtHead(val);

    m_sz++;
    m_tail->next = std::make_unique<Node>(val);
    m_tail = m_tail->next.get();
  }

  void addAtIndex(int index, int val)
  {
    if (m_sz < index)
      return;

    if (index == m_sz)
      return addAtTail(val);

    if (index == 0)
      return addAtHead(val);

    Node* cur = m_head.get();
    while (1 < index) {
      cur = cur->next.get();
      index--;
    }

    m_sz++;
    auto node = std::make_unique<Node>(val);
    node->next = std::move(cur->next);
    cur->next = std::move(node);
  }

  void deleteAtIndex(int index)
  {
    if (m_sz <= index)
      return;

    if (index == 0) {
      return pop_head();
    }

    bool atTail = index == m_sz - 1;

    Node* cur = m_head.get();
    while (1 < index) {
      cur = cur->next.get();
      index--;
    }

    if (cur->next) {
      cur->next = std::move(cur->next->next);
    } else {
      cur->next = nullptr;
    }

    m_sz--;
    if (atTail) {
      m_tail = cur;
    }
  }
};
