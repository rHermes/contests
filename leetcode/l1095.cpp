/**
 * // This is the MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *   public:
 *     int get(int index);
 *     int length();
 * };
 */
#include <unordered_map>
#include <vector>

class MountainArray
{
public:
  int get(int index) { return index; };
  int length() { return 42; };
};

class Cacher
{
  MountainArray& ma_;
  std::unordered_map<int, int> cache_;
  std::size_t hits_{ 0 };

public:
  Cacher(MountainArray& mm) : ma_{ mm } {}

  /* ~Cacher() { */
  /* 	const auto up = cache_.size(); */
  /* 	std::cout << "I was asked a total of: " << (up + hits_) << " where " << */
  /* 		hits_ << " was cache hits and " << up << " was cache misses." << std::endl; */
  /* } */

  [[nodiscard]] int get(const int i)
  {
    if (auto it = cache_.find(i); it != cache_.end()) {
      hits_++;
      return it->second;
    }

    const auto& [it, _] = cache_.emplace(i, ma_.get(i));
    return it->second;
  }
};

class Solution
{
public:
  int findInMountainArray(int target, MountainArray& mountainArr)
  {
    const int N = mountainArr.length();
    Cacher cache(mountainArr);

    /*
     * The idea for this is rather simple. We use a binary search to figure
     * out where the peak is. The maximum size of the list is 1000, which gives
     * us log2(10000) = ca 13. For each point we have 2 make two queries, so worst
     * case we spend 26 queries finding the peak.
     *
     * Then we do a regular binary search on each side of the mountain, starting
     * with the left side and returning as soon as we can. Each search is
     * log2(10000) in the worst case, and we might have to make two of them, so
     * we get: 2*log2(10000) = 26 queries for this also. This means that in the
     * worst case we are going to be asking about 54 questions.
     *
     * We would not be able to improve upon the worst case scenario here, but
     * we can improve the average case slightly, by introducing caching.
     *
     * The final optimization that I have yet to apply, is that if we find the
     * target while we are searching the array during the peak finding. We should
     * mark this and skip one of the two binary searches we perform afterwards.
     */

    int L = 0;
    int R = N - 2;

    while (L + 1 < R) {
      int C = (R + L) / 2;

      int cc = cache.get(C);
      int cr = cache.get(C + 1);

      if (cc < cr) {
        L = C;
      } else {
        R = C;
      }
    }

    // std::cout << "We found the center at: " << L << std::endl;
    const int top       = R;
    const int topHeight = cache.get(top);
    if (target == topHeight) {
      return top;
    } else if (topHeight < target) {
      return -1;
    }

    // We search on the left side.
    const int leftHeight = cache.get(0);
    if (leftHeight == target)
      return 0;

    if (leftHeight < target) {
      // We search.
      L = 0;
      R = top;
      while (L + 1 < R) {
        const int C = (R + L) / 2;
        int cc      = cache.get(C);

        if (cc == target) {
          return C;
        } else if (target < cc) {
          R = C;
        } else {
          L = C;
        }
      }

      if (cache.get(L) == target) {
        return L;
      }
    }

    // We search on the right side
    const int rightHeight = cache.get(N - 1);
    if (rightHeight == target) {
      return N - 1;
    }

    if (rightHeight < target) {
      L = top;
      R = N - 1;

      while (L + 1 < R) {
        const int C = (R + L) / 2;
        int cc      = cache.get(C);

        if (cc == target) {
          return C;
        } else if (cc < target) {
          R = C;
        } else {
          L = C;
        }
      }

      if (cache.get(R) == target) {
        return R;
      }
    }

    return -1;
  }
};

int
main()
{
  return 0;
};
