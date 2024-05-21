#include <limits>

class Solution {
public:
    static int reverse(int x) {
        if (x == -std::numeric_limits<int>::max()-1) {
            return 0;
        }

        bool sign = x < 0;
        if (sign)
            x = -x;

        int out = 0;
        while (0 < x) {
            // std::cout << "x: " << x << " vs " << out << "\n";
            if (std::numeric_limits<int>::max()/10 < out)
                return 0;
            
            out *= 10;

            if (std::numeric_limits<int>::max()-x%10 < out)
                return 0;

            out += x%10;
            x /= 10;
        }

        return sign ? -out : out;
    }
};

int main() { return 0; }
