#include <array>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <string_view>

enum class ParseResult {
  InvalidFormat = 1,
  DuplicatePair = 2,
  NotBinary = 3,
  MultipleRoots = 4,
  Cycle = 5,
  Good = 6,
};

inline std::ostream &operator<<(std::ostream &os, const ParseResult res) {
  switch (res) {
  case ParseResult::Good:
    os << "OK";
    break;
  case ParseResult::InvalidFormat:
    os << "E1";
    break;
  case ParseResult::DuplicatePair:
    os << "E2";
    break;
  case ParseResult::NotBinary:
    os << "E3";
    break;
  case ParseResult::MultipleRoots:
    os << "E4";
    break;
  case ParseResult::Cycle:
    os << "E5";
    break;
  }

  return os;
}

[[nodiscard]] constexpr ParseResult parseLine(std::string_view in) {
  if (!in.starts_with('(') || !in.ends_with(')'))
    return ParseResult::InvalidFormat;

  // we can actually do something cool here for a possibility of
  // an early return. We know that each pair is 5 characters long,
  // so we can check if the length of the string aligns with this.
  // This will also give us the number of nodes. This doesn't guarantee
  // That the answer is correct, but it's an easy way to escape.
  const auto sz = in.size();
  const auto numPairs = (sz + 1) / 6;
  const auto leftOver = (sz + 1) % 6;
  if (leftOver != 0) {
    return ParseResult::InvalidFormat;
  }

  std::bitset<26> seen;
  std::bitset<26> hasParent;
  std::bitset<26 * 26> edges;
  std::array<std::uint8_t, 26> numChildren{};

  ParseResult answer = ParseResult::Good;
  for (std::size_t i = 0; i < numPairs; i++) {
    // Each node notation is exactly 5 characters long.
    if (in[0] != '(' || in[2] != ',' || in[4] != ')' || in[1] < 'A' || 'Z' < in[1] || in[3] < 'A' ||
        'Z' < in[3])
      return ParseResult::InvalidFormat;

    const std::uint8_t parent = static_cast<std::uint8_t>(in[1] - 'A');
    const std::uint8_t child = static_cast<std::uint8_t>(in[3] - 'A');

    seen[parent] = true;
    seen[child] = true;

    // ok, so we have a couple of checks to do here.
    // first of all, have we seen this pair before?
    if (edges[parent * 26 + child])
      answer = std::min(answer, ParseResult::DuplicatePair);

    edges[parent * 26 + child] = true;

    // ok, so let's see if the parent has more than two children?
    numChildren[parent]++;
    if (2 < numChildren[parent]) {
      answer = std::min(answer, ParseResult::NotBinary);
    }

    // if a node has more than 1 parent, there must be at least a cycle.
    if (hasParent[child])
      answer = std::min(answer, ParseResult::Cycle);
    hasParent[child] = true;

    if (i < numPairs - 1) {
      if (in[5] != ' ')
        return ParseResult::InvalidFormat;

      in.remove_prefix(6);
    } else {
      in.remove_prefix(5);
    }
  }

  // ok, if we have an error, we will do a scan through the arrays for
  if (ParseResult::NotBinary < answer) {
    // We want to know how many roots we have. A root is a node
    // which we have seen, but which don't have a parent for.
    const auto cnt = (seen & ~hasParent).count();

    if (cnt == 0)
      answer = std::min(answer, ParseResult::Cycle);
    else if (1 < cnt)
      answer = std::min(answer, ParseResult::MultipleRoots);
  }

  return answer;
}

static_assert(parseLine("(B,D) (D,E) (A,B) (C,F) (E,G) (A,C)") == ParseResult::Good);
static_assert(parseLine("(B,D) (D,E) (A,B) (C,F) (E,G) (A,C)") == ParseResult::Good);
static_assert(parseLine("(A,B) (A,C) (B,D) (D,C)") == ParseResult::Cycle);
static_assert(parseLine("(A,B) (A,B)") == ParseResult::DuplicatePair);
static_assert(parseLine("(A,B) (B,A)") == ParseResult::Cycle);
// Invalid format
static_assert(parseLine("(A,B)  (A,C) (B,D) (D,C)") == ParseResult::InvalidFormat);
static_assert(parseLine("") == ParseResult::InvalidFormat);
static_assert(parseLine("  ") == ParseResult::InvalidFormat);
static_assert(parseLine("(A, B)  (A,C) (B,D) (D,C)") == ParseResult::InvalidFormat);

// We need a cycle and roots
static_assert(parseLine("(A,B) (D,C)") == ParseResult::MultipleRoots);

int main() {
  std::cin.tie(nullptr);
  std::cin.sync_with_stdio(false);

  // We should never see ';' in the input, so I'm using it here to make getline
  // consume the whole input.
  std::string line;
  std::getline(std::cin, line, ';');

  // If we failed to read in a line, or we are not at the end of the line when
  // we reached the newline.
  if (!std::cin || !std::cin.eof()) {
    std::cout << "E1" << std::endl;
    return 1;
  }

  // It's not clear from the specification if it wants us to accept inputs with
  // a newline at the end. I've implemented it here, but it's something that
  // could easily be changed.

  std::string_view view = line;

  if (view.ends_with("\r\n")) {
    view.remove_suffix(2);
  } else if (view.ends_with('\n')) {
    view.remove_suffix(1);
  }

  const auto result = parseLine(view);
  if (result != ParseResult::Good) {
    std::cout << result << std::endl;
    return static_cast<int>(result);
  }

  return 0;
}
