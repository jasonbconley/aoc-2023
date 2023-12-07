#include <stdio.h>

#define RACES 4

int times[RACES] = {38,67,76,73};
int distances[RACES] = {234,1027,1157,1236};

int main(void) {
  int standardDeviations = 1;
  for (int i=0; i<RACES; ++i) {
    int minWinner = -1;
    int maxWinner = -1;
    for (int t=0; t<=times[i]; ++t) {
      int currentDistance = t * (times[i] - t);
      if (currentDistance > distances[i] && minWinner == -1)
	minWinner = t;
      else if (currentDistance > distances[i] && maxWinner < t)
	maxWinner = t;
    }
    printf("Min: %d, Max: %d, SD: %d\n", minWinner, maxWinner, maxWinner - minWinner + 1);
    standardDeviations *= (maxWinner - minWinner + 1);
  }
  printf("Final SD: %d\n", standardDeviations);
}
