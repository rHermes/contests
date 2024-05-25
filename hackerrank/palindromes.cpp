#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::string
ltrim(const std::string&);
std::string
rtrim(const std::string&);

/*
 * Complete the 'solve' function below.
 *
 * The function is expected to return a DOUBLE.
 * The function accepts STRING s as parameter.
 */

using TT = double;

void
matReduce(std::vector<std::vector<TT>>& mat)
{
  const int ROWS = mat.size();
  const int COLS = mat[0].size();

  int pivotColumn = 0;
  int pivotRow = 0;

  while (pivotRow < ROWS && pivotColumn < COLS) {
    // first we pick from the available rows the largest one.
    auto maxAbs = std::abs(mat[pivotRow][pivotColumn]);
    int maxAbsIdx = pivotRow;

    for (int row = pivotRow + 1; row < ROWS; row++) {
      const auto posAbs = std::abs(mat[row][pivotColumn]);
      if (maxAbs < posAbs) {
        maxAbs = posAbs;
        maxAbsIdx = row;
      }
    }

    // Remember to use tolerances here
    if (maxAbs < 0.00000001) {
      // There are no pivots for this column, we continue
      pivotColumn++;
      continue;
    }

    // ok, let's swap us out with the best one
    std::swap(mat[pivotRow], mat[maxAbsIdx]);

    // now we are going to clear out the ones below us.
    for (int j = pivotRow + 1; j < ROWS; j++) {
      const auto factor = mat[j][pivotColumn] / mat[pivotRow][pivotColumn];

      // This is better than divding, because it makes the result more accurate.
      mat[j][pivotColumn] = 0;

      for (int k = pivotColumn + 1; k < COLS; k++) {
        mat[j][k] -= factor * (mat[pivotRow][k]);
      }
    }

    pivotColumn++;
    pivotRow++;
  }

  // std::cout << "We got to: " << pivotRow << " and " << pivotColumn << "\n";

  assert(pivotColumn == COLS - 1);
  assert(pivotRow = ROWS);

  // Ok, now we are going to do some backfilling.

  for (int row = ROWS - 1; 0 <= row; row--) {
    if (std::abs(mat[row][row]) < 0.0000001) {
      mat[row][COLS - 1] = 0;
      continue;
    }

    // we want to make this 1
    const TT factor = 1 / mat[row][row];
    mat[row][row] = 1;

    for (int col = row + 1; col < ROWS; col++) {
      mat[row][COLS - 1] -= mat[col][COLS - 1] * mat[row][col];
      mat[row][col] = 0;
    }

    mat[row][COLS - 1] *= factor;
  }
}

// We do this to reduce the number of states as much as possible.
void
cleanIt(std::string& s)
{
  std::unordered_map<char, char> mp;
  char cur = 'a';
  for (char& c : s) {
    auto it = mp.emplace(c, cur);
    if (it.second)
      cur++;

    c = it.first->second;
  }
}

std::unordered_map<std::string, double> cache_{};

double
solve(std::string s)
{
  cleanIt(s);
  if (auto it = cache_.find(s); it != cache_.end()) {
    return it->second;
  }

  const int N = s.size();
  // we could just do the recursion, but I want this with real answers!

  const auto isPalin = [](const std::string_view sv) {
    int i = 0;
    int j = sv.size() - 1;
    while (i < j) {
      if (sv[i++] != sv[j--])
        return false;
    }

    return !sv.empty();
  };

  if (isPalin(s)) {
    cache_[s] = 0;
    return 0;
  }

  // We are going to be building our matrix. First we need to build all the setup.

  // we begin by sorting, since we want the full permutaiton space.
  std::unordered_map<std::string, int> comp;
  comp[s] = 0;

  int numPalin = 0;

  // we want the full permutation space.
  std::sort(s.begin(), s.end());
  do {
    if (isPalin(s)) {
      numPalin++;
      continue;
    }

    // we still have to clean the output, as we might have gotten a swap.
    auto pt = s;
    cleanIt(pt);

    comp.emplace(pt, comp.size());

  } while (std::next_permutation(s.begin(), s.end()));

  if (numPalin == 0) {
    for (const auto& [str, id] : comp) {
      cache_[str] = std::numeric_limits<double>::quiet_NaN();
    }
    return std::numeric_limits<double>::quiet_NaN();
  }

  std::cout << "We have " << std::setw(5) << comp.size() << " unique non palindrome states for: " << s << "\n";
  // We are going to build a matrix and do schults elimination in it to solve it.
  const int ROWS = comp.size();
  const int COLS = ROWS + 1;

  // Now we build our array
  std::vector<std::vector<TT>> mat(ROWS, std::vector<TT>(COLS));

  // Now we will build the matrix.
  for (const auto& [str, id] : comp) {
    // The sum is always going to be one.
    /* mat[id][ROWS] = 1; */
    std::string ss = str;

    // we also add ourselves one here, because we are trying to figure ourselves out.
    int total = 0;
    for (int i = 0; i < N - 1; i++) {
      for (int j = i + 1; j < N; j++) {
        total++;

        std::swap(ss[i], ss[j]);
        auto pt = ss;
        cleanIt(pt);

        auto it = comp.find(pt);
        std::swap(ss[i], ss[j]);

        if (it == comp.end()) {
          continue;
        }

        --mat[id][it->second];
      }
    }

    // We now multiply the end with the count. This is better than spending time here
    // dividing all the ones before.
    mat[id][id] += total;
    mat[id][COLS - 1] = total;
  }
	
	// We now reduce the matrix to solve it.
  matReduce(mat);

  // ok, now I want to cache the answer for all the ids we have.
  for (const auto& [str, id] : comp) {
    cache_[str] = mat[id][COLS - 1];
  }

  return mat[0][COLS - 1];
}

int
main()
{
  std::ofstream fout(getenv("OUTPUT_PATH"));

  std::string t_temp;
  std::getline(std::cin, t_temp);

  int t = stoi(ltrim(rtrim(t_temp)));

  for (int t_itr = 0; t_itr < t; t_itr++) {
    std::string s;
    std::getline(std::cin, s);

    double result = solve(s);

    fout << std::fixed << std::setprecision(4) << result << "\n";
  }

  fout.close();

  return 0;
}

std::string
ltrim(const std::string& str)
{
  std::string s(str);

  s.erase(s.begin(), find_if(s.begin(), s.end(), [](const char c) { return !std::isspace(c); }));

  return s;
}

std::string
rtrim(const std::string& str)
{
  std::string s(str);

  s.erase(find_if(s.rbegin(), s.rend(), [](const char c) { return !std::isspace(c); }).base(), s.end());

  return s;
}
