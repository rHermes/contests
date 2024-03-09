/*
 * This program exists to answer a simple question, how many guesses does it take on average
 * to answer the question: "I'm thinking of a number between 0 and N, what number am I thinking of?".
 *
 * I know the worst case scenario for two strategies, but I want to see how the distribution
 * looks for the average case.
 */
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>
#include <cinttypes>
#include <map>

using UT = std::uint64_t;

UT guessWithSqrt(const std::size_t N, const std::size_t answer) {
	std::size_t lo = 0;
	std::size_t hi = N+1;

	UT guesses = 0;
	while (lo+1 < hi) {
		const std::size_t blockSize = static_cast<std::size_t>(std::ceil(std::sqrt(hi-lo)));
		while (lo+1 < hi) {
			auto curGuess = lo + blockSize - 1;
			guesses++;

			if (curGuess == answer) {
				return guesses;
			} else if (answer < curGuess) {
				hi = curGuess;
				break;
			} else {
				lo += blockSize;
			}
		}
	}
	if (lo != answer)
		throw std::runtime_error("WTF HAPPENED HERE");

	return guesses;
}

UT guessWithOneSqrt(const std::size_t N, const std::size_t answer) {
	std::size_t lo = 0;
	std::size_t hi = N+1;
	const std::size_t blockSize = static_cast<std::size_t>(std::ceil(std::sqrt(hi-lo)));

	UT guesses = 0;
	while (lo+1 < hi) {
		auto curGuess = lo + blockSize - 1;
		guesses++;

		if (curGuess == answer) {
			return guesses;
		} else if (answer < curGuess) {
			hi = curGuess;
			break;
		} else {
			lo += blockSize;
		}
	}

	
	guesses += answer - lo + 1;
	return guesses;
}

UT guessWithBinary(const std::size_t N, const std::size_t answer) {
	std::size_t lo = 0;
	std::size_t hi = N+1;

	UT guesses = 0;
	while (lo+1 < hi) {
		auto mid = (lo + hi) / 2;
		guesses++;

		if (mid == answer) {
			return guesses;
		} else if (answer < mid) {
			hi = mid;
		} else {
			lo = mid;
		}
	}

	if (lo != answer)
		throw std::runtime_error("WTF HAPPENED HERE");

	return guesses;
}

void runTestCase(const std::size_t N) {
	std::random_device dev;
	std::mt19937_64 gen(dev());
	std::uniform_int_distribution<std::size_t> guessDist(0, N);


	std::map<UT,UT> binGuesses;
	std::map<UT,UT> sqrtGuesses;
	std::map<UT,UT> oneSqrtGuesses;

	constexpr std::size_t numberOfRuns = 10'000'000;
	for (std::size_t runNum = 0; runNum < numberOfRuns; runNum++) {
		auto answer = guessDist(gen);

		binGuesses[guessWithBinary(N, answer)]++;
		sqrtGuesses[guessWithSqrt(N, answer)]++;
		oneSqrtGuesses[guessWithOneSqrt(N, answer)]++;
	}
	
	std::cout << "Distribution for binary search (lg2(N)=" << std::log2(N) << "):" << std::endl;
	UT bgSum = 0;
	for (const auto& [numGuesses, hits] : binGuesses) {
		bgSum += numGuesses * hits;
		double frac = static_cast<double>(hits) / static_cast<double>(numberOfRuns);
		std::cout << std::setw(2) << numGuesses << ": " << std::setw(8) << hits << " which is " 
			<< std::fixed << std::setprecision(3) << std::setw(7) <<  100*frac <<  std::endl;
	}

	std::cout << "Average guess: " << bgSum / numberOfRuns << std::endl;

	const std::size_t blockSize = static_cast<std::size_t>(std::ceil(std::sqrt(N)));
	std::cout << "Distribution for sqrt search (SQRT is " << blockSize << "):" << std::endl;
	UT sqrtSum = 0;
	for (const auto& [numGuesses, hits] : sqrtGuesses) {
		sqrtSum += numGuesses * hits;
		/* double frac = static_cast<double>(hits) / static_cast<double>(numberOfRuns); */
		/* std::cout << std::setw(2) << numGuesses << ": " << std::setw(8) << hits << " which is " */ 
		/* 	<< std::fixed << std::setprecision(3) << std::setw(7) <<  100*frac <<  std::endl; */
	}

	std::cout << "Average guess: " << sqrtSum / numberOfRuns << std::endl;

	std::cout << "Distribution for one sqrt search (SQRT is " << blockSize << "):" << std::endl;
	UT oneSqrtSum = 0;
	for (const auto& [numGuesses, hits] : oneSqrtGuesses) {
		oneSqrtSum += numGuesses * hits;
		/* double frac = static_cast<double>(hits) / static_cast<double>(numberOfRuns); */
		/* std::cout << std::setw(2) << numGuesses << ": " << std::setw(8) << hits << " which is " */ 
		/* 	<< std::fixed << std::setprecision(3) << std::setw(7) <<  100*frac <<  std::endl; */
	}

	std::cout << "Average guess: " << oneSqrtSum / numberOfRuns << std::endl;
}


int main() {
	runTestCase(10'000);
	return 0;
}
