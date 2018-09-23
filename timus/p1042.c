/*
 * p1042 - Central Heating
 *
 * So this is basically a linear equation, in Z/2, you could also see it as a
 * linear equation with boolean constontants.
 *
 * In our matrix, the columns are technicians and the rows are valves.
 *
 * Since we can replace no technican with any other, it means they are linearly
 * independent, so there will always be one and only one solution to this question.
 *
 * There is a method named as "The Four Russians" method for doing this slightly
 * faster, but I'm going to go with a normal Gaussian elimination.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 250

// in the matrix, the columns are technicans.
// We need one more row, because that will be the agumented row where everything is right.
bool matrix[MAX_N][MAX_N+1];
bool* rows[MAX_N];

// Translated straight from the pseudocode at wikipedia
void gauss(const int N) {
  int h = 0;
  int k = 0;

  // update the rows to work.
  // find the largest
  while (h < N && k < N+1) {
    int i_max;
    for (i_max = h; i_max < N && !rows[i_max][k]; i_max++) {}

    if (!rows[i_max][k]) {
      k++;
    } else {
      // Swap the two rows.
      bool* tmp = rows[h];
      rows[h] = rows[i_max];
      rows[i_max] = tmp;


      // Changing this slightly, we can start at 0, that way we get gaussian elimination
      //     for (int i = h+1; i < N; i++) {
      for (int i = 0; i < N; i++) {
        // if the pivot position is not true, we don't need to do anything.
        if (i != h && rows[i][k]) {
          rows[i][k] = false;

          for (int j = k+1; j < N+1; j++) {
            rows[i][j] = rows[i][j] ^ rows[h][j];
          }
        }
      }

      h++;
      k++;
    }
  }
}

int main() {
  // Initialize this to be a pointer to each row. That way, we can swap the rows quickly.
  int N;
  scanf("%d", &N);

  // Loop through all technicians
  for (int i = 0; i < N; i++) {
    int j;
    scanf("%d", &j);
    while (j > -1) {
      matrix[j-1][i] = true;
      scanf("%d", &j);
    }

    // Since we also have also have to loop through the array for the last
    // column and the rows to matrix, we do that here.
    // In the agumented matrix, the last column is always true 
    matrix[i][N] = true;
    rows[i] = matrix[i];
  }

  gauss(N);

  // Here we print out the ones which we need.
  for (int i = 0; i < N; i++) {
    if (rows[i][N]) {
      printf("%d ", i+1);
    }
  }

  printf("\n");

  return 0;
}
