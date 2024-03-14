#include <vector>
#include <algorithm>
#include <cinttypes>

using UT = std::uint64_t;

class Solution {
public:
    int maxBuilding(int n, std::vector<std::vector<int>>& restrictions) {
        // with empty, it's easy.
        if (restrictions.empty())
            return n-1;
        
        std::vector<std::pair<int,int>> res;
        res.emplace_back(1, 0);
        
        for (const auto& r : restrictions)
            res.emplace_back(r[0], r[1]);
        
        std::sort(res.begin(), res.end());
			
				// We solve this in 2 passes. The idea is that we first 
				for (std::size_t i = res.size()-1; 0 < i;) {
					i--;

					// ok, we are now adjusting.
					auto& cur = res[i];
					auto& next = res[i+1];
					const auto dist = next.first - cur.first;

					auto leftmin = std::min(cur.second, next.second+dist);
					auto rightmin = std::min(next.second, leftmin+dist);

					cur.second = leftmin;
					next.second = rightmin;
				}
	

				// On this second run, we are going to go forward through the
				// array. We are going to calculate the answer as we go, since
				// there is no need to loop over the array again.
        int ans = 0;
        int curH = 0;
        int curPos = 1;

				for (std::size_t i = 0; i < res.size()-1; i++) {
					// ok, we are going forward through the array once.
					/* auto& cur = res[i]; */
					auto& next = res[i+1];
					const auto dist = next.first - curPos;

					/* auto leftmin = std::min(cur.second, next.second+dist); */
					auto rightmin = std::min(next.second, curH+dist);

					ans = std::max(ans, curH + (rightmin-curH+dist)/2);
					curPos = next.first;
					curH = rightmin;
				}


				// Only thing left, is to see if we can make the best move going forward to the end.
        ans = std::max(ans, curH + n-curPos);
        return ans;
    }
};

int main() {}
