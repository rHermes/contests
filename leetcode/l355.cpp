#include <algorithm>
#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Twitter
{
  std::unordered_map<int, std::unordered_set<int>> m_follow;
  std::unordered_map<int, std::deque<std::pair<int, int>>> m_tweets;

  int m_gen{ 1 };

public:
  void postTweet(int userId, int tweetId)
  {
    auto& tweets = m_tweets[userId];
    tweets.emplace_front(m_gen++, tweetId);
    if (10 < tweets.size())
      tweets.pop_back();
  }

  std::vector<int> getNewsFeed(int userId)
  {
    std::vector<std::pair<int, int>> out(m_tweets[userId].begin(), m_tweets[userId].end());
    std::ranges::make_heap(out, std::ranges::greater{});

    for (const auto uid : m_follow[userId]) {
      for (const auto& pp : m_tweets[uid]) {
        if (out.size() != 10) {
          out.emplace_back(pp);
          std::ranges::push_heap(out, std::ranges::greater{});
        } else {
          if (pp.first <= out[0].first)
            break;

          std::ranges::pop_heap(out, std::ranges::greater{});
          out.back() = pp;
          std::ranges::push_heap(out, std::ranges::greater{});
        }
      }
    }

    std::ranges::sort_heap(out, std::ranges::greater{});

    std::vector<int> ans(out.size());
    for (std::size_t i = 0; i < out.size(); i++) {
      ans[i] = out[i].second;
    }
    return ans;
  }

  void follow(int followerId, int followeeId) { m_follow[followerId].emplace(followeeId); }

  void unfollow(int followerId, int followeeId) { m_follow[followerId].erase(followeeId); }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

int
main()
{
  return 0;
}
