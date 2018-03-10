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
	int misses;
};

struct square* solve(char* orig);
int instance_test(struct square* actual);


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

void remove_rect(char *screen, char x, char y, char a) {
	// first we draw the vertical lines.
	for (char k = 1; k < a-1; k++) {
		// Upper horiz. 
		screen[COORD(x + k, y)] = MIS;
		// Lower horiz.
		screen[COORD(x + k, y+a-1)] = MIS;
		// Left vert
		screen[(y+k)*W + x] = MIS;
		// Right vert
		screen[(y+k)*W + x + a-1] = MIS;
	}

	// corners.
	screen[y*W + x] = MIS; // UL
	screen[y*W + x + (a - 1)] = MIS; // UR
	screen[(y+(a-1))*W + x] = MIS; // DL
	screen[(y+(a-1))*W + x + (a - 1)] = MIS; // DR
}

// This draws the entire board, clearing the screen first.
void draw_board(char *screen, struct square* squares) {
	clear_screen(screen);
	for (int i = 0; i < sb_count(squares); i++) {
		draw_rect(screen, squares[i].x, squares[i].y, squares[i].a);
	}
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

		struct square tmp = {x, y, a};
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
/*
	char screen[W*H];
	char comp_screen[W*H];
	*/

	while (1) {
		// We generate the initseq and the initstate.
		uint64_t initstate = ((uint64_t)(pcg32_random_r(&rng1)) << 32) | pcg32_random_r(&rng2);
		uint64_t initseq = ((uint64_t)(pcg32_random_r(&rng1)) << 32) | pcg32_random_r(&rng2);
		printf("BOARD ID: 0x%016lX, 0x%016lX\n", initstate, initseq);

		struct square *actual = gen_random_screen(initstate,initseq);

		char rc = instance_test(actual);
		sb_free(actual);
		if (!rc) {
			break;
		}

		/*
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
		*/
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
		int misses = 0;
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
				
				misses += ld == MIS;
				misses += dr == MIS;
				misses += rd == MIS;

				matches += ld == LUC;
				matches += dr == LBC;
				matches += rd == RUC;
			} else if (ca == a-1) {
				misses += dr == MIS;
				matches += dr == RBC;
			} else {
				misses += ld == MIS;
				misses += rd == MIS;
				misses += ur == MIS;
				misses += dr == MIS;

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
			sss.misses = misses;
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

// This calculates the collide map into the collides variable.
void real_collide_map(struct square *squares, int** collides) {
	int SN = sb_count(squares);
	for (int i = 0; i < W*H; i++) {
		// first we free and then set to null everything.
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

	real_collide_map(squares, collides);

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




// This filters out the ones we are sure are there and the ones we don't know.
void filter_out_phase_1(char* screen, struct square *squares, int** sure, int** doubt) {
	int SN = sb_count(squares);
	// We generate a map over the places where two of them has collided.1
	int *collides[W*H];

	real_collide_map(squares, collides);

	// This is where you would do the comparison then		
	char *useless = malloc(SN*sizeof(char));
	char *jokers = malloc(SN*sizeof(char));
	int *ones = malloc(SN*sizeof(int));
	if (ones == NULL || useless == NULL || jokers == NULL) {
		printf("MALLOC ERROR!\n");
		return;
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
		char must = ones[i] != 0;
		char perfect = squares[i].matches == (squares[i].a-1)*4;
		
		// If it is perfect, or we are sure, we add it to the sure pile.
		if (must || perfect) { 
			sb_push(*sure, i);
		}  else {
			// We set useless on this.
			useless[i] = 1;
		}
	}
	
	// Done with the one count.
	free(ones);

	// We have to do this scan first.
	// We do the all useless scan first.
	for (int i = 0; i < W*H; i++) {
		int* cc = collides[i];
		// if there are less than 2 collides, we simply ignore this.
		if (sb_count(cc) < 2) {
			sb_free(cc);
			continue;
		}

		// We must figure out if this is what we want.

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
		}
		sb_free(cc);
	}

	// Now we simply loop through the list and find the ones we doubt.
	for (int i = 0; i < SN; i++) {
		if (jokers[i]) {
			if (jokers[i] > 1) {
				printf("WE GOT MORE THAN 1 THINGY HERE?!?!\n");
			}
			sb_push(*doubt, i);
		}
	}

	free(useless);
	free(jokers);
}


// Taken from here: 
// http://rosettacode.org/wiki/Combinations#Lexicographic_ordered_generation


// This function assumes that the squares are in the correct order, and it
// checks if any of the squares we have, do not affect output in it's current place.
// It returns a list of list over some which can be removed and not affect output.
int* no_effect_on_output(struct square *squares) {
	int SN = sb_count(squares);
	int* ret = NULL;

	
	char orig[W*H];
	char comp[W*H];

	draw_board(orig, squares);

	// we now check for each one.
	for (int i = 0; i < SN; i++) {
		clear_screen(comp);
		for (int j = 0; j < SN; j++) {
			if (j != i) {
				draw_rect(comp, squares[j].x, squares[j].y, squares[j].a);
			}
		}

		if (memcmp(orig,comp,W*H*sizeof(char)) == 0) {
			sb_push(ret, i);
		}
	}
	
	int m = sb_count(ret);

	int c[200] = {0};

	// Now we know the ones that we can remove. Now we just need to create the groups that work.
	for (int n = m; n >= 1; n--) {
		int i = 0;
		for (i = 0; i < n; i++) 
			c[i] = n - i;

		while (1) {
			clear_screen(comp);
			for (int j = 0; j < SN; j++) {
				int found = 0;
				for (int k = 0; k < n; k++) {
					if (j == ret[c[k]-1]) {
						found = 1;
						break;
					}
				}
				if (!found) {
					draw_rect(comp, squares[j].x, squares[j].y, squares[j].a);
				}
			}

			if (memcmp(orig,comp,W*H*sizeof(char)) == 0) {
				int* kkk = NULL;
				for (int k = 0; k < n; k++) {
					sb_push(kkk, ret[c[k]-1]);
				}
				sb_free(ret);
				return kkk;
			}

			/*
			for (i = n; i--;)
				printf("%d%c", c[i], i ? ' ': '\n');
				*/


			int totbreak = 0;
			for (i = 0; c[i] >= m - i;) {
				if (++i >= n)
					totbreak = 1;
			}
			if (totbreak) {
				break;
			}
			for (c[i]++; i; i--) c[i-1] = c[i] + 1;
		}
	}
	return NULL;
}


int still_left(char* screen) {
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			if (screen[COORD(x,y)] != EMP && screen[COORD(x,y)] != MIS) {
				return 1;
			}
		}
	}
	return 0;
}

struct square* 
remove_solve(char* orig) {
	// This is the solution in reverse.
	struct square* sol = NULL;

	// We must create a copy of orig, so that we don't mess it up.
	char screen[W*H];
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			screen[COORD(x,y)] = orig[COORD(x,y)];
		}
	}
	


	while (still_left(screen)) {
		// Gather possible squares.
		struct square *pos_squares = NULL;
		for (char y = 0; y < H; y++) {
			for (char x = 0; x < W; x++) {
				pos_squares = could_be_square(screen, pos_squares, x, y);
			}
		}

		// Now just loop through these squares and try to find one that is perfect.
		int found = 0;
		for (int i = 0; i < sb_count(pos_squares); i++) {
			struct square sq = pos_squares[i];
			char perfect = sq.matches+sq.misses == (sq.a-1)*4;

			if (perfect) {
				sb_push(sol, sq);
				remove_rect(screen, sq.x, sq.y, sq.a);
				found++;
			}
		}

		sb_free(pos_squares);

		if (found == 0) {
			printf("Couldn't find anyone, and we still haven't finished!\n");
		}
	}

	
	struct square* rev_sol = NULL;
	for (int i = sb_count(sol)-1; i >= 0; i--) {
		sb_push(rev_sol, sol[i]);
	}

	sb_free(sol);

	// We are going to remove the ones we don't think have any effect.
	struct square* real_sol = NULL;

	int *noeff = no_effect_on_output(rev_sol);
	if (sb_count(noeff) > 0) {
		printf("Cleaning up %d squares!\n", sb_count(noeff));
		for (int i = 0; i < sb_count(rev_sol); i++) {
			int found = 0;
			for (int j = 0; j < sb_count(noeff); j++) {
				// We here simply 
				if (noeff[j] == i) {
					found = 1;
					break;
				}
			}
			if (!found) {
				sb_push(real_sol, rev_sol[i]);
			}
		}


		sb_free(rev_sol);
	} else {
		real_sol = rev_sol;
	}
	sb_free(noeff);


	return real_sol;
}

// then pick out 1 by one, those who are "perfect" squares.
// I'm going to try another tactic. Generate all possible squares,
int instance_test2(struct square *actual) {
	char orig_screen[W*H];
	char comp_screen[W*H];
	
	draw_board(orig_screen, actual);


	struct square* comp = remove_solve(orig_screen);
	draw_board(comp_screen, comp);


	if (sb_count(actual) != sb_count(comp)) {
		/*
		// First we figure out if the actual has some small flaws.
		int *noeff = no_effect_on_output(comp);
		if (sb_count(noeff) > 0) {
			printf("There are certain squares which have no effect on the output!\n");
		}
		sb_free(noeff);
		*/
		printf("Unevencount: %d vs %d\n", sb_count(actual), sb_count(comp));
	}

	if (memcmp(orig_screen,comp_screen,W*H*sizeof(char)) != 0) {
		printf("DIFFERED IN OUTPUT!\n");
		print_board(orig_screen);
		printf("\n");
		print_board(comp_screen);
		sb_free(comp);
		return 0;
	}

	sb_free(comp);
	return 1;
}

// This 
int instance_test(struct square *actual) {
	return instance_test2(actual);
}



// This is a simple test thing. returns 1 on succsessfull test.
int instance_test1(struct square *actual) {
	int retval = 1;

	/*
	// First we figure out if the actual has some small flaws.
	int *noeff = no_effect_on_output(actual);
	if (sb_count(noeff) > 0) {
		printf("There are certain squares which have no effect on the output!\n");
		retval = 0;
	}

	sb_free(noeff);

	*/


	char orig[W*H];

	draw_board(orig, actual);

	struct square *pos_squares = NULL;
	for (char y = 0; y < H; y++) {
		for (char x = 0; x < W; x++) {
			pos_squares = could_be_square(orig, pos_squares, x, y);
		}
	}

	// we do a quick check here to figure out if we have found all the squares we are
	// going to need.
	for (int i = 0; i < sb_count(actual); i++) {
		struct square ac = actual[i];
		int found = 0;
		for (int j = 0; j < sb_count(pos_squares); j++) {
			struct square tmp = pos_squares[j];
			if (ac.x == tmp.x && ac.y == tmp.y && ac.a == tmp.a) {
				found += 1;
			}
		}
		
		// Check if we didn't find him or there is something fishy going on
		if (found != 1) {
			printf("HERE WE HAVE FOUND! %d\n", found);
		}
	}


	// Now we have the potential squares, we will now figure out
	// who we for sure will have, and those we won't have.
	int* sure_pass_1 = NULL;
	int* doubt_pass_1 = NULL;
	
	// We filter these out.
    filter_out_phase_1(orig, pos_squares, &sure_pass_1, &doubt_pass_1);
	
	// we build the list of the actual ones now.
	struct square* post_pass_1 = NULL;
	for (int j = 0; j < sb_count(sure_pass_1); j++) {
		sb_push(post_pass_1, pos_squares[sure_pass_1[j]]);
	}
	for (int j = 0; j < sb_count(doubt_pass_1); j++) {
		sb_push(post_pass_1, pos_squares[doubt_pass_1[j]]);
	}

	// See if all things went to shit here.
	


	// Now the first test, being if we can find one where a required
	// rectangle is not in the output.
	for (int i = 0; i < sb_count(actual); i++) {
		struct square ac = actual[i];
		int found = 0;
		for (int j = 0; j < sb_count(post_pass_1); j++) {
			struct square tmp = post_pass_1[j];
			if (ac.x == tmp.x && ac.y == tmp.y && ac.a == tmp.a) {
				found += 1;
			}
		}
		
		// Check if we didn't find him or there is something fishy going on
		if (found != 1) {
			// We draw the comp screen here now:
			char sure_screen[W*H];
			char doubt_screen[W*H];
			char comb_screen[W*H];

			clear_screen(sure_screen);
			clear_screen(doubt_screen);
			clear_screen(comb_screen);

			printf("Fpund was: %d\n", found);
			printf("Move missing: %d %d %d\n", ac.x, ac.y, ac.a);

			printf("Moves before first pass: %d\n", sb_count(pos_squares));
			printf("Moves after first pass: %d\n", sb_count(post_pass_1));

			printf("Actual moves %d:\n", sb_count(actual));
			for (int i = 0; i < sb_count(actual); i++) {
				printf(" %d %d %d\n", actual[i].x, actual[i].y, actual[i].a);
			}
			// Print out actual moves.
			printf("Our moves:\n");

			printf(" Sure moves %d:\n", sb_count(sure_pass_1));
			for (int i = 0; i < sb_count(sure_pass_1); i++) {
				int kk = sure_pass_1[i];
				printf("  %d %d %d\n", pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);
				draw_rect(sure_screen, pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);
				draw_rect(comb_screen, pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);

			}

			printf(" Doubt moves %d:\n", sb_count(doubt_pass_1));
			for (int i = 0; i < sb_count(doubt_pass_1); i++) {
				int kk = doubt_pass_1[i];
				printf("  %d %d %d\n", pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);
				draw_rect(doubt_screen, pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);
				draw_rect(comb_screen, pos_squares[kk].x, pos_squares[kk].y, pos_squares[kk].a);
			}
			
			// Now we print.
			

			printf("Sure Board:\n");
			print_board(sure_screen);
			
			printf("Doubt Board:\n");
			print_board(doubt_screen);

			printf("Comb Board:\n");
			print_board(comb_screen);

			printf("Actual Board:\n");
			print_board(orig);
			printf("Missing board:\n");
			clear_screen(comb_screen);
			draw_rect(comb_screen, ac.x, ac.y, ac.a);
			print_board(comb_screen);
			
			retval = 0;
		}
	}
	sb_free(pos_squares);

	sb_free(sure_pass_1);
	sb_free(doubt_pass_1); 
	sb_free(post_pass_1);
	return retval;
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
