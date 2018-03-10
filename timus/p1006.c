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
#include <stdint.h>

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

// Simple random code from pcb-c-basic
struct pcg_state_setseq_64 {    // Internals are *Private*.
    uint64_t state;             // RNG state.  All values are possible.
    uint64_t inc;               // Controls which RNG sequence (stream) is
                                // selected. Must *always* be odd.
};
typedef struct pcg_state_setseq_64 pcg32_random_t;

uint32_t pcg32_random_r(pcg32_random_t* rng)
{
    uint64_t oldstate = rng->state;
    rng->state = oldstate * 6364136223846793005ULL + rng->inc;
    uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
    uint32_t rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

void pcg32_srandom_r(pcg32_random_t* rng, uint64_t initstate, uint64_t initseq)
{
    rng->state = 0U;
    rng->inc = (initseq << 1u) | 1u;
    pcg32_random_r(rng);
    rng->state += initstate;
    pcg32_random_r(rng);
}

uint32_t pcg32_boundedrand_r(pcg32_random_t* rng, uint32_t bound) {
	uint32_t threshold = -bound % bound;
	for (;;) {
		uint32_t r = pcg32_random_r(rng);
		if (r >= threshold)
			return r % bound;
	}
}

// == HERE BEGINS MY CODE! ==
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

// This is the missing one.
#define MIS 88


#define COORD(X,Y) ((Y)*W + (X))


struct square {
	char x;
	char y;
	char a;
	int matches;
};

struct square* solve(char* orig);


void clear_screen(char *screen) {
	for (int i = 0; i < W*H; i++) {
		screen[i] = EMP;
	}
}

void print_board(char *screen) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			printf("%c", screen[COORD(x,y)]);
		}
		printf("\n");
	}
}


void draw_rect(char *screen, char x, char y, char a) {
	// first we draw the vertical lines.
	for (char k = 1; k < a-1; k++) {
		// Upper horiz. 
		screen[COORD(x + k, y)] = HOR;
		// Lower horiz.
		screen[COORD(x + k, y+a-1)] = HOR;
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

struct square*
gen_random_screen(uint64_t initstate, uint64_t initseq) {
	struct square* sqrs = NULL;

	pcg32_random_t rng;

	// Init the random number generator for this board.
	pcg32_srandom_r(&rng, initstate, initseq);

	// Now then, we figure out how many squares to draw.
	int N = pcg32_boundedrand_r(&rng, (N_MAX-1)) + 1;

	// ok, we now loop through the screens.
	for (int i = 0; i < N; i++) {
		// Now we need to generate a rectangle.
		// Since the smallest value we can get is 2 on the sides,
		// we set the limit at W-2 and H-2
		char x = pcg32_boundedrand_r(&rng, (W-2));
		char y = pcg32_boundedrand_r(&rng, (H-2));

		// Now the most we can get for the length of the smallest.
		char a = 0;
		if (W-x > H-y) {
			a = pcg32_boundedrand_r(&rng, (H-y-2)) + 2;
		} else {
			a = pcg32_boundedrand_r(&rng, (W-x-2)) + 2;
		}

		struct square tmp;
		tmp.x = x;
		tmp.y = y;
		tmp.a = a;
		sb_push(sqrs, tmp);

	}
	return sqrs;
}


// This function generates tests and tests it against my solutions.
int test() {
	// We are going to get the same things each time.
	pcg32_random_t rng1, rng2;
	
	// Initialize the random generators.
	pcg32_srandom_r(&rng1, 42u, 52u);
	pcg32_srandom_r(&rng2, 79u, 1002u);

	char screen[W*H];
	char comp_screen[W*H];

	while (1) {
		// We generate the initseq and the initstate.
		uint64_t initstate = ((uint64_t)(pcg32_random_r(&rng1)) << 32) | pcg32_random_r(&rng2);
		uint64_t initseq = ((uint64_t)(pcg32_random_r(&rng1)) << 32) | pcg32_random_r(&rng2);
		printf("BOARD ID: 0x%016lX, 0x%016lX\n", initstate, initseq);

		struct square *actual = gen_random_screen(initstate,initseq);

		clear_screen(screen);
		for (int i = 0; i < sb_count(actual); i++) {
			draw_rect(screen, actual[i].x, actual[i].y, actual[i].a);
		}


		// Now we have a screen and we can compute the list of moves for it.
		struct square *computed = solve(screen);	


		// Now generate the screen
		clear_screen(comp_screen);
		for (int i = 0; i < sb_count(computed); i++) {
			draw_rect(comp_screen, computed[i].x, computed[i].y, computed[i].a);
		}

		// check if the two boards are equal.
		if (memcmp(screen,comp_screen,W*H*sizeof(char)) != 0) {
			// Now we have something which is not good.
			// First we print out the id of the board.
			printf("Something went wrong!\n");
			//printf("BOARD ID: 0x%08lX, 0x%08lX\n", initstate, initseq);



			print_board(screen);
			printf("\n");
			print_board(comp_screen);

			// Print out actual moves.
			printf("Actual moves: \n");
			for (int i = 0; i < sb_count(actual); i++) {
				printf(" %d %d %d\n", actual[i].x, actual[i].y, actual[i].a);
			}
			// Print out actual moves.
			printf("Our moves: \n");
			for (int i = 0; i < sb_count(computed); i++) {
				printf(" %d %d %d\n", computed[i].x, computed[i].y, computed[i].a);
			}

			sb_free(actual);
			sb_free(computed);
			break;
		}
		sb_free(actual);
		sb_free(computed);
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
	char *useless = malloc(SN*sizeof(char));
	char *jokers = malloc(SN*sizeof(char));
	int *ones = malloc(SN*sizeof(int));
	if (ones == NULL || useless == NULL || jokers == NULL) {
		printf("MALLOC ERROR!\n");
		return NULL;
	}

	for (int i = 0; i < SN; i++) {
		ones[i] = 0;
		useless[i] = 0;
		jokers[i] = 0;
	}

	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		if (sb_count(cc) == 1) {
			ones[cc[0]]++;
		} 
	}

	// Look for the ones which have no ones, and see if they are perfect.
	for (int i = 0; i < SN; i++) {
		// If a square has no point of no conflict, and it is not a perfect
		// square, we mark it as useless
		if (ones[i] == 0 && (squares[i].matches != (squares[i].a-1)*4)) {
			useless[i] = 1;
		}
	}
	
	// Done with the one count.
	// Free ones.
	free(ones);
	

	// Now we are going to create the directed graph.
	// We will do this with a 2d array.
	char *edges = malloc(SN*SN*sizeof(char));
	if (edges == NULL) {
		printf("MALLOC ERROR!\n");
		return NULL;
	}

	for (int i = 0; i < SN*SN; i++) {
		edges[i] = 0;
	}



	// We have to do this scan first.
	// We do the all useless scan first.
	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		
		// if there are less than 2 collides, we simply ignore this.
		if (sb_count(cc) < 2) {
			continue;
		}


		// We have to figure out 
		// OK, so we are going to have to cheat a little bit here.
		// if there are only useless ones here, we have a case where
		// there is one that is not useless. we test this by checking
		// if they are all useless.
		int all_useless = 0;
		for (int j = 0; j < sb_count(cc); j++) {
			all_useless += useless[cc[j]];
		}
		if (all_useless == sb_count(cc)) {
			for (int j = 0; j < sb_count(cc); j++) {
				// we mark them all as not useless
				jokers[cc[j]]++;
				useless[cc[j]] = 0;
			}
			// If this is the case, we simply add them all to not useless

			// TODO(rhermes): This can be optimized by only looking at the borders of
			// both rectangles, but I couldn't be bothered to check write the code.
			// This will only happen a very few times and the extra overhead is very
			// small
			
			// OK. The way we do this is simple. We simply check if there is a spot
			// where only one uselss actually matches.
			
			// Everyone there was useless.
			// printf("WE HAVE AN ALL USELESS SPACE WITH %d POSSIBILITIES.\n", all_useless);
			// What we do now, is we check all the other places where they intersect and
			// if there is a place there where they have different expected values, we check it out.
			/*
			if (sb_count(cc) != 2) {
				printf("THERE ARE MORE THAN 2 USELESS!\n");
			}


			int u1 = cc[0];
			int u2 = cc[1];
			
			// 0 means u1, 1 means u2;
			int overall_res = -1;

			for (int y = 0; y < H; y++) {
				for (int x = 0; x < W; x++) {
					int* dcc = collides[y*W + x];

					// we now have to check if they are here.
					int found1 = 0;
					int found2 = 0;

					for (int jj = 0; jj < sb_count(dcc); jj++) {
						if (dcc[jj] == u1) {
							found1 = 1;
						} else if (dcc[jj] == u2) {
							found2 = 1;
						}
					}

					if (!found1 || !found2) {
						continue;
					}

					// Now we simply check what the expected value for both is
					// here and then we see what the actual answer is.
					int sup1 = supposed_to_be(squares[u1], x, y);
					int sup2 = supposed_to_be(squares[u2], x, y);
					int act  = (unsigned char)screen[y*W + x];

					if (sup1 == sup2) {
						continue;
					} else if (sup1 == act) {
						// This means that sup1 is the one who is over.
						// therfor we add an edge from sup2 to sup 1
						overall_res = 0;
					} else if (sup2 == act) {
						overall_res = 1;
					} else {
						printf("THIS IS NOT SUPPOSED TO HAPPEN!\n");
					}
				}

				if (overall_res != -1) {
					break;
				}
			}

			// if the overall result is still -1, then we simply pick one at random.
			if (overall_res == 0) {
				useless[u1] = 0;
			} else if (overall_res == 1) {
				useless[u2] = 0;
			} else {
				// THis means we found no conflicting place where one was dominant.
				printf("WTF!\n");
			}
			*/

		}
	}


	// Here we loop through the jokers.
	int first_first = 0;	
	for (int i = 0; i < SN; i++) {
		if (jokers[i]) {
			struct square sp = squares[i];
			if (first_first == 0) {
				printf("Jokers:\n");
				first_first = 1;
			}
			printf("- %d : %d : %d %d %d\n", i, jokers[i], sp.x, sp.y, sp.a);
		}
	}

	// So this is where we build the directed acyclic graph;

	// Here we build the dag,
	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		/*
		if (i % W == 0) {
			printf("\n");
		}
		printf("%d", sb_count(cc));
		*/

		if (sb_count(cc) < 2) {
			sb_free(collides[i]);
			continue;
		}

		// We cheat a little here, to speed things up.
		// if a square is perfect is must be first,
		// and so we can simply set the other ones up to it.
		for (int per = 0; per < sb_count(cc); per++) {
			struct square pers = squares[cc[per]];
			if (pers.matches != (pers.a-1)*4) {
				continue;
			}
			// Since only 1 can be perfect in such overlaps, we can now loop through again.

			for (int uper = 0; uper < sb_count(cc); uper++) {
				// Skip if either is uless or the same as the upper.
				if (uper == per || useless[cc[uper]]) {
					continue;
				}

				// Else set the edge
				edges[SN*cc[uper] + cc[per]] = 1;
			}
			
			break;
		}
		
		
		int *useful = NULL;
		// Make sure that there are 2 usefull ones.
		for (int j = 0; j < sb_count(cc); j++) {
			if (!useless[cc[j]]) {
				sb_push(useful, cc[j]);
			}
		}
		sb_free(collides[i]);

		// OK so check here is very simple. We check if there is only 1
		// with the correct expected value, and if it is, we add that
		// as an edge to all the others that are here.
		int y = i/W;
		int x = i % W;

		int act  = (unsigned char)screen[y*W + x];
		
		int thecor = -1;
		for (int j = 0; j < sb_count(useful); j++) {
			int sup = supposed_to_be(squares[useful[j]], x, y);
			if (sup == act) {
				if (thecor < 0) {
					thecor = useful[j];
				} else {
					thecor = -2;
					break;
				}
			}
		}

		// Now we check if there is only one.
		if (thecor >= 0) {
			// Since there is only one correct here, it must
			// mean that the others ones must be beneath it.
			for (int j = 0; j < sb_count(useful); j++) {
				if (useful[j] == thecor) {
					continue;
				}

				// add the link.
				edges[SN*useful[j] + thecor] = 1;
			}
		}

		sb_free(useful);
	}


	// Now the only thing left to do is to topologically sort them.

	int *ans = NULL;
	int *S = NULL;
	int S_first = 0;

	// Find the nodes with no incoming edge.
	for (int i = 0; i < SN; i++) {
		// We skip this if it's useless;
		if (useless[i]) {
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

	// Free the edges.
	free(useless);
	free(jokers);
	free(edges);

	return ans;
}

// Returns amount of moves added to the moves array.
struct square *solve(char* orig) {
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
	struct square *solution = NULL;

	struct square *pos_squares = NULL;
	for (char y = 0; y < H; y++) {
		for (char x = 0; x < W; x++) {
			pos_squares = could_be_square(orig, pos_squares, x, y);
		}
	}

	/* Now we have all the possible squares. Out of these there are a maximum of
	 * 15 which are the actual solution. */

	/*
	int npos = sb_count(pos_squares);

	// Time to free them.
	printf("We counted %d possible squares in total.\n", npos);
	for (int i = 0; i < npos; i++) {
		struct square tmp = pos_squares[i];
		printf(" %d %d %d\n", tmp.x, tmp.y, tmp.a);
	}
	*/
	
	// Build a map over all collisions on the map.
	int* draw_order = collide_map(orig, pos_squares);
	
	// Return the moves.
	for (int i = 0; i < sb_count(draw_order); i++) {
		struct square sq = pos_squares[draw_order[i]];
		sb_push(solution, sq);
	}
	sb_free(pos_squares);
	sb_free(draw_order);

	return solution;
}
