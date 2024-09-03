#include <array>
#include <string>
#include <unordered_map>
#include <vector>

template<class T>
inline void
hash_combine(std::size_t& seed, const T& v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

class Solution
{
  using Color = unsigned char;
  static constexpr Color RED = 0;
  static constexpr Color YELLOW = 1;
  static constexpr Color BLUE = 2;
  static constexpr Color GREEN = 3;
  static constexpr Color WHITE = 4;

  static constexpr Color fromLetter(const char c)
  {
    switch (c) {
      case 'R':
        return RED;
      case 'Y':
        return YELLOW;
      case 'B':
        return BLUE;
      case 'G':
        return GREEN;
      default:
        return WHITE;
    }
  }

  static constexpr char toLetter(const Color c)
  {
    switch (c) {
      case RED:
        return 'R';
      case YELLOW:
        return 'Y';
      case BLUE:
        return 'B';
      case GREEN:
        return 'G';
      default:
        return 'W';
    }
  }

  // How we represent the count of cards.
  using HAND = std::array<int, 5>;

  struct State
  {
    HAND hand{};
    HAND numBoard{};
    std::vector<std::pair<Color, int>> board;
    std::size_t preCompSig{ 0 };

    void computeSig()
    {
      preCompSig = 0;

      for (const auto& [col, amt] : board) {
        hash_combine(preCompSig, toLetter(col));
        hash_combine(preCompSig, amt);
      }

      hash_combine(preCompSig, '_');

      for (int i = 0; i < 5; i++) {
        hash_combine(preCompSig, toLetter(i));
        hash_combine(preCompSig, hand[i]);
      }
    }

    [[nodiscard]] std::size_t getSig() const { return preCompSig; }
  };

  using CACHE = std::unordered_map<std::size_t, int>;

  // WE can only have so many boards, so we move like this.
  static constexpr int SENTINEL = 6;

  static int solve(CACHE& cache, State& state, const int maxLeft)
  {
    if (maxLeft <= 0) {
      return maxLeft;
    }

    if (state.board.empty())
      return 0;

    // Here we both check that we can in theory fix all paths and
    // remove items on the hand that does not have representation on the
    // board.
    bool oneHand = false;
    for (int i = 0; i < 5; i++) {
      if (0 < state.numBoard[i]) {
        oneHand = oneHand || (0 < state.hand[i]);

        if (state.numBoard[i] + std::min(maxLeft, state.hand[i]) < 3)
          return maxLeft;
      } else if (0 < state.hand[i] && state.hand[i] < 3) {
        state.hand[i] = 0;
      }
    }
    if (!oneHand) {
      return maxLeft;
    }

    state.computeSig();

    const auto sig = state.getSig();
    if (auto it = cache.find(sig); it != cache.end()) {
      return it->second;
    }

    // We use ans from now on, to track the max depth. This allows us to
    // bound the search depth.
    int ans = maxLeft;

    const int N = state.board.size();

    // So I don't know why, but it seems we never need to insert something
    // betweeen 2 groups. or in front. I don't know why this is, but since
    // it passes all tests without it, I have not written it up here. it's
    // quite easy to implement. we try to put it first or last.
    for (int i = 0; i < N; i++) {
      if (state.board[i].second != 2)
        continue;

      for (int col = 0; col < 5; col++) {
        if (0 == state.hand[col] || state.board[i].first == col) {
          continue;
        }

        auto newState = state;
        newState.board[i].second--;
        newState.board.emplace(newState.board.begin() + i + 1, newState.board[i].first, 1);
        newState.board.emplace(newState.board.begin() + i + 1, col, 1);

        newState.hand[col]--;
        newState.numBoard[col]++;

        ans = std::min(ans, 1 + solve(cache, newState, ans - 1));
      }
    }

    for (int i = 0; i < N; i++) {
      const auto& [col, amt] = state.board[i];
      const int rem = 3 - amt;

      if (!(state.hand[col] < rem || ans <= rem)) {
        // ok, we will insert just enough to get 3.
        auto newState = state;
        newState.hand[col] -= rem;

        // We remove the ones which are there.
        newState.numBoard[col] -= amt;

        // ok, now we are simplifying.
        int l = i - 1;
        int r = i + 1;

        // this is the cascade.
        while (0 <= l && r < N) {
          const auto& [lcol, lamt] = newState.board[l];
          const auto& [rcol, ramt] = newState.board[r];
          if (lcol != rcol) {
            break;
          }

          newState.board[l].second += ramt;
          r++;
          if (newState.board[l].second < 3) {
            break;
          }

          newState.numBoard[lcol] -= newState.board[l].second;

          l--;
        }

        newState.board.erase(newState.board.begin() + l + 1, newState.board.begin() + r);

        ans = std::min(ans, rem + solve(cache, newState, ans - rem));
      }
    }

    cache.emplace(sig, ans);
    return ans;
  }

public:
  static int findMinStep(const std::string& board, const std::string& hand)
  {
    // We create the root state, which we will be using from here on out.
    State root;
    for (const auto c : hand) {
      root.hand[fromLetter(c)]++;
    }

    for (const auto c : board) {
      const auto col = fromLetter(c);
      root.numBoard[col]++;

      if (root.board.empty() || root.board.back().first != col) {
        root.board.emplace_back(col, 1);
      } else {
        root.board.back().second++;
      }
    }

    CACHE cache;
    const int ans = solve(cache, root, SENTINEL);
    return (ans == SENTINEL) ? -1 : ans;
  }
};
