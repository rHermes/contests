#include <deque>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
  using PARENT = std::vector<std::vector<int>>;

  static void reconstructPath(const std::vector<std::string>& wordList,
                              const PARENT& parents,
                              std::vector<std::vector<std::string>>& out,
                              const bool reverse,
                              std::vector<std::string>& tmp,
                              const int curIdx)
  {
    tmp.emplace_back(wordList[curIdx]);

    if (parents[curIdx].empty()) {
      if (reverse) {
        out.emplace_back(tmp.rbegin(), tmp.rend());
      } else {
        out.push_back(tmp);
      }

      tmp.pop_back();
      return;
    }

    for (const auto& nextInt : parents[curIdx]) {
      reconstructPath(wordList, parents, out, reverse, tmp, nextInt);
    }
    tmp.pop_back();
  }

public:
  static std::vector<std::vector<std::string>> findLadders(const std::string& beginWord,
                                                           const std::string& endWord,
                                                           const std::vector<std::string>& wordList)
  {
    const int N = wordList.size();
    const int SN = beginWord.size();

    const auto hasEdge = [&](const std::string& a, const std::string& b) {
      int diffs = 0;
      for (int i = 0; i < SN; i++) {
        diffs += (a[i] != b[i]);
      }

      return diffs == 1;
    };

    constexpr int SENTINEL = std::numeric_limits<int>::max();
    std::vector<int> srcSeen(N, SENTINEL);
    std::vector<int> dstSeen(N, SENTINEL);

    std::deque<int> dstQ;

    for (int i = 0; i < N; i++) {
      if (endWord == wordList[i]) {
        dstQ.emplace_back(i);
        dstSeen[i] = 0;
        break;
      }
    }

    if (dstQ.empty())
      return {};

    std::deque<int> srcQ;
    for (int i = 0; i < N; i++) {
      if (beginWord == wordList[i]) {
        // We skip this in case it exists.
        srcSeen[i] = 0;
      } else if (hasEdge(beginWord, wordList[i])) {
        srcQ.emplace_back(i);
        srcSeen[i] = 1;
      }
    }
    if (srcQ.empty()) {
      return {};
    }

    // If there is a srcSeen we should mark it as zero.
    for (int i = 0; i < N; i++) {
      if (beginWord == wordList[i]) {
        break;
      }
    }

    std::vector<std::vector<std::string>> out;

    if (srcSeen[dstQ.front()] != SENTINEL) {
      // In this case there is only one answer.
      out.push_back({ beginWord, endWord });
      return out;
    }

    PARENT srcParents(N);
    PARENT dstParents(N);

    auto BFS = [&](std::deque<int>& Q,
                   std::vector<int>& seen,
                   const std::vector<int>& otherSeen,
                   PARENT& parents,
                   std::vector<int>& hits) {
      const int NN = Q.size();
      for (int zzz = 0; zzz < NN; zzz++) {
        const auto cur = Q.front();
        Q.pop_front();

        const auto curDist = seen[cur] + 1;
        for (int i = 0; i < N; i++) {
          if (seen[i] < curDist)
            continue;

          if (hasEdge(wordList[cur], wordList[i])) {
            if (curDist < seen[i])
              Q.emplace_back(i);

            if ((seen[i] == SENTINEL) && (otherSeen[i] != SENTINEL)) {
              hits.push_back(i);
            }

            seen[i] = curDist;
            parents[i].emplace_back(cur);
          }
        }
      }
    };

    std::vector<int> hits;
    while (!dstQ.empty() && !srcQ.empty()) {
      BFS(srcQ, srcSeen, dstSeen, srcParents, hits);
      if (hits.empty())
        BFS(dstQ, dstSeen, srcSeen, dstParents, hits);

      if (hits.empty())
        continue;

      for (const auto& midPoint : hits) {
        std::vector<std::vector<std::string>> leftSide;
        std::vector<std::vector<std::string>> rightSide;

        std::vector<std::string> tmp;
        reconstructPath(wordList, srcParents, leftSide, true, tmp, midPoint);
        reconstructPath(wordList, dstParents, rightSide, false, tmp, midPoint);

        for (const auto& left : leftSide) {
          for (const auto& right : rightSide) {
            out.push_back({ beginWord });
            out.back().insert(out.back().end(), left.begin(), left.end());
            out.back().insert(out.back().end(), right.begin() + 1, right.end());
          }
        }
      }

      // ok, now let's see if we have any overlap.
      break;
    }

    return out;
  }
};
