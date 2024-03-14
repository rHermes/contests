// For a K-D tree approach:
// https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/solutions/1182639/k-d-tree-solution-follow-up-with-solutions-overview-c/
// https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/solutions/1182879/Optimized-K-D-tree-Solution-+-Follow-up-with-solutions-overview-C++/


// https://stackoverflow.com/questions/41946007/efficient-and-well-explained-implementation-of-a-quadtree-for-2d-collision-det
// Read more here about quad trees also!
#include <map>
#include <vector>
#include <stdexcept>
#include <memory>
#include <iostream>
#include <cmath>

struct Rect {
	int lx;
	int ly;

	int tx;
	int ty;

	Rect(int ax, int ay, int bx, int by) : lx{ax}, ly{ay}, tx{bx}, ty{by} {
		// we just assert some things here.
		if (tx < lx || ty < ly)
			throw std::runtime_error("Invalid rectangle");
	}


	[[nodiscard]] bool intersects(const Rect& other) {
		// lets check
		return (this->lx <= other.tx && other.lx <= this->tx)
			&& (this->ly <= other.ty && other.ly <= this->ty);
	}

	[[nodiscard]] bool contains(const int x, const int y) {
		return (this->lx <= x && x <= this->tx) && (
				this->ly <= y && y <= this->ty
				);
	}
};


class QuadNode {
	Rect area;

	const std::size_t MaxData_{16};

	std::vector<std::pair<int,int>> pts_;

	std::unique_ptr<QuadNode> nw;
	std::unique_ptr<QuadNode> ne;
	std::unique_ptr<QuadNode> sw;
	std::unique_ptr<QuadNode> se;



	public:

	QuadNode(int ax, int ay, int bx, int by) : area(ax, ay, bx, by) {}
	explicit QuadNode(Rect ar) : area(std::move(ar)) {}


	[[nodiscard]] bool insert(const int x, const int y) {
		if (!area.contains(x, y))
			return false;

		// we always have to check if we contain it.


		if (pts_.size() < MaxData_) {
			// std::cout << "we are inserting data!" << std::endl;
			pts_.emplace_back(x, y);

			if (pts_.size() < MaxData_)
				return true;

			// Ok, now we need to split.
			// We can actually always split, because our area is even.
			// They all have the same size.
			int midx = (area.tx+area.lx) / 2;
			int midy = (area.ty+area.ly) / 2;

			nw = std::make_unique<QuadNode>(area.lx, midy+1, midx, area.ty);
			ne = std::make_unique<QuadNode>(midx+1, midy+1, area.tx, area.ty);
			se = std::make_unique<QuadNode>(midx+1, area.ly, area.tx, midy);
			sw = std::make_unique<QuadNode>(area.lx, area.ly, midx, midy);

			return true;
		} else {
			// std::cout << "We are going into the lower barracks here!" << std::endl;
			if (nw->insert(x,y))
				return true;

			if (ne->insert(x,y))
				return true;

			if (se->insert(x,y))
				return true;

			if (sw->insert(x,y))
				return true;

			throw std::runtime_error("We should never reach this!");
		}
	}

	// query based on the circle.
	void query(std::vector<std::pair<int,int>>& out, const int x, const int y, const int r) {
		Rect re(x-r, y-r, x+r, y+r);

		if (!area.intersects(re)) {
			/* std::cout << "We had a miss, but this shouldn't be possible" << std::endl; */
			return;
		}

		// we must check all at my level.
		for (const auto& [sx,sy] : pts_) {
			bool lol = (std::pow(sx - x,2) + std::pow(sy - y, 2)) <= r*r;
			/*
				 std::cout << "comparing circle (" << x << ", " << y << ", " << r << ") with (" << sx << ", " << sy << ")" << 
				 " gives: " << lol << std::endl;
				 */
			if (lol)
				out.emplace_back(sx, sy);
		}

		// Then we need to check below us also.
		if (pts_.size() == MaxData_) {
			nw->query(out, x, y, r);
			ne->query(out, x, y, r);
			se->query(out, x, y, r);
			sw->query(out, x, y, r);
		}
	}
};

class Solution {
	public:
		std::vector<int> countPoints(std::vector<std::vector<int>>& points, std::vector<std::vector<int>>& queries) {
			// OK, we are going to try to solve this with a quad tree.
			// I'm going to count the number of times a vector is inserted, and we will get
			// out an array of vectors for each.
			QuadNode root(0, 0, 500, 500);

			std::map<std::pair<int,int>, int> comp;
			for (const auto& pt : points) {
				auto [it, found] = comp.emplace(std::piecewise_construct,
						std::forward_as_tuple(pt[0], pt[1]),
						std::forward_as_tuple(1));
				if (found) {
					std::ignore = root.insert(pt[0], pt[1]);
				} else {
					it->second++;
				}
			}

			// std::cout << "We inserted " << comp.size() << " unique elements" << std::endl;

			std::vector<int> ans;
			std::vector<std::pair<int,int>> temp;
			for (const auto& qr : queries) {
				temp.clear();
				root.query(temp, qr[0], qr[1], qr[2]);

				// std::cout << "We had " << temp.size() << " hits for this query" << std::endl;

				int hits = 0;
				for (const auto& p : temp) {
					hits += comp[p];
				}

				ans.push_back(hits);
			}

			return ans;
		}
};

int main() { return 0; };
