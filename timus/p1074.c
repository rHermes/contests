/*
 * p1074 - Very Short Problem
 *
 * I love these tasks!
 *
 * For now, I simply parse as much as a I can, within each function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// The end is not inclusive.
typedef struct {
	char *start;
	char *end;
} UnsignedIntegerNumber;

typedef struct {
	bool negative;
	UnsignedIntegerNumber* num;
} IntegerNumber;

typedef struct {
	UnsignedIntegerNumber *integ;
	UnsignedIntegerNumber *fract;
} SimpleUnsignedRealNumber;

typedef struct {
	bool negative;
	SimpleUnsignedRealNumber *num;
} SimpleRealNumber;

typedef struct {
	SimpleRealNumber *num;
	IntegerNumber *expo;
} RealNumber;


// Buffers: 
char buff[105];
char final_out[205];
char out_buff[205];

// Returns number of bytes read. if this is 0, then it's an invalid integer.
// If it's -1, then the integer might be all zero.
int read_UnsignedIntegerNumber(char* inp, UnsignedIntegerNumber* uin, bool shave) {
	uin->start = inp;
	for (; isdigit(*inp); inp++);
	uin->end = inp;
	
	int rc = uin->end - uin->start;
	
	if (shave) {
		// Now we trim off all, but the last zero.
		// Trim the zeroes.
		while (uin->start < uin->end-1) {
			if (*uin->start == '0') {
				uin->start++;
			} else {
				break;
			}
		}
	}

	return rc;
}

// Returns number of bytes read. If 0, we have an error.
int read_IntegerNumber(char* inp, IntegerNumber* integ) {
	int rc;
	int ret = 0;
	// First we check if we have a sign.
	char c = *inp;
	
	if (c == '+' || c == '-') {
		integ->negative = c == '-';
		ret++;
		inp++;
	} else {
		integ->negative = false;
	}

	rc = read_UnsignedIntegerNumber(inp, integ->num, true);
	if (rc < 1) {
		// We return 0;
		return 0;
	} else {
		return ret += rc;
	}
}  

int read_SimpleUnsignedRealNumber(char* inp, SimpleUnsignedRealNumber* num) {
	// We first test to see if we have a first one.
	if (*inp == '.') {
		// The first part must be NULLed then.
		num->integ = NULL;
		
		inp++;

		int rc = read_UnsignedIntegerNumber(inp, num->fract, false);
		if (rc < 1) {
			return 0;
		} else {
			return 1 + rc;
		}
	} else {
		// We now read in the first number.
		int rc = read_UnsignedIntegerNumber(inp, num->integ, true);
		if (rc < 1) {
			return 0;
		}
		inp += rc;

		if (*inp == '.') {
			inp++;
			int rc2 = read_UnsignedIntegerNumber(inp, num->fract, false);
			if (rc2 < 1) {
				return 0;
			} else {
				return 1 + rc + rc2;
			}
			
		} else {
			// WE must zero the second part.
			num->fract = NULL;

			return rc;
		}

	}
}

// Returns number of bytes read. If 0, we have an error.
int read_SimpleRealNumber(char* inp, SimpleRealNumber* num) {
	int rc;
	int ret = 0;
	// First we check if we have a sign.
	char c = *inp;

	if (c == '+' || c == '-') {
		num->negative = c == '-';
		ret++;
		inp++;
	} else {
		num->negative = false;
	}

	rc = read_SimpleUnsignedRealNumber(inp, num->num);
	if (rc < 1) {
		// We return 0;
		return 0;
	} else {
		return ret += rc;
	}
}  

int read_RealNumber(char* inp, RealNumber* real) {
	// We must always read a simple real number.
	int rc = read_SimpleRealNumber(inp, real->num);
	if (rc < 1) {
		return 0;
	}

	inp += rc;
	
	// We must now check if we are done, or if we have
	// an exponent.
	char c = *inp;
	if (c == '\0') {
		// We done, we just return.
		real->expo = NULL;
		return rc;
	} else if (c != 'E' && c != 'e') {
		// This is an error, since we need an integer
		// or an exponent here.
		return 0;
	}

	inp++;
	int rc2 = read_IntegerNumber(inp, real->expo);
	if (rc2 < 1) {
		return 0;
	} else {
		inp += rc2;

		if (*inp != '\0') {
			return 0;
		}

		return 1 + rc + rc2;
	}
}

// We always need to read a simple real number.

// This is a more brutish approach.
char* format_real_simple_simple(RealNumber *real, int N) {
	// first we copy file to buf.
	int point = 0;
	char *outp = out_buff;

	bool all_zero = true;
	bool negative = false;

	SimpleRealNumber *srn = real->num; 
	SimpleUnsignedRealNumber *surn = srn->num; 
	negative = srn->negative;

	if (surn->integ != NULL) {
		char *start = surn->integ->start;
		char *end = surn->integ->end;

		while (start < end) {
			*outp++ = *start++;
			point++;
		}
	} 

	if (surn->fract != NULL) {
		char *start = surn->fract->start;
		char *end = surn->fract->end;

		while (start < end) {
			*outp++ = *start++;
		}
	}

	if (real->expo != NULL && *real->expo->num->start != '0') {
		IntegerNumber *expo = real->expo;

		// one thing that is important here, is that since the output cannot be more
		// than 200 symbols long, so if the exponent is larger than 201, then this
		// wont work.
		// This is positive or -1 if it's extreme value.
		
		int	expo_int = -999;
		if (expo->num->end - expo->num->start <= 5) {
			char *start = expo->num->start;
			char *end = expo->num->end;
			
			// Convert to int.
			expo_int = 0;
			while (start < end) {
				expo_int = expo_int*10 + (*start - '0');
				start++;
			}
			
			if (expo->negative) {
				expo_int = -expo_int;
			}
		}

		// we simply add this to the point.
		point += expo_int;
	}

	final_out[0] = '-';
	char *fpout = final_out+1;
	char *finp = out_buff;
	// Now we copy to the final output.
	if (point > 0) {
		// The point is not negative.
		// we always print the first character.

		while (point > 0) {
			if (finp < outp) {
				if (all_zero && *finp == '0') {
					finp++;
				} else {
					all_zero = false;
					*fpout++ = *finp++;
				}
			} else {
				if (!all_zero) {
					*fpout++ = '0';
				}
			}
			point--;
		}

		// Now that we are here, if we are all_zero and haven't written anything, we write a 0.
		if (all_zero) {
			*fpout++ = '0';
		}

		// Now we just print the stuff behind the zero.
		if (N > 0) {
			*fpout++ = '.';
			while (N > 0) {
				if (finp < outp) {
					if (*finp != '0') {
						all_zero = false;
					}
					*fpout++ = *finp++;
				} else {
					*fpout++ = '0';
				}
				N--;
			}
		}
	}  else {
		// the point is beyond the first number, so we start of with 0.
		*fpout++ = '0';

		if (N > 0) {
			*fpout++ = '.';
			while (N > 0) {
				if (point < 0) {
					*fpout++ = '0';
					point++;
				} else if (finp < outp) {
					if (*finp != '0') {
						all_zero = false;
					}
					*fpout++ = *finp++;
				} else {
					*fpout++ = '0';
				}

				N--;
			}
		}
	}

	// The ending on the cake.
	*fpout = '\0';
	
	// if we are not all zero and the real part had a negative prefix, we can
	// simply use that.
	if (negative && !all_zero) {
		return final_out;
	} else {
		return final_out+1;
	}
}

int main() {
	while ((fgets(buff, sizeof(buff), stdin)) != NULL) {
		// Read the start of the character.
		// Now we read the number.
		int N;
		scanf("%d%*[\n]", &N);
		
		// ok, we try again, this time, removing the spaces.
		// char *wow = trimwhitespace(buff);
		char *wow = buff;
		wow[strlen(wow)-1] = '\0';
		
		if (wow[0] == '#' && wow[1] == 0) {
			return 0;
		}

		 // printf("INPUT FLOAT: %d | %s\n", N, wow);


		// now we just need to read the things. 
		// This is made somewhat harder by the fact that I chose to be so idiotic about these things.

		// We allocate for the worst.
		// Real Number = simple real number + exponent
		//
		UnsignedIntegerNumber expo_unsigned, integ_part, fract_part;
		
		IntegerNumber expo_part;
		expo_part.num = &expo_unsigned;

		SimpleUnsignedRealNumber simple_unsigned_part;
		simple_unsigned_part.integ = &integ_part;
		simple_unsigned_part.fract = &fract_part;

		SimpleRealNumber simple_real_part;
		simple_real_part.num = &simple_unsigned_part;

		RealNumber real;
		real.num = &simple_real_part;
		real.expo = &expo_part;

		int rc = read_RealNumber(wow, &real);
		if (rc < 1) {
			printf("Not a floating point number\n");
		} else {
			printf("%s\n", format_real_simple_simple(&real, N));
		}
	}
}
