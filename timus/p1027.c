/*
 * p1027 - D++ Again
 *
 * This is a fun little parser challenge. I'll just write a simple state parser.
 */

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <ctype.h>

char buffer[10001];

int main() {
	// We read in.
	size_t in_size = fread(buffer, sizeof(char), 10000, stdin);
	// This saves us from doing buffer overflow checks.
	buffer[in_size+1] = '\0';
	
	// These are the only 3 variables we need.
	char *cur = buffer;
	bool in_comment = false;
	int32_t arith_level = 0;

	char *end = buffer+in_size;

	while (cur < end) {
		if (in_comment) {
			if (*cur == '*' && *(cur+1) == ')') {
				in_comment = false;
				cur++;
			}
		} else if (arith_level > 0) {
			if (*cur == '(') {
				if (*(cur+1) == '*') {
					in_comment = true;
					cur++;
				} else {
					arith_level++;
				}
			} else if (*cur == ')') {
				arith_level--;
			} else {
				if (!(isdigit(*cur) 
							|| *cur == '\n' || *cur == '+' 
							|| *cur == '=' || *cur == '-'
							|| *cur == '*' || *cur == '/' )) {
					// Very wrong.
					break;
				}
			}
		} else {
			// we can check for error right here.
			if (*cur == ')') {
				arith_level = -1;
				break;
			}
			if (*cur == '(') {
				if (*(cur+1) == '*') {
					in_comment = true;
					cur++;
				} else {
					arith_level++;
				}
			}
		}
		cur++;
	}

	// If we got this far, we must now check that we are of a sane state,
	// and if we are, then we got it.
	if (!in_comment && arith_level == 0) {
		printf("YES\n");
	} else {
		printf("NO\n");
	}

	return 0;
}
