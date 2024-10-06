#include <algorithm>
#include <bitset>
#include <immintrin.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

/* #define VERBOSE 1 */

inline const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

std::string
reverseInt32(const std::uint32_t x)
{
  auto str = std::bitset<32>(x).to_string(' ', '1');
  std::ranges::reverse(str);
  return str;
}

class Solution
{
public:
  static bool areSentencesSimilar(const std::string& s1, const std::string& s2)
  {
    const int SN1 = s1.size();
    const int SN2 = s2.size();

    if (SN1 == SN2) {
      return s1 == s2;
    } else if (SN2 < SN1) {
      return areSentencesSimilar(s2, s1);
    }

    // ok, so since this is so small strings, we will cheat a bit here
    // and create a buffer with 128 bytes, since it's good.
		
		// We pad with 32 bits on each side, to make sure we can load it.
    alignas(32) std::array<char, 132> buf1;
    alignas(32) std::array<char, 132> buf2;
    std::ranges::fill(buf1, ' ');
    std::ranges::fill(buf2, ' ');

    std::ranges::copy(s1, buf1.begin());
    std::ranges::copy(s2, buf2.begin());

    // ok, now then, we have our aligned stuff.
    int leftPos = 0;

    // 256 bit vector approach
    const __m256i spaceVec = _mm256_set1_epi8(' ');
    for (int i = 0; i < 100; i += 32) {
#ifdef VERBOSE
      std::cout << "Entering loop with i=" << i << ", we are comparing:\n";
      std::cout << "b1: [" << std::setw(32) << std::string_view(buf1.data() + i, 32) << "]\n";
      std::cout << "b2: [" << std::setw(32) << std::string_view(buf2.data() + i, 32) << "]\n";
#endif

      const __m256i b1 = _mm256_stream_load_si256(reinterpret_cast<__m256i*>(buf1.data() + i));
      const __m256i b2 = _mm256_stream_load_si256(reinterpret_cast<__m256i*>(buf2.data() + i));

      const auto isEq = _mm256_cmpeq_epi8(b1, b2);
      const std::uint32_t whereEq = _mm256_movemask_epi8(isEq);


      // ok, now first of we are always looking for spaces.
      const auto isSpace = _mm256_cmpeq_epi8(b1, spaceVec);
      const std::uint32_t hasSpace = _mm256_movemask_epi8(isSpace);

#ifdef VERBOSE
      std::cout << "we: [" << reverseInt32(whereEq) << "]\n";
      std::cout << "se: [" << reverseInt32(hasSpace) << "]\n";
#endif

      if (whereEq == std::numeric_limits<std::uint32_t>::max()) {
        // Now we just need to know the left most space.
        const int spacePos = 31 - static_cast<int>(std::countl_zero(hasSpace));
        if (spacePos != -1) {
          leftPos = i + spacePos;
#ifdef VERBOSE
          std::cout << "We got a new space: " << (i + spacePos) << "\n";
#endif
        }

        continue;
      }

			const auto badSpot = std::countr_one(whereEq);

			const std::uint32_t goodMask = (static_cast<std::uint32_t>(1)<<badSpot)-1;
			const std::uint32_t modSpace = goodMask & hasSpace;

#ifdef VERBOSE
			std::cout << "there is a mismatch at: " << (i + badSpot) << "\n";
			std::cout << "gm: [" << reverseInt32(goodMask) << "]\n";
			std::cout << "ms: [" << reverseInt32(modSpace) << "]\n";
#endif

			const int spacePos = 31 - static_cast<int>(std::countl_zero(modSpace));
			if (spacePos != -1) {
				leftPos = i + spacePos;
#ifdef VERBOSE
				std::cout << "We got a new space: " << leftPos << "\n";
#endif
			}

			// ok, now then, how do I play this. We are going to first search all later
			// than that then.

			break;

      leftPos = i;
    }

		if (SN1 <= leftPos) {
			return true;
		}

		if (leftPos == 0 && buf2[SN2-SN1-1] != ' ')
			return false;


		for (int i = leftPos; i < SN1; i+= 32) {
			const int buf2Idx = SN2-SN1+i;
#ifdef VERBOSE
				std::cout << "Entering loop with i=" << i << ", we are comparing:\n";
				std::cout << "b1: [" << std::setw(32) << std::string_view(buf1.data() + i, 32) << "]\n";
				std::cout << "b2: [" << std::setw(32) << std::string_view(buf2.data() + buf2Idx, 32) << "]\n";
#endif
				
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
		{ "l QnKiZr mS eR AT", "l QnKiZr I ReEYVC qDATgJ hnY xyWP eQ FVYbiJmEIJ fcDITWEybj UADjg mS eR AT", true},
		{"UsD Sz AkHl PxthQ gz DDSoF J f ni QkC PZkuFiAAGONW Y Nekys H do WavjwwV Ci", "UsD Sz AkHl PxthQ gz DDSoF J f Nekys H do WavjwwV Ci", true},
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
