#include <algorithm>
#include <immintrin.h>
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

  static bool __attribute__((target("avx,avx2"))) areSimilar1(const char* __restrict__ s1,
                                                              const int SN1,
                                                              const char* __restrict__ s2,
                                                              const int SN2)

  {
    // ok, so since this is so small strings, we will cheat a bit here
    // and create a buffer with 128 bytes, which frees us from doing much else

    // We pad with 32 bits on each side, to make sure we can load it, int the last iteration.
    alignas(32) std::array<char, 133> buf1;
    alignas(32) std::array<char, 133> buf2;
    // We want to fill these with ' ', so that edge detection is easier.
    std::ranges::fill(buf1, ' ');
    std::ranges::fill(buf2, ' ');

    std::ranges::copy_n(s1, SN1, buf1.begin());
    std::ranges::copy_n(s2, SN2, buf2.begin());

    // This stores the last valid space we saw
    int leftPos = 0;

    // 256 bit vector approach
    const __m256i spaceVec = _mm256_set1_epi8(' ');
    for (int i = 0; i < 100; i += 32) {
      const __m256i b1 = _mm256_stream_load_si256(reinterpret_cast<__m256i*>(buf1.data() + i));
      const __m256i b2 = _mm256_stream_load_si256(reinterpret_cast<__m256i*>(buf2.data() + i));

      const auto isEq = _mm256_cmpeq_epi8(b1, b2);
      const std::uint32_t whereEq = _mm256_movemask_epi8(isEq);

      // ok, now first of we are always looking for spaces.
      const auto isSpace = _mm256_cmpeq_epi8(b1, spaceVec);
      const std::uint32_t hasSpace = _mm256_movemask_epi8(isSpace);

      if (whereEq == std::numeric_limits<std::uint32_t>::max()) {
        // Now we just need to know the left most space.
        const int spacePos = 31 - static_cast<int>(std::countl_zero(hasSpace));
        if (spacePos != -1) {
          leftPos = i + spacePos;
        }

        continue;
      }

      const auto badSpot = std::countr_one(whereEq);

      const std::uint32_t goodMask = (static_cast<std::uint32_t>(1) << badSpot) - 1;
      const std::uint32_t modSpace = goodMask & hasSpace;

      const int spacePos = 31 - static_cast<int>(std::countl_zero(modSpace));
      if (spacePos != -1) {
        leftPos = i + spacePos;
      }

      // ok, now then, how do I play this. We are going to first search all later than that then.

      break;
    }

    if (SN1 <= leftPos) {
      return true;
    }

    if (leftPos == 0 && buf2[SN2 - SN1 - 1] != ' ')
      return false;

    for (int i = leftPos; i < SN1; i += 32) {
      const int buf2Idx = SN2 - SN1 + i;

      // We can no longer use streaming, because we are not assured of being
      __m256i b1 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(buf1.data() + i));
      __m256i b2 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(buf2.data() + buf2Idx));

      const auto isEq = _mm256_cmpeq_epi8(b1, b2);
      const std::uint32_t whereEq = _mm256_movemask_epi8(isEq);

      if (whereEq != std::numeric_limits<std::uint32_t>::max())
        return false;
    }

    return true;
  }

  // SN1 must be smaller than SN2
  // Version which does not allocate extra memory, and does not rely on max length of the strings.
  static bool __attribute__((target("avx,avx2"))) areSimilar2(const char* __restrict__ s1,
                                                              const int SN1,
                                                              const char* __restrict__ s2,
                                                              const int SN2)

  {
    // 256 bit vector approach
    const __m256i spaceVec = _mm256_set1_epi8(' ');
    constexpr std::uint32_t ALL_ONES = std::numeric_limits<std::uint32_t>::max();

    int leftPos = 0;

    // ok, so since this is so small strings, we will cheat a bit here
    // and create a buffer with 128 bytes, which frees us from doing much else
    bool allMatched = true;
    int i;
    for (i = 0; i < SN1 - 32; i += 32) {
      const __m256i b1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(s1 + i));
      const __m256i b2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(s2 + i));

      const std::uint32_t whereEq = _mm256_movemask_epi8(_mm256_cmpeq_epi8(b1, b2));
      const std::uint32_t whereSpace = _mm256_movemask_epi8(_mm256_cmpeq_epi8(b1, spaceVec));

      if (whereEq == ALL_ONES) {
        const int spacePos = 31 - static_cast<int>(std::countl_zero(whereSpace));
        if (spacePos != -1) {
          leftPos = i + spacePos;
        }
        continue;
      }

      allMatched = false;

      const auto badSpot = std::countr_one(whereEq);

      const std::uint32_t goodMask = (static_cast<std::uint32_t>(1) << badSpot) - 1;
      const std::uint32_t modSpace = goodMask & whereSpace;

      const int spacePos = 31 - static_cast<int>(std::countl_zero(modSpace));
      if (spacePos != -1) {
        leftPos = i + spacePos;
      }
      break;
    }

    // let's do the comparision
    if (allMatched) {
      for (; i < SN1; i++) {
        if (s1[i] != s2[i]) {
          allMatched = false;
          break;
        }
        if (s1[i] == ' ') {
          leftPos = i;
        }
      }
    }

    if (allMatched && (s2[SN1] == ' '))
      return true;

    // We can do a quick check to see if
    if (leftPos == 0 && s2[SN2 - SN1 - 1] != ' ')
      return false;

    int j = leftPos;
    for (; j < SN1 - 32; j += 32) {
      const __m256i b1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(s1 + j));
      const __m256i b2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(s2 + SN2 - SN1 + j));

      const std::uint32_t whereEq = _mm256_movemask_epi8(_mm256_cmpeq_epi8(b1, b2));
      if (whereEq != ALL_ONES)
        return false;
    }

    for (; j < SN1; j++) {
      if (s1[j] != s2[SN2 - SN1 + j])
        return false;
    }

    return true;
  }

public:
  static bool __attribute__((target("avx,avx2"))) areSentencesSimilar(const std::string& s1, const std::string& s2)
  {
    const int SN1 = s1.size();
    const int SN2 = s2.size();

    if (SN1 == SN2) {
      return s1 == s2;
    } else if (SN2 < SN1) {
      return areSimilar2(s2.data(), SN2, s1.data(), SN1);
    } else {
      return areSimilar2(s1.data(), SN1, s2.data(), SN2);
    }
  }
};

int
main()
{
  std::vector<std::tuple<std::string, std::string, bool>> tests = {
    { "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww",
      "kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww we",
      true },
    { "aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt",
      "aa bb cc dd ee ff gg hh ii jj kk ll mm nn oo pp qq rr ss tt ww zz",
      true },
    { "Eating", "Eating right now", true },
    { "My name is Haley", "My Haley", true },
    { "of", "A lot of words", false },
    { "DN PD", "D", false },
    { "xD iP tqchblXgqvNVdi", "FmtdCzv Gp YZf UYJ xD iP tqchblXgqvNVdi", true },
    { "l QnKiZr mS eR AT", "l QnKiZr I ReEYVC qDATgJ hnY xyWP eQ FVYbiJmEIJ fcDITWEybj UADjg mS eR AT", true },
    { "UsD Sz AkHl PxthQ gz DDSoF J f ni QkC PZkuFiAAGONW Y Nekys H do WavjwwV Ci",
      "UsD Sz AkHl PxthQ gz DDSoF J f Nekys H do WavjwwV Ci",
      true },
  };

  for (const auto& [a, b, should] : tests) {
    /* std::cout << "\n"; */
    const auto comp = Solution::areSentencesSimilar(a, b);
    if (comp != should) {
      std::cout << "We should have gotten: " << should << ", but we got: " << comp << " for:\n";
      std::cout << "[" << a << "]\n";
      std::cout << "[" << b << "]\n";
      break;
    }
  }

  return 0;
}
