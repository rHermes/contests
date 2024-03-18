#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

/*
 * Please note that the current implementation is setup to handle a large amount
 * of elephants. If I knew some more about the bounds here, I would have gone for a more
 * cache friendly, but worse big O implementation.
 */
class ElephantCompetition {
private:
  struct Elephant {
    std::uint64_t height;
    std::uint64_t enter;
    std::uint64_t leave;
    std::string name;

    Elephant(std::string name, std::uint64_t enter, std::uint64_t leave, std::uint64_t height)
        : height{height}, enter{enter}, leave{leave}, name{std::move(name)} {}
  };
  // Name, enter, exit, sorted so the ones that enter first is in the back.
  // this way, we can do pop_back as elephants enter.
  std::vector<Elephant> waiting_;
  std::multiset<std::uint64_t> otherElephants_;

  // This is based on height.
  std::multimap<std::uint64_t, std::string> currentElephants_;
  // This is based on exit time.
  std::multimap<std::uint64_t, decltype(currentElephants_)::const_iterator> exitTimes_;

public:
  ElephantCompetition(
      const std::vector<std::pair<std::string, std::uint64_t>> &elephants,
      const std::vector<std::tuple<std::string, std::uint64_t, std::uint64_t>> &schedule) {

    // This is a potential optimization, maybe we could use just vectors and binary search to get
    // better locality here?
    std::unordered_map<std::string, std::uint64_t> heights;
    for (const auto &[name, height] : elephants)
      heights.emplace(name, height);

    for (const auto &[name, enter, leave] : schedule) {
      waiting_.emplace_back(name, enter, leave, heights[name]);
    }

    // we want to sort by both enter time and height
    std::sort(waiting_.begin(), waiting_.end(), [](const auto &a, const auto &b) {
      if (b.enter != a.enter) {
        return b.enter < a.enter;
      }

      return a.height < b.height;
    });
  }

  void elephantEntered(const std::uint64_t currentTime, const std::uint64_t height) {
    // We have to make sure it's not one of our own.

    // we have to search the waiting elephants, by the current time. There might be more
    // than one of them with the current time.

    // we are first going to search for it.
    // We want to erase the fewest number of items, so we are looking for the last value.
    // Since we are doing a custom comparison, we have to implement the binary search ourselves.
    if (waiting_.empty()) {
      otherElephants_.emplace(height);
      return;
    }

    // We have to use a custom comparator here, because we are running a custom search.
    std::size_t L = 0;
    std::size_t R = waiting_.size();
    while (L + 1 < R) {
      auto C = (L + R) / 2;
      const auto &elp = waiting_[C];

      auto lessThan =
          (elp.enter <= currentTime) || (elp.enter == currentTime && elp.height <= height);
      if (lessThan) {
        L = C;
      } else {
        R = C;
      }
    }

    // Now we just check if L has the
    const auto &el = waiting_[L];
    if (el.enter != currentTime || el.height != height) {
      otherElephants_.emplace(height);
      return;
    }

    auto elIt = currentElephants_.emplace(el.height, el.name);
    exitTimes_.emplace(el.leave, elIt);

    waiting_.erase(waiting_.begin() + static_cast<std::ptrdiff_t>(L));
  }

  void elephantLeft(const std::uint64_t currentTime, const std::uint64_t height) {
    auto [beg, end] = exitTimes_.equal_range(currentTime);
    while (beg != end) {
      if (beg->second->first == height) {
        currentElephants_.erase(beg->second);
        exitTimes_.erase(beg);
        return;
      }
      beg++;
    }
    otherElephants_.extract(height);
  }

  std::vector<std::string> getBiggestElephants(const std::uint64_t currentTime) {
    std::ignore = currentTime;

    // now it becomes rather easy to solve this problem.
    auto begin = otherElephants_.empty() ? currentElephants_.cbegin()
                                         : currentElephants_.lower_bound(*otherElephants_.rbegin());

    std::vector<std::string> answer;
    for (; begin != currentElephants_.end(); begin++) {
      answer.emplace_back(begin->second);
    }

    std::sort(answer.begin(), answer.end());

    return answer;
  }

  void printIt(const std::uint64_t currentTime) {
    const auto &answer = getBiggestElephants(currentTime);

    std::cout << answer.size();
    for (const auto &name : answer) {
      std::cout << " " << name;
    }

    std::cout << std::endl;
  }
};

int main() {
  std::vector<std::pair<std::string, std::uint64_t>> elephants{
      {"marry", 300},
      {"rob", 250},
  };
  std::vector<std::tuple<std::string, std::uint64_t, std::uint64_t>> schedule{
      {"marry", 10, 15},
      {"rob", 13, 20},
  };

  ElephantCompetition contest(elephants, schedule);

  contest.elephantEntered(8, 200);
  contest.elephantEntered(10, 310);
  contest.elephantEntered(10, 300);
  contest.printIt(11);
  contest.elephantEntered(13, 250);
  contest.elephantLeft(13, 310);
  contest.printIt(13);
  contest.elephantLeft(15, 300);
  contest.printIt(16);
  contest.elephantLeft(16, 200);
  contest.elephantLeft(20, 250);

  return 0;
};
