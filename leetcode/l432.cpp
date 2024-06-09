#include <iostream>
#include <list>
#include <string>
#include <unordered_map>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class AllOne
{

  struct ClusterNode;

  struct UnderNode
  {
    std::string key;
    std::list<ClusterNode>::iterator parent;
    std::list<UnderNode*>::iterator our;
  };

  struct ClusterNode
  {
    int value{ 0 };
    std::list<UnderNode*> nodes;
  };

  std::list<ClusterNode> m_clusters;

  std::unordered_map<std::string, UnderNode> m_kv;

public:
  void inc(const std::string& key)
  {
    auto it = m_kv.find(key);
    if (it == m_kv.end()) {
      if (m_clusters.empty() || m_clusters.front().value != 1) {
        m_clusters.emplace_front(1);
      }

      UnderNode node{ key, m_clusters.begin(), {} };
      auto [it2, _] = m_kv.emplace(node.key, std::move(node));

      m_clusters.front().nodes.push_front(&it2->second);
      it2->second.our = m_clusters.front().nodes.begin();

      return;
    }

    auto& unode = it->second;

    auto curNode = unode.parent;
    auto nextNode = std::next(curNode);

    if (nextNode == m_clusters.end() || (curNode->value + 1 != nextNode->value)) {
      nextNode = m_clusters.emplace(nextNode, curNode->value + 1);
    }

    nextNode->nodes.splice(nextNode->nodes.begin(), curNode->nodes, unode.our);
    unode.parent = nextNode;
    unode.our = nextNode->nodes.begin();

    if (curNode->nodes.empty()) {
      m_clusters.erase(curNode);
    }
  }

  void dec(const std::string& key)
  {
    auto& node = m_kv[key];

    auto curNode = node.parent;
    if (curNode->value != 1) {
      if (curNode == m_clusters.begin() || std::prev(curNode)->value != (curNode->value - 1)) {
        m_clusters.emplace(curNode, curNode->value - 1);
      }

      auto prevNode = std::prev(curNode);
      prevNode->nodes.splice(prevNode->nodes.begin(), curNode->nodes, node.our);
      node.parent = prevNode;
      node.our = prevNode->nodes.begin();
    } else {
      curNode->nodes.erase(node.our);
      m_kv.erase(key);
    }

    if (curNode->nodes.empty()) {
      m_clusters.erase(curNode);
    }
  }

  std::string getMaxKey()
  {
    if (m_clusters.empty())
      return "";
    else
      return m_clusters.back().nodes.front()->key;
  }

  std::string getMinKey()
  {
    if (m_clusters.empty())
      return "";
    else
      return m_clusters.front().nodes.front()->key;
  }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
