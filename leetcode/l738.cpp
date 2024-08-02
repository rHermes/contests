#include <vector>

class Solution
{
public:
  static constexpr int monotoneIncreasingDigits(const int n)
  {
    // interesting things happening here.
    // we want to follow them as long as we can, but if at some point we cannot
    std::vector<int> st;
    int cur = n;
    do {
      st.push_back(cur % 10);
      cur /= 10;
    } while (0 < cur);

    // ok, we go the digits now in st.
    const int N = st.size();

    // Now we will walk through it and it has to be an increasing

    int ans = st.back();
    int i = N - 2;
    while (0 <= i) {
      if (st[i + 1] <= st[i]) {
        ans *= 10;
        ans += st[i];
        i--;
        continue;
      }

      // ok, so we cannot do this. Now then the game is:
      // we have to find the first spot where we can go one down.
      while (i < N - 1) {
        // so far it's been a smash hit, so we know that st is in monotonic increasing from.
        if (st[i] - 1 < st[i + 1]) {
          // this didn't work.
          ans /= 10;
          i++;
          continue;
        }

        break;
      }

      // ok i is now at the spot where we will se to
      ans *= 10;
      ans += st[i] - 1;
      i--;
      while (0 <= i) {
        ans *= 10;
        ans += 9;
        i--;
      }
      break;
    }

    return ans;
  }
};
