/*
 * p1002 - Phone Numbers
 *
 * I ended up doing this with some very simple dynamic programming. Start at
 * the back and work your way backwards, always checking what the fastest way
 * to get here is.
 *
 * If I wanted to speed this up, the "is_prefix" function could be better and
 * I could create another array with the transformed versions of the words
 * into numbers. That way, we wouldn't need the lookup of the table.
 * 
 * More info can be found here: https://www.fi.muni.cz/ceoi1999/
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MAX_DIGITS 100
#define MAX_WORDS 50000
#define MAX_INPUT (307200 + MAX_WORDS)

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

int main() {
	char* best_word[MAX_DIGITS+1];
	int best_jumps[MAX_DIGITS+1];

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
		int number_size = strlen(readin);
		for (int i = 0; i < number_size; i++) {
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

		// We set the last jump to 0
		best_jumps[number_size] = 0;

		// We start from the back and simply do a comperison each time we get it right.
		for (int i = number_size-1; i >= 0; i--) {
			// We set this to -1.
			best_jumps[i] = -1;
			// For each one that has a match, we check if it is the best one.
			for (int j = 0; j < dict_size; j++) {
				char* word = dict[j];
				int word_size = strlen(word);

				if (is_prefix(number+i, number_size-i,word, word_size)) {
					int rc = best_jumps[i+word_size];
					if (rc != -1 && (best_jumps[i] == -1 || rc+1 < best_jumps[i])) {
						best_jumps[i] = rc+1;
						best_word[i] = word;
					}
				}

			}
		}

		if (best_jumps[0] == -1) {
			printf("No solution.\n");
		} else {
			for (int i = 0; i < number_size; i += strlen(best_word[i])) {
				if (i == 0) {
					printf("%s", best_word[i]);
				} else {
					printf(" %s", best_word[i]);
				}
			}
			printf("\n");
		}
	}

	return 0;
}
