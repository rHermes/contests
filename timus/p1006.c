/*
 * http://acm.timus.ru/problem.aspx?space=1&num=1006
 *
 * 1006. Square Frames.
 *
 * N Square frames (1 <= N <= 15)
 *
 * 50 chars wide
 * 20 tall
 *
 *
 * output is in CP347, can be viewed in modern terminal by doing
 *
 * iconv -f CP437 -t utf-8
 *
 * On the output.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MAX 15
#define W 50
#define H 20


#define LUC 218
#define RUC 191
#define LBC 192
#define RBC 217

#define VER 179
#define HOR 196
#define EMP 46

// This is from stb. I use it to get vectors easy for my tests.
#ifndef STB_STRETCHY_BUFFER_H_INCLUDED
#define STB_STRETCHY_BUFFER_H_INCLUDED

#ifndef NO_STRETCHY_BUFFER_SHORT_NAMES
#define sb_free   stb_sb_free
#define sb_push   stb_sb_push
#define sb_count  stb_sb_count
#define sb_add    stb_sb_add
#define sb_last   stb_sb_last
#endif

#define stb_sb_free(a)         ((a) ? free(stb__sbraw(a)),0 : 0)
#define stb_sb_push(a,v)       (stb__sbmaybegrow(a,1), (a)[stb__sbn(a)++] = (v))
#define stb_sb_count(a)        ((a) ? stb__sbn(a) : 0)
#define stb_sb_add(a,n)        (stb__sbmaybegrow(a,n), stb__sbn(a)+=(n), &(a)[stb__sbn(a)-(n)])
#define stb_sb_last(a)         ((a)[stb__sbn(a)-1])

#define stb__sbraw(a) ((int *) (a) - 2)
#define stb__sbm(a)   stb__sbraw(a)[0]
#define stb__sbn(a)   stb__sbraw(a)[1]

#define stb__sbneedgrow(a,n)  ((a)==0 || stb__sbn(a)+(n) >= stb__sbm(a))
#define stb__sbmaybegrow(a,n) (stb__sbneedgrow(a,(n)) ? stb__sbgrow(a,n) : 0)
#define stb__sbgrow(a,n)      (*((void **)&(a)) = stb__sbgrowf((a), (n), sizeof(*(a))))

#include <stdlib.h>

static void * stb__sbgrowf(void *arr, int increment, int itemsize)
{
   int dbl_cur = arr ? 2*stb__sbm(arr) : 0;
   int min_needed = stb_sb_count(arr) + increment;
   int m = dbl_cur > min_needed ? dbl_cur : min_needed;
   int *p = (int *) realloc(arr ? stb__sbraw(arr) : 0, itemsize * m + sizeof(int)*2);
   if (p) {
      if (!arr)
         p[1] = 0;
      p[0] = m;
      return p+2;
   } else {
      #ifdef STRETCHY_BUFFER_OUT_OF_MEMORY
      STRETCHY_BUFFER_OUT_OF_MEMORY ;
      #endif
      return (void *) (2*sizeof(int)); // try to force a NULL pointer exception later
   }
}
#endif // STB_STRETCHY_BUFFER_H_INCLUDED

int solve(char* orig, char *moves);

// == UTILITY ==

// // Assumes 0 <= max <= RAND_MAX
// Returns in the closed interval [0, max]
long random_at_most(long max) {
	unsigned long
		// max <= RAND_MAX < ULONG_MAX, so this is okay.
		num_bins = (unsigned long) max + 1,
				 num_rand = (unsigned long) RAND_MAX + 1,
				 bin_size = num_rand / num_bins,
				 defect   = num_rand % num_bins;

	long x;
	do {
		x = rand();
	}
	// This is carefully written not to overflow
	while (num_rand - defect <= (unsigned long)x);

	// Truncated division is intentional
	return x/bin_size;
}


void clear_screen(char *screen) {
	for (int i = 0; i < W*H; i++) {
		screen[i] = EMP;
	}
}

void print_board(char *screen) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			printf("%c", screen[y*W + x]);
		}
		printf("\n");
	}
}


void draw_rect(char *screen, char x, char y, char a) {
	printf("DRAWING RECT: %d %d %d\n", x, y, a);
	// first we draw the vertical lines.
	for (char k = 1; k < a-1; k++) {
		// Upper horiz. 
		screen[y*W + x + k] = HOR;

		// Lower horiz.
		screen[(y+a-1)*W + x + k] = HOR;

		// Left vert
		screen[(y+k)*W + x] = VER;

		// Right vert
		screen[(y+k)*W + x + a-1] = VER;
	}

	// corners.
	screen[y*W + x] = LUC; // UL
	screen[y*W + x + (a - 1)] = RUC; // UR
	screen[(y+(a-1))*W + x] = LBC; // DL
	screen[(y+(a-1))*W + x + (a - 1)] = RBC; // DR
}

void wtf() {
	char screen[W*H];

	clear_screen(screen);

	draw_rect(screen, 16, 11, 7);
	draw_rect(screen, 32, 14, 4);
	draw_rect(screen, 4, 8, 8);
	draw_rect(screen, 11, 6, 7);
	draw_rect(screen, 36, 11, 3);
	draw_rect(screen, 28, 8, 3);

	print_board(screen);
}



void gen_screen(char *screen) {
	// we zero out the previous board, just to be secure.
	clear_screen(screen);

	// Now then, we figure out how many squares to draw.
	int N = random_at_most(N_MAX-1) + 1;

	// ok, we now loop through the screens.
	for (int i = 0; i < N; i++) {
		// Now we need to generate a rectangle.
		// Since the smallest value we can get is 2 on the sides,
		// we set the limit at W-2 and H-2
		char x = random_at_most(W-2);
		char y = random_at_most(H-2);

		// Now the most we can get for the length of the smallest.
		char a = 0;
		if (W-x > H-y) {
			a = random_at_most(H-y-2) + 2;
		} else {
			a = random_at_most(W-x-2) + 2;
		}

		// Now we simply draw the rectangle.
		draw_rect(screen, x, y, a);
	}
}



int test() {
	// we want the same test sequence each time, so that we don't 
	srand(10);

	char screen[W*H];
	char moves[3*N_MAX];
	char comp_screen[W*H];

	while (1) {
		gen_screen(screen);
		clear_screen(comp_screen);


		int nmoves = solve(screen, moves);
		
		// Now generate the screen
		for (int i = 0; i < nmoves; i++) {
			draw_rect(comp_screen, moves[3*i + 0], moves[3*i + 1], moves[3*i + 2]);
		}

		// check if the two boards are equal.
		if (memcmp(screen,comp_screen,W*H*sizeof(char)) != 0) {
			print_board(screen);
			printf("\n");
			print_board(comp_screen);
			break;
		}
	}

	return 0;
}


int actual_contest() {
	char screen[W*H];
	for (int i = 0; i < W*H; i++) {
		char k;
		do {
			k = getchar();
		} while (k == '\n');
		screen[i] = k;
	}

	// Now we have the board read in.
	

	// Print the board to be safe.
	print_board(screen);
	return 0;
}

int main() {
	// return actual_contest();
	return test();
}

struct square {
	char x;
	char y;
	char a;
	int matches;
};

// The x and y are the upper left corner.
struct square *
could_be_square(char *screen, struct square *squares, char x, char y) {
	if (screen[W*y + x] == EMP) {
		return squares;
	}

	// For now I am going to test every possible size of a, but this could be
	// optimized in the application, by stopping once the down or left ones
	// no longer gave anymore.
	for (char a = 2; x + a <= W && y + a <= H; a++) {
		int matches = 0;
		char clz = 1;
		for (char ca = 0; ca < a; ca++) {
			char kx = x + ca;
			char ky = y + ca;
			// Now we test it all.

			// Left down, up right, right down, down right
			int ld = (unsigned char)screen[W*ky + x];
			int ur = (unsigned char)screen[W*y + kx];
			int rd = (unsigned char)screen[W*ky + x + (a-1)];
			int dr = (unsigned char)screen[W*(y + (a-1)) + kx];

			// Just checking that all the spots are filled.
			clz &= ld != EMP && ur != EMP && rd != EMP && dr != EMP;

			if (!clz) {
				break;
			}

			// Now we check for matches. If it's the first or last round, we need to
			// check for corners.
			if (ca == 0) {
				matches += ld == LUC;
				matches += dr == LBC;
				matches += rd == RUC;
			} else if (ca == a-1) {
				matches += dr == RBC;
			} else {
				matches += ld == VER;
				matches += rd == VER;
				matches += ur == HOR;
				matches += dr == HOR;
			}
		}
		if (clz && matches > 0) {
			struct square sss;
			sss.x = x;
			sss.y = y;
			sss.a = a;
			sss.matches = matches;
			sb_push(squares, sss);
		}
	}

	return squares;
}

// This returns what type the edge is supposed to be.
int supposed_to_be(struct square s, int x, int y) {
	// decide first if he is on edge or not.
	int sx = s.x;
	int sy = s.y;
	int sa = s.a;

	char isleft = sx == x;
	char isright = (sx + sa - 1) == x;
	char isup = sy == y;
	char isdown = (sy + sa - 1) == y;


	if (isup) {
		if (isleft) {
			return LUC;
		} else if (isright) {
			return RUC;
		} else {
			return HOR;
		}
	} else if (!isdown) {
		return VER;
	} else {
		// isdown is true here.
		if (isleft) {
			return LBC;
		} else if (isright) {
			return RBC;
		} else {
			return HOR;
		}
	}
}


// Ok, this becomes easier then. We build a map, figure out who is on top,
// build a DAG from this and then use topological sorting to print out the
// order.
// It returns the order of the squares in squares, to print out.
//
// A way to filter down the squares we are going to need, to look at the
// ones who don't have any 1 and aren't perfect.
int *collide_map(char *screen, struct square *squares) {
	int SN = sb_count(squares);
	// We generate a map over the places where two of them has collided.1
	int *collides[W*H];

	for (int i = 0; i < W*H; i++) {
		collides[i] = NULL;
	}
	
	// Now we genereate the map.
	for (int i = 0; i < SN; i++) {
		struct square s = squares[i];

		int x = s.x;
		int y = s.y;
		int a = s.a;


		for (int k = 1; k < a-1; k++) {
			// Upper horiz. 
			sb_push(collides[y*W + x + k], i);

			// Lower horiz.
			sb_push(collides[(y+a-1)*W + x + k], i);

			// Left vert
			sb_push(collides[(y+k)*W + x], i);

			// Right vert
			sb_push(collides[(y+k)*W + x + a-1], i);
		}
		// Corners
		sb_push(collides[y*W + x], i); // UL
		sb_push(collides[y*W + x + (a - 1)], i); // UR
		sb_push(collides[(y+(a-1))*W + x], i); // DL
		sb_push(collides[(y+(a-1))*W + x + (a - 1)], i); // DR
	}

	// This is where you would do the comparison then		
	int *useless = NULL;
	int *ones = malloc(SN*sizeof(int));
	if (ones == NULL) {
		printf("MALLOC ERROR!\n");
		return NULL;
	}


	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		if (sb_count(cc) == 1) {
			ones[cc[0]]++;
		} 
	}

	// Look for the ones which have no ones, and see if they are perfect.
	for (int i = 0; i < SN; i++) {
		if (ones[i] == 0 && (squares[i].matches != (squares[i].a-1)*4)) {
			sb_push(useless, i);
		}
	}
	
	// Done with the one count.
	// Free ones.
	free(ones);

	for (int i = 0; i < sb_count(useless); i++) {
		struct square s = squares[useless[i]];
		printf("USELESS RECT: %d %d %d\n", s.x, s.y, s.a);
	}
	

	// Now we are going to create the directed graph.
	// We will do this with a 2d array.
	char *edges = malloc(SN*SN*sizeof(char));
	if (edges == NULL) {
		printf("MALLOC ERROR!\n");
		return NULL;
	}

	// Here we build the dag,
	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		if (i % W == 0) {
			printf("\n");
		}
		printf("%d", sb_count(cc));
		
		// Only the places where only one intersects are important to us.
		if (sb_count(cc) != 2) {
			sb_free(collides[i]);
			continue;
		}


		int c1 = cc[0];
		int c2 = cc[1];

		// We skip this if it's useless;
		int ubreak = 0;
		for (int i = 0; i < sb_count(useless); i++) {
			if (useless[i] == c1 || useless[i] == c2) {
				ubreak = 1;	
				break;
			}
		}
		if (ubreak) {
			continue;
		}

		// we now have the integers we need
		sb_free(collides[i]);

		// Check if we already have them ordered.
		if (edges[SN*c1 + c2] || edges[SN*c2 + c1]) {
			continue;
		}

		
		int y = i/W;
		int x = i % W;

		int sup1 = supposed_to_be(squares[c1], x, y);
		int sup2 = supposed_to_be(squares[c2], x, y);
		int act  = (unsigned char)screen[y*W + x];

		if (sup1 == sup2) {
			continue;
		} else if (sup1 == act) {
			// This means that sup1 is the one who is over.
			// therfor we add an edge from sup2 to sup 1
			edges[SN*c2 + c1] = 1;
		} else if (sup2 == act) {
			edges[SN*c1 + c2] = 1;
		} else {
			printf("THIS IS NOT SUPPOSED TO HAPPEN!\n");
		}
	}
	printf("\n");

	// Now the only thing left to do is to topologically sort them.

	int *ans = NULL;
	int *S = NULL;
	int S_first = 0;

	// Find the nodes with no incoming edge.
	for (int i = 0; i < SN; i++) {
		// We skip this if it's useless;
		int ubreak = 0;
		for (int j = 0; j < sb_count(useless); j++) {
			if (useless[j] == i) {
				ubreak = 1;	
				break;
			}
		}
		if (ubreak) {
			continue;
		}
		// Check if anyone has a node to this.
		int clean = 1;

		for (int j = 0; j < SN; j++) {
			if (edges[SN*j + i]) {
				clean = 0;
				break;
			}
		}

		if (clean) {
			// We add it to the queue.
			sb_push(S, i);
		}
	}

	while (sb_count(S) - S_first) {
		int n = S[S_first];
		S_first++;
		sb_push(ans, n);

		for (int i = 0; i < SN; i++) {
			if (edges[SN*n + i]) {
				edges[SN*n + i] = 0;

				// we have to test if it has any other edges.
				int clean = 1;

				for (int j = 0; j < SN; j++) {
					if (edges[SN*j + i]) {
						clean = 0;
						break;
					}
				}

				if (clean) {
					// We add it to the queue.
					sb_push(S, i);
				}
			}
		}
	}


	// Free S
	sb_free(S);


	sb_free(useless);

	// Free the edges.
	free(edges);

	return ans;
}

// Returns amount of moves added to the moves array.
int solve(char* orig, char *moves) {
	// First we are going to run a though experiment though, we are going
	// First thing we do is try to identify the rectangles that are here.
	//
	// WE can divide rectangles into two groups: Whole and non whole.
	// To find the whole ones, we simply search for corners, and once we
	// find them, we can 
	//
	//
	// There is also one more distinction between the rectangles.
	//
	//
	// to generate all the possible squares, not thinking about the actual
	// signs there.
	struct square *pos_squares = NULL;
	for (char y = 0; y < H; y++) {
		for (char x = 0; x < W; x++) {
			pos_squares = could_be_square(orig, pos_squares, x, y);
		}
	}

	int npos = sb_count(pos_squares);

	// Time to free them.
	printf("We counted %d possible squares in total.\n", npos);
	
	// Build a map over all collisions on the map.
	int* draw_order = collide_map(orig, pos_squares);
	
	// Return the moves.
	int ans = 0;
	for (int i = 0; i < sb_count(draw_order); i++) {
		struct square sq = pos_squares[draw_order[i]];
		moves[ans*3] = sq.x;
		moves[ans*3 + 1] = sq.y;
		moves[ans*3 + 2] = sq.a;
		ans++;
	}
	sb_free(pos_squares);

	return ans;
}
