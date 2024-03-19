#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
	std::string_view canBeDone(const std::string_view s,
														const std::unordered_map<char, int>& needed,
														const std::size_t size) {
		auto wanted = needed;

		std::size_t head = 0;
		for (std::size_t i = 0; i < size; i++) {
			if (auto it = wanted.find(s[i]); it != wanted.end())
				it->second--;
		}

		auto done = std::all_of(wanted.cbegin(), wanted.cend(),
													[](const auto& a) { return a.second <= 0; });

		if (done) {
			return s.substr(head, size);
		}

		while (head < (s.size() - size)) {
			if (auto it = wanted.find(s[head]); it != wanted.end())
				it->second++;

			if (auto it = wanted.find(s[head + size]); it != wanted.end()) {
				head++;
				// ok, here we are.
				it->second--;
				if (0 != it->second) {
					continue;
				}

				auto done =
					std::all_of(wanted.cbegin(), wanted.cend(),
								 [](const auto& a) { return a.second <= 0; });

				if (done) {
					return s.substr(head, size);
				}

				continue;
			}

			head++;
		}

		return {};
	}

public:
	std::string minWindow(std::string s, std::string t) {
		std::unordered_map<char, int> needed;
		for (const auto c : t)
		needed[c]++;

		auto best = canBeDone(s, needed, s.size());
		if (best.empty()) {
			return "";
		}

		std::size_t L = 0;
		std::size_t R = s.size();

		while (L + 1 < R) {
			auto C = (L + R) / 2;
			auto top = canBeDone(s, needed, C);
			if (top.empty()) {
				L = C;
			} else {
				best = top;
				R = C;
			}
		}

		// Ok, so we know
		return std::string(best);
	}
};

int main() { return 0; }
