/*
 * p1038 - Spell Checker
 *
 * Just another parser problem in disguise.
 */


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

char buff[10001];

int main() {
	bool sentence_start = true;
	int mistakes = 0;
	while (fgets(buff, sizeof(buff), stdin) != NULL) {
		for (char *cur = buff; *cur != '\0'; cur++) {
			// This is always the start of a word.
			char c = *cur;
			if (sentence_start) {
				if (isupper(c)) {
					sentence_start = false;
				} else if (islower(c)) {
					sentence_start = false;
					mistakes++;
				} 
			} 
			
			if (isalpha(c)) {
				while (isalpha(*++cur)) {
					if (isupper(*cur)) {
						mistakes++;
					}
				}
			}
			// we are not a the start of a sentence.
			char c2 = *cur;
			if (c2 == '.' || c2 == '?' || c2 == '!') {
				sentence_start = true;
			} 
		}
	}

	printf("%d\n", mistakes);
	return 0;
}
