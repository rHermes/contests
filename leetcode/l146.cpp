#include <iostream>
#include <list>
#include <unordered_map>

class LRUCache
{
public:
  int cap_;
  std::list<std::pair<int, int>> nodes;
  std::unordered_map<int, decltype(nodes)::iterator> dict;

  LRUCache(int capacity) : cap_{ capacity } {}

  int get(int key)
  {
    auto it = dict.find(key);
    if (it == dict.end()) {
      return -1;
    }
    nodes.splice(nodes.begin(), nodes, it->second);

    return it->second->second;
  }

  void put(int key, int value)
  {
    if (auto it = dict.find(key); it != dict.end()) {
      nodes.splice(nodes.begin(), nodes, it->second);
      it->second->second = value;
      return;
    }

    // ok, so there are two options. Either we have enough nodes.
    if (nodes.size() < static_cast<unsigned int>(cap_)) {
      nodes.emplace_front(key, value);
      dict.emplace(key, nodes.begin());
    } else {
      // ok, so we now we remove the last element and reuse that node.
      auto oldestNode = nodes.end();
      oldestNode--;

      dict.erase(oldestNode->first);
      oldestNode->first = key;
      oldestNode->second = value;

      nodes.splice(nodes.begin(), nodes, oldestNode);
      dict.emplace(key, oldestNode);
    }
  }
};

int
main()
{
  LRUCache lRUCache(2);
  lRUCache.put(1, 1);                        // cache is {1=1}
  lRUCache.put(2, 2);                        // cache is {1=1, 2=2}
  std::cout << lRUCache.get(1) << std::endl; // return 1
  lRUCache.put(3, 3);                        // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  std::cout << lRUCache.get(2) << std::endl; // returns -1 (not found)
  lRUCache.put(4, 4);                        // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  std::cout << lRUCache.get(1) << std::endl; // return -1 (not found)
  std::cout << lRUCache.get(3) << std::endl; // return 3
  std::cout << lRUCache.get(4) << std::endl; // return 4
}
