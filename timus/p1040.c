/*
 * p1040 - Airline Company
 *
 * The trick here is that gcd(x, x+1) == 1 and so a chain which goes through
 * all nodes will always work, since we must have entered and exited the node
 * with an x and x+1
 */

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>


// We calculate the MAX_NN by summing up the amount of flights with ((MAX_N-1)*(MAX_N-1+1))/2, which is 1225 in this case.
#define MAX_N 50
#define MAX_NN 1225

#define max(x,y) ( \
    { __auto_type __x = (x); __auto_type __y = (y); \
      __x > __y ? __x : __y; })



// The answer is the tail number
int flights[MAX_NN][2];
int answers[MAX_N][MAX_N];

bool is_flight[MAX_N][MAX_N];
bool is_done[MAX_N];


// Dfs starting at node x.

int N, M;
int cur_flight = 0;

void dfs(const int x) {
  is_done[x] = true;
  for (int i = 0; i < N; i++) {
    // Has there been a flight and if so, have we evaluated it yet?
    if (is_flight[x][i] && answers[x][i] == 0) {
      cur_flight++;
      answers[x][i] = cur_flight;
      answers[i][x] = cur_flight;

      // if we haven't done the destination we jump to it.
      if (!is_done[i]) {
        dfs(i);
      }
    }
  }
}

int main() {
  scanf("%d%d", &N, &M);
  int p, q;
  for (int i = 0; i < M; i++) {
    scanf("%d%d", &p, &q);
    // Record to and from the flights.
    flights[i][0] = p-1;
    flights[i][1] = q-1;

    // record if there was a flight
    is_flight[p-1][q-1] = true;
    is_flight[q-1][p-1] = true;
  }

  // We now search the first node.
  dfs(0);

  // we know that there is a solution
  printf("YES\n");
  for (int i = 0; i < M-1; i++) {
    printf("%d ", answers[flights[i][0]][flights[i][1]]);
  }
  printf("%d\n", answers[flights[M-1][0]][flights[M-1][1]]);
  return 0;
}

