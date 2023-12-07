#include <stdio.h>

long time = 38677673;
long distance = 234102711571236;

int main(void) {
  long minWinner = -1;
  long maxWinner = -1;
  for (long t=0; t<=time; ++t) {
    long currentDistance = t * (time - t);
    if (currentDistance > distance && minWinner == -1)
      minWinner = t;
    else if (currentDistance > distance && maxWinner < t)
      maxWinner = t;
  }
  printf("Min: %ld, Max: %ld, SD: %ld\n", minWinner, maxWinner, maxWinner - minWinner + 1);
  return 0;
}
