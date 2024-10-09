#include <immintrin.h>
#include <iostream>
#include <string>

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

class Solution
{
public:
  static int __attribute__((target("sse4.2"))) minAddToMakeValid(const std::string& s)
  {
    const int N = s.size();

    int ans = 0;
    int balance = 0;

    const auto ALL_ONE = _mm_set1_epi8(0x01);
    const auto ALL_SET = _mm_set1_epi8(0xFF);

    int i = 0;
    for (; i + 16 <= N; i += 16) {
      const auto chunk = _mm_loadu_si128(reinterpret_cast<__m128i const*>(s.data() + i));
      const auto leftBraces = _mm_sub_epi8(chunk, _mm_set1_epi8(')'));
      const auto rightBraces = _mm_andnot_si128(leftBraces, ALL_SET);
      const auto valueChunk = _mm_or_si128(rightBraces, ALL_ONE);

      auto psa = _mm_add_epi8(valueChunk, _mm_bslli_si128(valueChunk, 1));
      psa = _mm_add_epi8(psa, _mm_bslli_si128(psa, 2));
      psa = _mm_add_epi8(psa, _mm_bslli_si128(psa, 4));
      psa = _mm_add_epi8(psa, _mm_bslli_si128(psa, 8));

      // Now if I have more than 16 in balance,  I can skip the next bit,
      // but I don't, since it's better to just pipeline everything.
      auto min = _mm_min_epi8(psa, _mm_bslli_si128(psa, 1));
      min = _mm_min_epi8(min, _mm_bslli_si128(min, 2));
      min = _mm_min_epi8(min, _mm_bslli_si128(min, 4));
      min = _mm_min_epi8(min, _mm_bslli_si128(min, 8));

      const std::int8_t finPsa = static_cast<std::int8_t>(_mm_extract_epi8(psa, 15));
      const std::int8_t minVal = -static_cast<std::int8_t>(_mm_extract_epi8(min, 15));

      const int padding = std::max(0, minVal - balance);
      balance += finPsa + padding;
      ans += padding;
    }

    for (; i < N; i++) {
      if (s[i] == '(') {
        balance++;
      } else {
        balance--;
        if (balance < 0) {
          ans++;
          balance = 0;
        }
      }
    }

    return ans + balance;
  }
};
