#include <iostream>
#include <set>
#include <string>
#include <string_view>
#include <vector>

class Solution
{
public:
  // The reason we use a sorted set, is that the merge performance is better.
  // An alternative here, for smaller sizes, would just be to use vectors for
  // everything and maintain the invariants at the start and end of the expansions
  // this could work, and given the layout of a vector, would probabily give us
  // a better cache locality. I've optimized for the common case here, where we
  // don't know the set sizes.
  using set_type = std::set<std::string>;

  void carts(set_type& dst, set_type& src)
  {
    if (src.empty())
      return;

    if (dst.empty()) {
      dst = std::move(src);
      return;
    }

    set_type cart;
    for (const auto& a : dst)
      for (const auto& b : src)
	cart.insert(a + b);

    dst = std::move(cart);
  }

  // This is devious, but
  set_type expand(std::string_view& current)
  {
    set_type accumulated;

    // We are going to be scanning this one element at a time.
    if (!current.starts_with('{'))
      throw std::runtime_error("We should always give a full capture for expansion");

    current.remove_prefix(1);

    // ok, so we keep iterating until we see our first '}'
    while (!current.starts_with('}')) {
      // ok, now we should always be at either
      set_type cum; // this is for this element.

      while (!current.starts_with(',') && !current.starts_with('}')) {
	// std::cout << "We are entering inner with: " << current <<
	// std::endl;
	//  ok, so we have procecced one element
	if (current.starts_with('{')) {
	  auto subexpand = expand(current);
	  carts(cum, subexpand);
	} else {
	  // ok, now we are going to keep scanning until we find a ','
	  auto end = current.find_first_of(",{}");
	  // We just iterate over and add to the queue.
	  set_type gotit;
	  gotit.emplace(current.substr(0, end));

	  carts(cum, gotit);

	  current.remove_prefix(end);
	}
      }

      // At the end of this element, we just merge the two.
      accumulated.merge(cum);

      if (current.starts_with(',')) {
	current.remove_prefix(1);
      }
    }

    // We pop the end square bracket
    current.remove_prefix(1);

    return accumulated;
  }

  std::vector<std::string> braceExpansionII(std::string expression)
  {
    // I can only expand full braces, so we wrap the expression in one,
    // to be sure we handle all cases.
    expression = '{' + expression + '}';
    std::string_view view(expression);
    // ok ok ok, here we go.
    const auto goods = expand(view);

    std::vector<std::string> ret(goods.begin(), goods.end());

    return ret;
  }
};

static const auto optimize = []() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  return 0;
}();

int
main()
{
  return 0;
}
