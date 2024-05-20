#include <stack>
#include <vector>

class Solution
{
private:
  int maxHist(const std::vector<int>& height, std::stack<unsigned, std::vector<unsigned>>& st)
  {
    const auto cols = static_cast<unsigned>(height.size());
    const unsigned sentinel = static_cast<unsigned>(-1);
    st.push(sentinel);

    unsigned ans = 0;

    // The idea here, is that we are going to keeping a stack, with the
    // index of the currently longest strictly increasing subseqence.
    // each time we remove an element, we know that we can create a rectangle
    // with all the spots that are between it and the next smaller element.
    // This is because each element that comes in acts like a choke, eliminating
    // larger elements behind it, with 0 being the restart value.
    for (unsigned i = 0; i < cols; i++) {
      while ((st.top() != sentinel) && (height[i] <= height[st.top()])) {
        const auto curH = height[st.top()];
        st.pop();

        // Because we always push i-1 on the top of the stack at the
        // end of each round, we know that when we enter here, i-1 is
        // taller than all other elements that are currently in the stack.
        // This means that when we are building a rectangle, we are going
        // from the previous instant in the stacks position to i-1 with it's
        // value, since the first element before it that is smaller than it,
        // is the next value in the stack.
        //
        // This means we record the height at the top of the stack. Then we
        // pop of the top. The top of the stack is now the position of the first
        // element smaller than the current height. normally you have dst - src + 1,
        // but that is only if we include both sides. We are not including the src,
        // as it's smaller than the current height, so it only becomes dst - src,
        // which in our case is (i-1) - st.top()
        ans = std::max(ans, static_cast<unsigned>(curH) * (i - st.top() - 1));
      }

      st.push(i);
    }

    // Now that we are done, we know that all elemnts in the stack, are smaller than
    // what we have at (cols-1). We do the same song and dance as we did before.
    while (st.top() != sentinel) {
      const auto curH = height[st.top()];
      st.pop();
      ans = std::max(ans, static_cast<unsigned>(curH) * (cols - 1 - st.top()));
    }

    // Remove -1, since we are entering and exciting this.
    st.pop();

    return static_cast<int>(ans);
  }

public:
  int maximalRectangle(std::vector<std::vector<char>>& matrix)
  {
    const auto rows = matrix.size();
    const auto cols = matrix[0].size();

    std::vector<int> height(cols);
    std::vector<unsigned> stackArr;
    stackArr.reserve(cols + 1);
    std::stack st(std::move(stackArr));

    int ans = 0;
    // We look at the first
    for (std::size_t row = 0; row < rows; row++) {
      // first we update the height.
      for (std::size_t i = 0; i < cols; i++) {
        if (matrix[row][i] == '1') {
          height[i]++;
        } else {
          height[i] = 0;
        }
      }

      ans = std::max(ans, maxHist(height, st));
    }
    return ans;
  }
};
int
main()
{
}
