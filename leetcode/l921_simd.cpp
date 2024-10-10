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
  static int __attribute__((target("avx2"))) minAddToMakeValid(const std::string& s)
  {
    const int N = s.size();

    const auto ALL_ZERO = _mm256_setzero_si256();
    const auto ALL_ONE = _mm256_set1_epi8(0x01);
    const auto ALL_SET = _mm256_set1_epi8(-1);

    auto ans = _mm256_setzero_si256();
    auto balance = _mm256_setzero_si256();

    int i = 0;
    for (; i + 32 <= N; i += 32) {
      const auto chunk = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(s.data() + i));
      const auto leftBraces = _mm256_sub_epi8(chunk, _mm256_set1_epi8(')'));
      const auto rightBraces = _mm256_andnot_si256(leftBraces, ALL_SET);
      const auto valueChunk = _mm256_or_si256(rightBraces, ALL_ONE);

      auto psa = _mm256_add_epi8(valueChunk, _mm256_bslli_epi128(valueChunk, 1));
      psa = _mm256_add_epi8(psa, _mm256_bslli_epi128(psa, 2));
      psa = _mm256_add_epi8(psa, _mm256_bslli_epi128(psa, 4));
      psa = _mm256_add_epi8(psa, _mm256_bslli_epi128(psa, 8));

      auto min = _mm256_min_epi8(psa, _mm256_bslli_epi128(psa, 1));
      min = _mm256_min_epi8(min, _mm256_bslli_epi128(min, 2));
      min = _mm256_min_epi8(min, _mm256_bslli_epi128(min, 4));
      min = _mm256_min_epi8(min, _mm256_bslli_epi128(min, 8));

      // ok, let's swap min and psa.
      const auto flippedPSA = _mm256_permute2x128_si256(psa, psa, 0x01);
      const auto flippedMin = _mm256_permute2x128_si256(min, min, 0x01);

      // ok, now we add these together.
      const auto finalPsa = _mm256_add_epi8(flippedPSA, psa);
      const auto finalMin = _mm256_add_epi8(flippedMin, psa);

      // ok, so now we just have to compare.
      const auto totalMin = _mm256_min_epi8(min, finalMin);
      const auto negMin = _mm256_sub_epi8(ALL_ZERO, totalMin);

      // now then, we are going to revesre the totalMin, since we need that.
      // ok, so this is nice, we can actually get both of them like we want by shifting 15 to the right.
      const auto onlyPSA = _mm256_bsrli_epi128(finalPsa, 15);
      const auto onlyMin = _mm256_bsrli_epi128(negMin, 15);

      // Now then, we are going to convert this.
      const auto lowOnlyPSA = _mm256_castsi256_si128(onlyPSA);
      const auto lowOnlyMin = _mm256_castsi256_si128(onlyMin);

      // We need to use 32, because there there is no max_epi64
      const auto onlyPSA_32 = _mm256_cvtepi8_epi32(lowOnlyPSA);
      const auto onlyMin_32 = _mm256_cvtepi8_epi32(lowOnlyMin);

      const auto padding = _mm256_max_epi32(_mm256_sub_epi32(onlyMin_32, balance), ALL_ZERO);
      const auto tempAdd = _mm256_add_epi32(padding, onlyPSA_32);

      balance = _mm256_add_epi32(balance, tempAdd);
      ans = _mm256_add_epi32(ans, padding);
    }

    int scalarBalance = _mm256_cvtsi256_si32(balance);
    int scalarAns = _mm256_cvtsi256_si32(ans);

    for (; i < N; i++) {
      if (s[i] == '(') {
        scalarBalance++;
      } else {
        scalarBalance--;
        if (scalarBalance < 0) {
          scalarAns++;
          scalarBalance = 0;
        }
      }
    }

    return scalarAns + scalarBalance;
  }
};
