#include <vector>

class Solution {
public:
    static int kthFactor(int n, int k) {
        std::vector<bool> notAFactor(n + 1);
        for (int i = 1; i <= n; i++) {
            if (notAFactor[i])
                continue;

            if ((n % i) != 0) {
                notAFactor[i] = true;
                for (int ii = i + i; ii <= n; ii += i) {
                    notAFactor[ii] = true;
                }
            } else {
                k--;
                if (k == 0) {
                    return i;
                }
            }
        }

        return -1;
    }
};

int main() { return 0; }
