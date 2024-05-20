#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

struct Rect
{
  int ly;
  int lx;

  int ty;
  int tx;

  Rect(int xi, int yi, int ai, int bi)
  {
    ly = yi;
    lx = xi;
    ty = bi;
    tx = ai;
  }

  auto operator<=>(const Rect&) const = default;

  friend std::ostream& operator<<(std::ostream& stream, const Rect& r)
  {
    stream << "((" << r.lx << ", " << r.ly << "), (" << r.tx << ", " << r.ty << "))";
    return stream;
  }
};

struct Node
{
  bool dirty{ false };

  bool even{ true };
  int y{ 0 };
};

void
pushDown(std::vector<Node>& nodes, const std::size_t idx)
{
  auto& root = nodes[idx];
  if (root.dirty) {
    auto& left = nodes[idx * 2];
    auto& right = nodes[idx * 2 + 1];

    left.dirty = right.dirty = true;
    left.even = right.even = true;
    left.y = right.y = root.y;
    root.dirty = false;
  }
}

bool
update(std::vector<Node>& nodes,
       const std::size_t idx,
       const std::size_t tl,
       const std::size_t tr,
       const std::size_t l,
       const std::size_t r,
       const int expected,
       const int newVal)
{
  // The node that we end up updating, has to be even. Otherwise, we are
  // screwed to begin with. Furthermore, it has to have the same value as we
  // expect.
  auto& root = nodes[idx];
  if (l == tl && r == tr) {
    if (!root.even)
      return false;

    if (root.y != expected)
      return false;

    root.dirty = true;
    root.y = newVal;
    return true;
  } else {
    pushDown(nodes, idx);
    std::size_t tm = (tl + tr) / 2;

    if (l <= tm) {
      if (!update(nodes, idx * 2, tl, tm, l, std::min(r, tm), expected, newVal))
        return false;
    }

    if ((tm + 1) <= r) {
      if (!update(nodes, idx * 2 + 1, tm + 1, tr, std::max(l, tm + 1), r, expected, newVal))
        return false;
    }

    auto& left = nodes[idx * 2];
    auto& right = nodes[idx * 2 + 1];
    if (left.even && right.even && (left.y == right.y)) {
      root.even = true;
      root.y = left.y;
    } else {
      root.even = false;
    }

    return true;
  }
}

void
printOut(std::vector<Node>& nodes, const std::size_t idx, const std::size_t tl, const std::size_t tr, int level = 0)
{

  // So This is the idea:
  // The node that we end up updating, has to be even. Otherwise, we are
  // screwed to begin with. Furthermore, it has to have the same value as we
  // expect.
  const auto& root = nodes[idx];
  for (int i = 0; i < level; i++)
    std::cout << "  ";

  std::cout << idx << "[" << tl << ", " << tr << "]: even=" << root.even << ", y=" << root.y << std::endl;

  if (tl == tr)
    return;

  pushDown(nodes, idx);
  std::size_t tm = (tl + tr) / 2;
  printOut(nodes, idx * 2, tl, tm, level + 1);
  printOut(nodes, idx * 2 + 1, tm + 1, tr, level + 1);
}

class Solution
{
public:
  bool isRectangleCover(std::vector<std::vector<int>>& rectangles)
  {
    if (rectangles.size() == 1)
      return true;

    std::vector<Rect> rects;
    int minx = std::numeric_limits<int>::max();
    int miny = std::numeric_limits<int>::max();
    int maxx = -std::numeric_limits<int>::max();

    for (const auto& rc : rectangles) {
      minx = std::min(minx, rc[0]);
      miny = std::min(miny, rc[1]);
      maxx = std::max(maxx, rc[2]);

      rects.emplace_back(rc[0], rc[1], rc[2], rc[3]);
    }
    std::sort(rects.begin(), rects.end());

    const std::size_t WIDTH = static_cast<std::size_t>(maxx - minx);
    std::vector<Node> tree(4 * WIDTH);
    // Now we are going to go through and add each rectangle.
    for (const auto& r : rects) {
      const int curY = r.ly - miny;
      const int nextY = r.ty - miny;
      const std::size_t tl = static_cast<std::size_t>(r.lx - minx);
      const std::size_t tr = static_cast<std::size_t>(r.tx - minx - 1);

      if (!update(tree, 1, 0, WIDTH - 1, tl, tr, curY, nextY))
        return false;
    }

    // Now we just need to see if the root is even.
    return tree[1].even;
  }
};

int
main()
{
  return 0;
}
