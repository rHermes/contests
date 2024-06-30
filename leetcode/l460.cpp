#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class LFUCache
{
  // We cluster on frequency, as this will prevent so many move operations
  struct Group
  {
    struct KV
    {
      int key;
      int value;
      std::list<Group>::iterator group;
    };
    std::size_t freq;
    std::list<KV> kvs;
  };

  std::size_t m_cap;
  std::list<Group> m_groups;
  std::unordered_map<int, std::list<Group::KV>::iterator> m_data;

  // Move an entry from one group to another.
  void move(std::list<Group::KV>::iterator kv, std::list<Group>::iterator group, std::size_t freq)
  {
    if (group == m_groups.end() || freq != group->freq) {
      // We know that this is either our size, or we must insert a new
      // group of that size.
      group = m_groups.emplace(group, freq);
    }

    // we insert the node at the beginning of the list
    group->kvs.splice(group->kvs.begin(), kv->group->kvs, kv);
    if (kv->group->kvs.empty())
      m_groups.erase(kv->group);

    kv->group = group;
  }

public:
  LFUCache(int capacity) : m_cap(capacity) {}

  int get(int key)
  {
    auto it = m_data.find(key);
    if (it == m_data.end())
      return -1;

    move(it->second, std::next(it->second->group), it->second->group->freq + 1);

    return it->second->value;
  }

  void put(int key, int value)
  {

    auto it = m_data.find(key);
    if (it != m_data.end()) {
      move(it->second, std::next(it->second->group), it->second->group->freq + 1);
      it->second->value = value;

      return;
    }

    auto group = m_groups.begin();
    if (m_cap == 0) {
      auto kv = std::prev(group->kvs.end());
      move(kv, group, 1);
      m_data.erase(std::exchange(kv->key, key));
      kv->value = value;
      m_data.emplace(key, kv);
      return;
    }

    m_cap--;
    if (group == m_groups.end() || group->freq != 1) {
      group = m_groups.emplace(group, 1);
    }

    auto it2 = group->kvs.emplace(group->kvs.begin(), key, value, group);
    m_data.emplace(key, it2);
  }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
