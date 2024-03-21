class Solution {
public:
    bool canWinNim(int n) {
        // The idea here is just from what position can we not win?
        // we are always trying to move our oppounent to such a move.
        // the first place it's possible to lose is n=4. If we start
        // and we get n=5, n=6 or n=7, we can force our opponent to
        // start with p=4 and they will lose. At p=8 our opponent
        // can force us onto p=4, so we lose. This pattern is clear
        // and it means that unless we start on a number divisible
        // by 4, we are going to win.
        return n % 4 != 0;
    }
}; 

int main() { return 0; }
