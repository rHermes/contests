/*
 * p. 1016 - Cube on the Walk
 *
 * Seems to be a simple graph problem.
 */

#include <stdio.h>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

template <template<class,class,class...> class C, typename K, typename V, typename... Args>
V GetWithDef(const C<K,V,Args...>& m, K const& key, const V & defval)
{
    typename C<K,V,Args...>::const_iterator it = m.find( key );
    if (it == m.end())
        return defval;
    return it->second;
}

class Cube {
	public:
		int front;
		int back;
		int up;
		int down;
		int left;
		int right;


		Cube() {
			front = 0;
			back = 0;
			up = 0;
			down = 0;
			left = 0;
			right = 0;
		}

		Cube(int f, int b, int u, int d, int l, int r) : front(f), back(b), up(u)
													, down(d), left(l), right(r) {}

		bool operator< (const Cube& c) const {
			if (front != c.front) {
				return front < c.front;
			} else if (back != c.back) {
				return back < c.back;
			} else if (up != c.up) {
				return up < c.up;
			} else if (down != c.down) {
				return down < c.down;
			} else if (left != c.left) {
				return left < c.left;
			} else {
				return right < c.right;
			}
		}


		Cube moveLeft() { return Cube(front, back, right, left, up, down); }
		Cube moveRight() { return Cube(front, back, left, right, down, up); }
		Cube moveUp() { return Cube(down, up, front, back, left, right); }
		Cube moveDown() { return Cube(up, down, back, front, left, right); }

};

class Node {
	public:
		int x;
		int y;
		Cube c;

		Node() {
			x = 0;
			y = 0;
			c = Cube(0,0,0,0,0,0);
		}
		Node(int x, int y, Cube c): x(x), y(y), c(c) {}


		bool operator< (const Node& n) const {
			if (x != n.x) {
				return x < n.x;
			} else if (y != n.y) {
				return y < n.y;
			} else {
				return c < n.c;
			}
		}


		long heuristic(int tx, int ty) {
			// this is the huristic. if we are at the goal, it is 0.
			if (tx == x && ty == y) {
				return 0;
			}

			// For now, we simply return the smallest of the value on the sides.
			return std::min(std::min(c.front, c.back), std::min(c.left, c.right));
		}
};



std::vector<Node> a_star(int sx, int sy, int gx, int gy, Cube c) {

	Node start(sx, sy, c);

	std::set<Node> closedSet;
	std::set<Node> openSet {start};

	std::map<Node,Node> cameFrom;
	std::map<Node,long> gScore;
	
	// The cost of getting to the start, is the current
	// down value.
	gScore[start] = start.c.down;

	std::map<Node,long> fScore;

	fScore[start] = start.heuristic(gx, gy);

	while (!openSet.empty()) {
		Node current = *openSet.begin();

		for (auto& p : openSet) {
			if (fScore[p] < fScore[current]) {
				current = p;
			}  
		}
		
		// We have arrived.
		if (current.x == gx && current.y == gy) {
			std::vector<Node> total_path;

			total_path.push_back(current);

			while (cameFrom.count(current)) {
				current = cameFrom[current];
				total_path.push_back(current);
			}
			return total_path;
		}

		openSet.erase(current);
		closedSet.insert(current);


		// Here we must iterate the neighbors.
		
		std::vector<Node> neis;

		// There are at most 4.
		if (current.x > 0) {
			// This is the one to the left.
			neis.push_back(Node(current.x-1, current.y, current.c.moveLeft()));
		}

		if (current.x < 7) {
			// This is the one to the right.
			neis.push_back(Node(current.x+1, current.y, current.c.moveRight()));
		}

		if (current.y > 0) {
			// This is the one on the bottom.
			neis.push_back(Node(current.x, current.y-1, current.c.moveDown()));
		}

		if (current.y < 7) {
			// This is the one on the top.
			neis.push_back(Node(current.x, current.y+1, current.c.moveUp()));
		}


		for (auto& nei : neis) {
			if (closedSet.count(nei)) {
				continue;
			}

			openSet.insert(nei);

			
			// The distance between the two is the down on the next neighboor.
			long tenta = gScore[current] +	nei.c.down;
			if (tenta >= GetWithDef(gScore, nei, 10000000L)) {
				continue;
			}

			cameFrom[nei] = current;
			gScore[nei] = tenta;
			fScore[nei] = gScore[nei] + nei.heuristic(gx, gy);
		}
	}

	// Now we can print out the path.
	return std::vector<Node>();
}

int main() {
	// So the way I think of doing this is to create a graph,
	// where there is one node for every type of of node.
	//
	// This gives 64*64*6 nodes, this is well within the bounds
	// of the problem.
	//
	// We don't need the entire graph however, we can simply just use the
	// nodes we need as we need them. 
	//
	// We are going to use A* for this. The huristic we will use is the
	// minimum of the sides on the side of the cube. This way, it is better
	// than h(x) = 0, but we will never overestimate. We will either use this
	// or the minimum amount we could get from the entire cube and just rolling.
	// 
	// This will allow us too fairly easly do a lot of this.
	//
	//
	// A possible optimi
	//
	// e2 e3 0 8 1 2 1 1
	// Cube test_1(0, 8, 1, 1, 1, 2);
	// std::vector<Node> pth = a_star(4, 1, 4, 2, test_1);

	// here we read it in.
	char m1x, m2x;
	int m1y, m2y, f, b, u, r, d, l;
	scanf("%c%d %c%d %d %d %d %d %d %d", &m1x, &m1y, &m2x, &m2y, &f, &b, &u, &r, &d, &l);

	Cube inn(f, b, u, d, l, r); 
	std::vector<Node> pth = a_star(m1x-'a',m1y-1, m2x-'a', m2y-1, inn);


	if (pth.size() == 0) {
		printf("WTF!\n");
	} else {
		long sum = 0;
		for (auto it = pth.begin(); it != pth.end(); it++) {
			sum += it->c.down;
		}
		printf("%ld", sum);

		for (auto it = pth.rbegin(); it != pth.rend(); it++) {
			printf(" %c%d", 'a'+(it->x), it->y+1);
		}
		printf("\n");
	}
	
	return 0;
}
