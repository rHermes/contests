/*
 * p1002 - Phone Numbers
 */

// Table generated in python by doing:
//
// import itertools
// mps = [(1, "ij"), (2, "abc"), (3, "def"), (4, "gh"), (5, "kl"), (6, "mn"), (7, "prs"), (8, "tuv"), (9, "wxy"), (0, "oqz")]
// blowup = itertools.chain.from_iterable([[(k, c) for c in v] for (k,v) in mps])
// tbl = [a[0] for a in sorted(blowup,key=lambda tup: tup[1])]
// print(tbl)
//
// The output from that command is: 
//
// [2, 2, 2, 3, 3, 3, 4, 4, 1, 1, 5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0]
//
// One way to do this is to 

// One way we could do this is to create a graph over all the ones
// that does fit the bill, then do a shortests path search to find
// the shortest one. The question then becomes how to identify words that would fit.
//
// A prefix tree might be the fastest way to do this?
//
// Another way to do this is to do a sort on the words, 2 layers deep.
//
//
// How one would do this then is to search through all the words against the number,
// and see if it works.


#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Table from (c-'a') to the number.
const int8_t lookup[] =  {2, 2, 2, 3, 3, 3, 4, 4, 1, 1, 5, 5, 6, 6, 0, 7, 0, 7, 7, 8, 8, 8, 9, 9, 9, 0};


// returns 0 on not a prefix and 1 on prefix.
int is_prefix(uint8_t* number, int number_size, char* word, int word_size) {
	if (number_size < word_size) {
		return 0;
	}

	for (int i = 0; i < word_size; i++) {
		if (number[i] != lookup[word[i]-'a']) {
			return 0;
		}
	}
	return 1;
}


// We do this recursiv so that we don't need a queue.
int solve(uint8_t* number, int number_size, char** dict, int dict_size, int level, int best_so_far,
		char** buffer, char** buffer_best) {
	// We don't go deeper than we need to.
	if (level > best_so_far) {
		return best_so_far;
	}

	if (number_size == 0) {
		return level;
	}

	// First we checkout every single word and where it would fit.
	for (int i = 0; i < dict_size; i++) {
		char* word = dict[i];
		int word_size = strlen(word);
		if (is_prefix(number, number_size, word, word_size)) {
			// Mutate the buffer.
			buffer[level] = word;
			int new_rc = solve(number+word_size, number_size-word_size, dict, dict_size, level+1, best_so_far, buffer, buffer_best);
			if (new_rc < best_so_far) {
				best_so_far = new_rc;
				
				// copy over the buffer.
				for (int j = 0; j < new_rc; j++) {
					buffer_best[j] = buffer[j];
				}
			}
		}
	}

	return best_so_far;
}



#define MAX_DIGITS 100
#define MAX_INPUT 307200
#define MAX_WORDS 50000
int main() {
	char* buffer[MAX_DIGITS+1];
	char* buffer_best[MAX_DIGITS+1];

	char readin[MAX_INPUT+1];
	char* dict[MAX_WORDS];

	uint8_t number[MAX_DIGITS];
	
	// This is the loop we use.
	while (1) {
		scanf("%s", readin);
		// First thing we check is if it's -1
		if (readin[0] == '-') {
			break;
		}
		// Now we loop through and build the array.
		int num_length = strlen(readin);
		for (int i = 0; i < num_length; i++) {
			number[i] = readin[i]-'0';
		}

		// Now we need to read in the number of words.
		int dict_size = 0;
		scanf("%d", &dict_size);

		int read_so_far = 0;
		for (int i = 0; i < dict_size; i++) {
			scanf("%s", readin+read_so_far);
			dict[i] = readin+read_so_far;
			read_so_far += 1 + strlen(dict[i]);
		}

		// Now we have all the info, we simply call the function
		int best = solve(number, num_length, dict, dict_size, 0, MAX_DIGITS+1, buffer, buffer_best);

		if (best == MAX_DIGITS+1) {
			printf("No solution.\n");
		} else {
			// We can now go through the buffer best.
			for (int i = 0; i < best; i++) {
				if (i == 0) {
					printf("%s", buffer_best[i]);
				} else {
					printf(" %s", buffer_best[i]);
				}
			}
			printf("\n");
		}
	}

	return 0;
}
