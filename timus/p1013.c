/*
 *  p. 1013 - K-based Numbers. Version 3
 *
 *  This is just a copy of my solution to p. 1009.
 *
 *  If you tinker with the equation for a bit, you can spot that it follows
 *  the following recurrence equation:
 *
 *  F(N) = (K-1) * F(N-1) + (K-1) * F(N-2) = (F(N-1) + F(N-2)) * (K-1)
 *
 *  The reason for this is not that hard to understand. When we add a new digit
 *  space, that slot can have (K-1) values, remember it cannot be 0. We can combine
 *  these (K-1) possibilites with all the sequences we found for F(N-1). The
 *  problem is that F(N-1) doesn't account for the scenarios where the first
 *  digit is 0. With this possibility, there are F(N-2) possible new sequences,
 *  that we have to add.
 *
 *  Looking at this function, you can see that it closely resembles the Fibonacci
 *  sequence. One of the fastest way to calculate this sequence is to convert it
 *  to matrix form[1].
 *
 *  The way to envision this is to say that we have:
 *
 *  L(N) = { { F(N+1), F(N) }, { F(N), F(N-1) } }
 *
 *  We want to find a matrix R such that:
 *
 *  L(N) * R = L(N+1)
 *
 *  It is easy to deduct that R must be:
 *
 *  R = { { K-1, 1 }, { K-1, 0 } }
 *
 *  Knowing this gives us the fact that
 *
 *  L(N) = L(1) * R^(N-1)
 *
 *  It is worth noteing that we only have to find L(N-1) to find F(N),
 *  as it will be included in the matrix.
 *
 *  If we do the matrix exponation in the form of exponentation by squaring,
 *  we now have O(log(n)) operations.
 *
 *  The L(1) part is equal to:
 *
 *  L(1) = { { K*(K-1), K-1 }, { K-1, 1} }
 *
 *  An implementation of this in mathematica then is as simple as:
 *
 *  F[N_,K_] := ({{K*(K-1), K-1},{K-1, 1}}.MatrixPower[{{K-1,1},{K-1,0}}, N-2])[[1,1]] 
 *
 *  All output values will be within reason, so what we do is that we, use
 *  modular exponention on matrixes, to find it. This works, in 99%
 *  of cases, since 10^18 fits into uint64_t.
 *
 *  We have a test case for when it doesn't where we use russian peasant multiplication[2]
 *  which gives us the ability to do this. This is slower than we want to, but it works
 *  everytime. I have no idea how people could optimize this further, other than to
 *  simply manage to avoid using modulu in most cases.
 *
 *  A fast implementation of this version of the algorithm in mathematica is:
 *
 *  F[N_, K_, M_] := Mod[
 *  Mod[{{K*(K - 1), K - 1}, {K - 1, 1}}, M]
 *    .
 *    Algebra`MatrixPowerMod[{{K - 1, 1}, {K - 1, 0}}, N - 2, M], 
 *  M][[1, 1]]
 *
 *
 *  [1]: https://www.nayuki.io/page/fast-fibonacci-algorithms
 *  [2]: http://mathforum.org/dr.math/faq/faq.peasant.html
 */

#include <stdio.h>
#include <stdint.h>
#include <math.h>

// This is because my machine uses slightly different scanners than the
// online judge.
#ifdef ONLINE_JUDGE
	#define LONG_SCAN "%llu"
#else
	#define LONG_SCAN "%lu"
#endif

#define TT uint64_t

// We can have multiple versions of this, with varing degrees of mod-ness.
// This calculates the mat_mod normally and returns it in the o parameters.
void mat_mod_norm(TT a11, TT a12, TT a21, TT a22, TT b, TT c, TT *o11, TT *o12, TT *o21, TT *o22) {
	// Before being passed in here A is % C
	if (b == 0) {
		// This is the same as the identity matrix.
		*o11 = 1;
		*o12 = 0;
		*o21 = 0;
		*o22 = 1;
	} else if (b % 2 == 1) {
		TT d11, d12, d21, d22;

		// calculate the new mod.
		mat_mod_norm(a11,a12,a21,a22, b - 1, c, &d11, &d12, &d21, &d22);  

		// Now we should set the output to (A * D) mod C 

		// Get the output
		*o11 = (a11*d11 + a12*d21) % c;
		*o12 = (a11*d12 + a12*d22) % c;
		*o21 = (a21*d11 + a22*d21) % c;
		*o22 = (a21*d12 + a22*d22) % c;
	} else {
		// Here we create a matrix D,
		// and then we return it.
		TT d11, d12, d21, d22;
		
		// Here we calculate the norm.
		mat_mod_norm(a11,a12,a21,a22, b / 2, c, &d11, &d12, &d21, &d22);

		// Now we have to do D * D mod c and return that.
		// We actually don't have to do mod in the middle there,
		// because D * D is allready mod C, and so it would help
		// nothing to put it there.
		*o11 = (d11*d11 + d12*d21) % c;
		*o12 = (d11*d12 + d12*d22) % c;
		*o21 = (d21*d11 + d22*d21) % c;
		*o22 = (d21*d12 + d22*d22) % c;
	}
}

int just_works(TT N, TT K, TT M) {
	const TT KMM = (K-1) % M;

	TT d11, d12, d21, d22;

	// Here we calculate the norm.
	mat_mod_norm(KMM, 1 % M, KMM, 0, N-2, M, &d11, &d12, &d21, &d22);

	// Only part that is really important here, is the d11
	//
	// Now we get the answer by doing.
	TT ans = (((((K%M)*KMM)%M) * d11)%M + ((KMM * d21 ) % M)) % M;
	printf(LONG_SCAN "\n", ans);
	return 0;
}



// A method to multiply two numbers using Russian Peasant method
//
// returns a * b % c
//TT russianPeasant(TT a, TT b, TT c)
TT rip(TT a, TT b, TT c)
{
    TT res = 0;  // initialize result
 
    // While second number doesn't become 1
    while (b > 0)
    {
         // If second number becomes odd, add the first number to result
         if (b & 1)
             res = (res + a ) % c;
 
         // Double the first number and halve the second number
         a = (a << 1) % c;
         b = (b >> 1) % c;
     }
     return res;
}

// We can have multiple versions of this, with varing degrees of mod-ness.
// This calculates the mat_mod normally and returns it in the o parameters.
void mat_mod_rus(TT a11, TT a12, TT a21, TT a22, TT b, TT c, TT *o11, TT *o12, TT *o21, TT *o22) {
	// Before being passed in here A is % C
	if (b == 0) {
		// This is the same as the identity matrix.
		*o11 = 1;
		*o12 = 0;
		*o21 = 0;
		*o22 = 1;
	} else if (b % 2 == 1) {
		TT d11, d12, d21, d22;

		// calculate the new mod.
		mat_mod_rus(a11,a12,a21,a22, b - 1, c, &d11, &d12, &d21, &d22);  

		// Now we should set the output to (A * D) mod C 
		// Get the output
		*o11 = (rip(a11,d11,c) + rip(a12,d21,c)) % c;
		*o12 = (rip(a11,d12,c) + rip(a12,d22,c)) % c;
		*o21 = (rip(a21,d11,c) + rip(a22,d21,c)) % c;
		*o22 = (rip(a21,d12,c) + rip(a22,d22,c)) % c;
	} else {
		// Here we create a matrix D,
		// and then we return it.
		TT d11, d12, d21, d22;
		
		// Here we calculate the norm.
		mat_mod_rus(a11,a12,a21,a22, b / 2, c, &d11, &d12, &d21, &d22);

		// Now we have to do D * D mod c and return that.
		// We actually don't have to do mod in the middle there,
		// because D * D is allready mod C, and so it would help
		// nothing to put it there.
		*o11 = (rip(d11,d11,c) + rip(d12,d21,c)) % c;
		*o12 = (rip(d11,d12,c) + rip(d12,d22,c)) % c;
		*o21 = (rip(d21,d11,c) + rip(d22,d21,c)) % c;
		*o22 = (rip(d21,d12,c) + rip(d22,d22,c)) % c;
	}
}


int peasant_just_works(TT N, TT K, TT M) {
	const TT KMM = (K-1) % M;

	TT d11, d12, d21, d22;

	// Here we calculate the norm.
	mat_mod_rus(KMM, 1 % M, KMM, 0, N-2, M, &d11, &d12, &d21, &d22); 
	// Only part that is really important here, is the d11
	//
	// Now we get the answer by doing.
	TT ans = (rip(rip(K%M, KMM, M) , d11, M) + rip(KMM,d21,M)) % M;
	printf(LONG_SCAN "\n", ans);
	return 0;
}

// We take them in and then we decide what to do.
int main() {
	TT N, K, M;

	scanf(LONG_SCAN "\n" LONG_SCAN "\n" LONG_SCAN, &N, &K, &M);

	if (2*log2(M) > 63) {
		return peasant_just_works(N, K, M);
	}else {
		return just_works(N, K, M);
	}
}
