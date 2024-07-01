#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class TweetCounts
{
  std::unordered_map<std::string, std::map<int, int>> m_data;

public:
  void recordTweet(const std::string& tweetName, int time) { m_data[tweetName][time]++; }

  std::vector<int> getTweetCountsPerFrequency(const std::string& freq,
                                              const std::string& tweetName,
                                              int startTime,
                                              int endTime)
  {
    const int mult = [&] {
      if (freq == "minute") {
        return 60;
      } else if (freq == "hour") {
        return 60 * 60;
      } else {
        return 60 * 60 * 24;
      }
    }();
    // const int buckets = (endTime - startTime + mult - 1) / mult;
    const int buckets = (endTime - startTime) / mult + 1;

    std::vector<int> out(buckets);
    auto it2 = m_data.find(tweetName);
    if (it2 == m_data.end()) {
      return out;
    }

    const auto& tm = it2->second;

    const auto itStart = tm.lower_bound(startTime);
    const auto itEnd = tm.upper_bound(endTime);

    for (auto it = itStart; it != itEnd; it++) {
      const auto bucket = (it->first - startTime) / mult;
      out[bucket] += it->second;
    }

    return out;
  }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 =
 * obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
