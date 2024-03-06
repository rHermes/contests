#include <string>
#include <iostream>
#include <vector>
#include <stack>

int longestValidParenthesesDP(std::string s) {
	// dp[i+1] == longest substring ending at s[i]
	std::vector<std::size_t> dp(s.size()+1);

	// we are storing in DP, the maximum size of the valid paranthasis ending at i
	int ans = 0;
	for (std::size_t i = 1; i < s.size(); i++) {
		if (s[i] == ')' && (dp[i] + 1 <= i) && s[i - dp[i] - 1] == '(')
					dp[i+1] = dp[i] + 2 + dp[i- dp[i] - 1];

		ans = std::max(ans, static_cast<int>(dp[i+1]));
	}

	return ans;
}

int longestValidParentheses(std::string s) {
	std::stack<int, std::vector<int>> stk;
	stk.push(-1); // Sentinel value??

	int ans = 0;
	for (std::size_t i = 0; i < s.size(); i++) {
		const auto ii = static_cast<int>(i);
		if (s[i] == '(') {
			stk.push(ii);
		} else {
			// if there is only one value left, it is the sentinel value, meaning the last
			// spot we saw a ')'
			if (stk.size() == 1) {
				stk.top() = ii;
			} else {
				// we remove the current brace, and we now know that everything until the
				// next value in line is valid. This is why we don't have the usual + 1 here,
				// because we don't count the brace we are executing against.
				stk.pop();
				ans = std::max(ans, ii - stk.top());
			}
		}
	}

	return ans;
}

int main() {
	std::cout << longestValidParentheses("") << std::endl;
	std::cout << longestValidParentheses("())") << std::endl;
	std::cout << longestValidParentheses("(()") << std::endl;
	std::cout << longestValidParentheses(")()())") << std::endl;
	std::cout << longestValidParentheses(")()())(()((") << std::endl;
	std::cout << longestValidParentheses(")()())") << std::endl;
	std::cout << longestValidParentheses("(()())") << std::endl;
	return 0;
}
