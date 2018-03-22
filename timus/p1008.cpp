/*
 * p1008 - Image encoding
 *
 */

#include <stdio.h>
#include <vector>
#include <queue>
#include <set>
#include <utility>


void parse_first(bool pixels[10][10], int number) {
	for (int i = number; i > 0; i--) {
		int a, b;
		scanf("%d %d\n", &a, &b);
		pixels[b-1][a-1] = true;
	}
}

void parse_second(bool pixels[10][10], int sx, int sy) {
	std::queue<std::pair<int,int>> work;

	work.push(std::make_pair(sx,sy));

	while (!work.empty()) {
		std::pair<int,int> current = work.front();
		work.pop();

		int cx = current.first;
		int cy = current.second;

		// insert the current one.
		pixels[cy][cx] = true;
		
		// scan a line.
		char line[10];
		fgets(line, 10, stdin);

		for (int i = 0; line[i] != ',' && line[i] != '.'; i++) {
			int ii = line[i];
			if (ii == 'R') {
				work.push(std::make_pair(cx+1,cy));
			} else if (ii == 'L') {
				work.push(std::make_pair(cx-1,cy));
			} else if (ii == 'T') {
				work.push(std::make_pair(cx,cy+1));
			} else if (ii == 'B') {
				work.push(std::make_pair(cx,cy-1));
			}
		}
	}
}

// returns 0 on first rep and 1 on second rep. and -1 on error.
int parse(bool pixels[10][10]) {
	// We can tell from the first line what this is going to be.
	int a, b, rc;

	char line[10];
	fgets(line, 10, stdin);
	rc = sscanf(line, "%d %d\n", &a, &b);

	if (rc == 1) {
		// its the first format.
		parse_first(pixels, a);
		return 0;
	} else if (rc == 2) {
		parse_second(pixels, a-1, b-1);
		return 1;
	}
	return -1;
}

void print_first(bool pixels[10][10]) {
	std::vector<std::pair<int,int>> outs;
	for (int x = 0; x < 10; x++) {
		for (int y = 0; y < 10; y++) {
			if (pixels[y][x]) {
				outs.push_back(std::make_pair(x,y));
			}
		}
	}

	printf("%ld\n", outs.size());
	for (auto& p : outs) {
		printf("%d %d\n", p.first+1, p.second+1);
	}
}

void print_second(bool pixels[10][10]) {
	std::set<std::pair<int,int>> seen;
	std::queue<std::pair<int,int>> work;

	// First we find the first pixel.
	bool first = true;
	std::pair<int,int> start_point;
	for (int x = 0; x < 10 && first; x++) {
		for (int y = 0; y < 10; y++) {
			if (pixels[y][x]) {
				first = false;
				work.push(std::make_pair(x,y));
				// we now print out the location
				printf("%d %d\n", x+1, y+1);
				break;
			}
		}
	}

	// We now have the first one, and we print out
	while (!work.empty()) {
		std::pair<int,int> current = work.front();
		work.pop();
		seen.insert(current);

		int cx = current.first;
		int cy = current.second;

		// We check right, up, left, down
		// Right
		if (cx < 9 && pixels[cy][cx+1]) {
			std::pair<int,int> tmp = std::make_pair(cx+1,cy);
			if (!seen.count(tmp)) {
				seen.insert(tmp);
				work.push(tmp);
				printf("R");
			}
		}

		// UP
		if (cy < 9 && pixels[cy+1][cx]) {
			std::pair<int,int> tmp = std::make_pair(cx,cy+1);
			if (!seen.count(tmp)) {
				seen.insert(tmp);
				work.push(tmp);
				printf("T");
			}
		}

		// Left
		if (cx > 0 && pixels[cy][cx-1]) {
			std::pair<int,int> tmp = std::make_pair(cx-1,cy);
			if (!seen.count(tmp)) {
				seen.insert(tmp);
				work.push(tmp);
				printf("L");
			}
		}

		// Down
		if (cy > 0 && pixels[cy-1][cx]) {
			std::pair<int,int> tmp = std::make_pair(cx, cy-1);
			if (!seen.count(tmp)) {
				seen.insert(tmp);
				work.push(tmp);
				printf("B");
			}
		}
		// We are now done with this

		// we must check here if this will be the last line.
		if (work.empty()) {
			printf(".\n");
		} else {
			printf(",\n");
		}
	}
}

int main() {
	bool pixels[10][10] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0}
	};
	int rc;
	rc = parse(pixels);

	if (rc < 0) {
		printf("GREAVE MISTAKE!\n");
		return 1;
	} else if (rc == 0) {
		print_second(pixels);
	} else {
		print_first(pixels);
	}

	return 0;
}
