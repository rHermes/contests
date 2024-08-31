#include <deque>
#include <iostream>
#include <unordered_map>
#include <vector>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int minJumps(const std::vector<int>& arr)
  {
    // Let's build the graph.
    const int N = arr.size();
    std::unordered_map<int, std::vector<int>> GFS;

    for (int i = 1; i < N; i++) {
      // There is no need to add the middle parts of long runs, we
      // can just do the ends.
      if (0 < i && i < N - 1 && arr[i - 1] == arr[i] && arr[i] == arr[i + 1]) {
        continue;
      }
      GFS[arr[i]].emplace_back(i);
    }

    std::vector<unsigned char> seen(N, false);
    seen[0] = true;

    std::deque<int> Q;
    Q.push_back(0);

    int jumps = 0;
    while (!Q.empty()) {
      const int thisRound = Q.size();
      for (int i = 0; i < thisRound; i++) {
        const int cur = Q.front();
        Q.pop_front();

        if (cur == N - 1)
          return jumps;

        if (0 < cur && !seen[cur - 1]) {
          seen[cur - 1] = true;
          Q.push_back(cur - 1);
        }

        if (cur < N - 1 && !seen[cur + 1]) {
          seen[cur + 1] = true;
          Q.push_back(cur + 1);
        }

        if (auto jit = GFS.find(arr[cur]); jit != GFS.end()) {
          for (const auto next : jit->second) {
            if (!seen[next]) {
              seen[next] = true;
              Q.push_back(next);
            }
          }

          // We clear the jump list, to make sure we don't do more than one
          // jump.
          GFS.erase(jit);
        }
      }
      jumps++;
    }
    return -1;
  }
};
