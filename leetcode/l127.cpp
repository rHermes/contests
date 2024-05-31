#include <deque>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  static int ladderLength(const std::string& beginWord,
                          const std::string& endWord,
                          const std::vector<std::string>& wordList)
  {

    const int TN = beginWord.size();

    const std::unordered_set<std::string_view> canMatch(wordList.begin(), wordList.end());
    if (!canMatch.contains(endWord)) {
      return 0;
    }

    std::string tmp;
    using AT = std::unordered_map<std::string_view, int>;

    const auto expandList = [&](AT& forwardSteps, const AT& reverseSteps, std::deque<std::string_view>& Q) {
      const int thisRound = Q.size();
      for (int z = 0; z < thisRound; z++) {
        auto cur = Q[z];
        tmp = cur;

        int steps = forwardSteps[cur];

        for (int i = 0; i < TN; i++) {
          const auto prev = tmp[i];
          for (char k = 'a'; k <= 'z'; k++) {
            tmp[i] = k;
            auto it1 = canMatch.find(tmp);
            if (it1 == canMatch.end())
              continue;

            auto [it2, ins] = forwardSteps.emplace(*it1, steps + 1);
            if (!ins)
              continue;

            if (auto it3 = reverseSteps.find(it2->first); it3 != reverseSteps.end()) {
              return it3->second + it2->second - 1;
            }

            Q.emplace_back(it2->first);
          }
          tmp[i] = prev;
        }
      }
      Q.erase(Q.begin(), Q.begin() + thisRound);
      return -1;
    };

    AT forwardMap{ { beginWord, 1 } };
    AT backwardMap{ { endWord, 1 } };

    std::deque<std::string_view> forwardQ{ { beginWord } };
    std::deque<std::string_view> reverseQ{ { endWord } };

    while (!forwardQ.empty() && !reverseQ.empty()) {
      int ans = -1;
      if (forwardQ.size() <= reverseQ.size()) {
        ans = expandList(forwardMap, backwardMap, forwardQ);
      } else {
        ans = expandList(backwardMap, forwardMap, reverseQ);
      }
      if (ans != -1)
        return ans;
    }
    return 0;
  }
};

int
main()
{
  return 0;
}
