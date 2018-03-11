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
 * The idea for this solution is that we remove one square at a time and
 * and overwrite it with MISSED symbols which are like jokers. They can be
 * anything. We always pick a perfect rectangle, in that it has all matches.
 *
 * This works since we don't have to find the optimal solution.
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

void clear_screen(char *screen) {
	for (int i = 0; i < W*H; i++) {
		screen[i] = EMP;
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
			//printf("Couldn't find anyone, and we still haven't finished!\n");
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
int main() {
	char orig_screen[W*H];
	for (int i = 0; i < W*H; i++) {
		char k;
		do {
			k = getchar();
		} while (k == '\n');
		orig_screen[i] = k;
	}

	// Now we have the board read in.
	
	struct square* comp = remove_solve(orig_screen);

	int N = sb_count(comp);
	printf("%d\n", N);
	
	for (int i = 0; i < N; i++) {
		struct square sq = comp[i];
		printf("%d %d %d\n", sq.x, sq.y, sq.a);
	}

	sb_free(comp);
	return 0;
}
