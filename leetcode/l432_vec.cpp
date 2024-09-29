#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

// VectorList is a better performing linked list, on average.
// It does however make this entire thing a huge pain.

class AllOne
{
  using ID = std::int32_t;

  struct UnderNode
  {
    ID prev{ -1 };
    ID next{ -1 };

    ID parent{ -1 };
    std::string key;
  };

  struct ClusterNode
  {
    ID prev{ -1 };
    ID next{ -1 };

    int freq{ 1 };
    ID underHead{ -1 };
  };

  std::vector<UnderNode> m_underNodes;
  std::vector<ClusterNode> m_clusterNodes;

  std::unordered_map<std::string, ID> m_kv;

  // We keep track of the beginning and end for queries.
  ID m_clusterHead{ -1 };
  ID m_clusterTail{ -1 };

  // Freelists for the different types of nodes.
  ID m_freeUnderNodes{ -1 };
  ID m_freeClusterNodes{ -1 };

  constexpr void freeClusterNode(const ID id)
  {
    m_clusterNodes[id].next = m_freeClusterNodes;
    m_freeClusterNodes = id;
  }

  constexpr void freeUnderNode(const ID id)
  {
    m_underNodes[id].next = m_freeUnderNodes;
    m_freeUnderNodes = id;
  }

  [[nodiscard]] constexpr ID getFreshClusterNode()
  {
    if (m_freeClusterNodes != -1) {
      const auto ret = m_freeClusterNodes;
      m_freeClusterNodes = m_clusterNodes[ret].next;
      return ret;
    } else {
      const ID ret = m_clusterNodes.size();
      m_clusterNodes.emplace_back();
      return ret;
    }
  }

  [[nodiscard]] constexpr ID getFreshUnderNode()
  {
    if (m_freeUnderNodes != -1) {
      const auto ret = m_freeUnderNodes;
      m_freeUnderNodes = m_underNodes[ret].next;
      return ret;
    } else {
      const ID ret = m_underNodes.size();
      m_underNodes.emplace_back();
      return ret;
    }
  }

public:
  AllOne()
  {
    // too avoid too much resizing and copying.
    m_clusterNodes.reserve(100);
    m_underNodes.reserve(1000);
  }

  void inc(const std::string& key)
  {
    auto it = m_kv.find(key);
    if (it == m_kv.end()) {
      if (m_clusterHead == -1 || m_clusterNodes[m_clusterHead].freq != 1) {
        const auto nid = getFreshClusterNode();
        m_clusterNodes[nid] = { .prev = -1, .next = m_clusterHead, .freq = 1 };

        if (m_clusterHead == -1) {
          m_clusterTail = nid;
        } else {
          m_clusterNodes[m_clusterHead].prev = nid;
        }
        m_clusterHead = nid;
      }

      auto& cHead = m_clusterNodes[m_clusterHead];

      const auto unid = getFreshUnderNode();
      m_underNodes[unid] = { .prev = -1, .next = cHead.underHead, .parent = m_clusterHead, .key = key };

      if (cHead.underHead != -1) {
        m_underNodes[cHead.underHead].prev = unid;
      }
      cHead.underHead = unid;

      m_kv.emplace(key, unid);
      return;
    }

    // Ok, nowe we are here.
    const auto unid = it->second;
    auto& curUnderNode = m_underNodes[unid];

    const auto curNodeId = curUnderNode.parent;
    auto& curNode = m_clusterNodes[curNodeId];

    const auto prevNodeId = curNode.prev;
    const auto nextNodeId = curNode.next;

    // Ok, I'll bite. We could make this faster by having a dummy start and a dummy
		// end node, but I prefer it like this. I'll map out all the scenarios and
		// even though it makes the code messy, it will perform quite well I think.
    if (unid == curNode.underHead && m_underNodes[curNode.underHead].next == -1) {
      // ok, so this node is the only one in the current node, we can now
      // try to do some smart things.
      if (nextNodeId == -1 || m_clusterNodes[nextNodeId].freq != (curNode.freq + 1)) {
        // ok, easy we just increase the freq
        curNode.freq++;
        return;
      }

      // Ok, we need to move the node over, then free the current one.
      auto& nextNode = m_clusterNodes[nextNodeId];
      curUnderNode.prev = -1;
      curUnderNode.next = nextNode.underHead;
      curUnderNode.parent = nextNodeId;

      m_underNodes[nextNode.underHead].prev = unid;
      nextNode.underHead = unid;

      nextNode.prev = prevNodeId;
      if (prevNodeId == -1) {
        // we are the front, so the head will move.
        m_clusterHead = nextNodeId;
      } else {
        m_clusterNodes[prevNodeId].next = nextNodeId;
      }
      freeClusterNode(curNodeId);

      return;
    } else {
      // ok, let's remove my current one.
      if (unid == curNode.underHead) {
        curNode.underHead = curUnderNode.next;
        m_underNodes[curUnderNode.next].prev = -1;
      } else {
        // We are in the middle.
        m_underNodes[curUnderNode.prev].next = curUnderNode.next;
        if (curUnderNode.next != -1) {
          m_underNodes[curUnderNode.next].prev = curUnderNode.prev;
        }
      }

      // we know it's not empty, so we are going to need a new node
      // regardless.

      // Ok, we know that the current node is not empty, so we are going
      // to have to either move it forward or create a new one.
      if (nextNodeId == -1 || m_clusterNodes[nextNodeId].freq != (curNode.freq + 1)) {
        // ok, no next node, or it's in the wrong.
        const auto newNodeId = getFreshClusterNode();
        auto& newNode = m_clusterNodes[newNodeId];

        m_clusterNodes[curNodeId].next = newNodeId;

        newNode.freq = m_clusterNodes[curNodeId].freq + 1;
        newNode.prev = curNodeId;
        newNode.next = nextNodeId;
        newNode.underHead = unid;

        curUnderNode.next = -1;
        curUnderNode.prev = -1;
        curUnderNode.parent = newNodeId;

        if (newNode.next == -1) {
          m_clusterTail = newNodeId;
        } else {
          m_clusterNodes[newNode.next].prev = newNodeId;
        }
      } else {
        // we just move em over.
        auto& nextNode = m_clusterNodes[nextNodeId];

        curUnderNode.next = nextNode.underHead;
        curUnderNode.prev = -1;
        curUnderNode.parent = nextNodeId;

        m_underNodes[curUnderNode.next].prev = unid;
        nextNode.underHead = unid;
      }
    }
  }

  void dec(const std::string& key)
  {
    // ok, so this is just the same as before, just in reverse, so get ready
    // for pain. We always know that we are in here.
    auto it = m_kv.find(key);

    const auto curUnderNodeId = it->second;
    auto& curUnderNode = m_underNodes[curUnderNodeId];

    const auto curNodeId = curUnderNode.parent;
    auto& curNode = m_clusterNodes[curNodeId];

    const auto nextNodeId = curNode.next;
    const auto prevNodeId = curNode.prev;

    // Check if the key is alone in the node
    if (curUnderNodeId == curNode.underHead && curUnderNode.next == -1) {

      // ok, if we are one, we just free all involved here
      if (curNode.freq == 1) {
        m_kv.erase(it);

        freeUnderNode(curUnderNodeId);
        m_clusterHead = nextNodeId;
        if (nextNodeId != -1) {
          m_clusterNodes[nextNodeId].prev = -1;
        } else {
          m_clusterTail = -1;
        }
        freeClusterNode(curNodeId);
        return;
      }

      // ok, so we are not 1, but maybe the one behind us is nothing.
      if (prevNodeId == -1 || m_clusterNodes[prevNodeId].freq != (curNode.freq - 1)) {
        // We can just decrease our own freq
        curNode.freq--;
        return;
      }

      auto& prevNode = m_clusterNodes[prevNodeId];

      // ok so we just need to move it backwards.
      curUnderNode.parent = prevNodeId;

      curUnderNode.next = prevNode.underHead;
      curUnderNode.prev = -1;
      m_underNodes[prevNode.underHead].prev = curUnderNodeId;

      prevNode.underHead = curUnderNodeId;

      if (nextNodeId == -1) {
        prevNode.next = -1;
        m_clusterTail = prevNodeId;
      } else {
        prevNode.next = nextNodeId;
        m_clusterNodes[nextNodeId].prev = prevNodeId;
      }

      freeClusterNode(curNodeId);
      return;
    } else {
      // ok, so we are not an only child, very sad, we are going to need
      // to split.
      if (curUnderNodeId == curNode.underHead) {
        m_underNodes[curUnderNode.next].prev = -1;
        curNode.underHead = curUnderNode.next;
      } else {
        // we are in the middle.
        m_underNodes[curUnderNode.prev].next = curUnderNode.next;
        if (curUnderNode.next != -1) {
          m_underNodes[curUnderNode.next].prev = curUnderNode.prev;
        }
      }

      // If we are at one, we simply free it.
      if (curNode.freq == 1) {
        m_kv.erase(it);
        freeUnderNode(curUnderNodeId);

        return;
      }

      // ok, now we have two variants. Either we will need a new node, or
      // we won't, let's see.
      if (prevNodeId == -1 || m_clusterNodes[prevNodeId].freq != (curNode.freq - 1)) {
        const auto newNodeId = getFreshClusterNode();
        auto& newNode = m_clusterNodes[newNodeId];

        newNode = {
          .prev = prevNodeId, .next = curNodeId, .freq = m_clusterNodes[curNodeId].freq - 1, .underHead = curUnderNodeId
        };
        curUnderNode.prev = -1;
        curUnderNode.next = -1;
        curUnderNode.parent = newNodeId;

        m_clusterNodes[curNodeId].prev = newNodeId;

        if (prevNodeId == -1) {
          m_clusterHead = newNodeId;
        } else {
          m_clusterNodes[prevNodeId].next = newNodeId;
        }

        return;
      }

      // ok, so we are just moving it to the new node.
      auto& prevNode = m_clusterNodes[prevNodeId];
      curUnderNode.parent = prevNodeId;
      curUnderNode.prev = -1;
      curUnderNode.next = prevNode.underHead;
      m_underNodes[prevNode.underHead].prev = curUnderNodeId;
      prevNode.underHead = curUnderNodeId;
    }
  }

  [[nodiscard]] constexpr std::string getMaxKey() const
  {
    if (m_clusterTail == -1)
      return "";

    // Cluster tail is the last one.
    const auto unid = m_clusterNodes[m_clusterTail].underHead;
    return m_underNodes[unid].key;
  }

  [[nodiscard]] constexpr std::string getMinKey() const
  {
    if (m_clusterHead == -1)
      return "";

    const auto unid = m_clusterNodes[m_clusterHead].underHead;
    return m_underNodes[unid].key;
  }

  // Helper function I wrote to validate the tree, as things got messy.
  void validateTree() const
  {
    if (m_clusterHead == -1) {
      assert(m_clusterTail == -1);
      return;
    }

    auto curId = m_clusterHead;
    assert(m_clusterNodes[curId].prev == -1);
    while (true) {
      const auto& curNode = m_clusterNodes[curId];
      std::cout << "Cluster " << curId << ": freq = " << curNode.freq << ", next = " << curNode.next << "\n";
      std::cout << std::flush;

      assert(curNode.underHead != -1);
      assert(m_underNodes[curNode.underHead].prev == -1);

      auto underId = curNode.underHead;
      while (true) {
        const auto& underNode = m_underNodes[underId];

        std::cout << "\t Under " << underId << ": key = " << underNode.key << ", parent = " << underNode.parent
                  << ", next =" << underNode.next << "\n";

        assert(underNode.parent == curId);
        if (underNode.next == -1) {
          break;
        }

        std::cout << std::flush;
        assert(m_underNodes[underNode.next].prev == underId);

        underId = underNode.next;
      }

      if (curNode.next == -1) {
        assert(curId == m_clusterTail);
        break;
      }

      assert(m_clusterNodes[curNode.next].prev == curId);

      curId = curNode.next;
    }
  }
};
