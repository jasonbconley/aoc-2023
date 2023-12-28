#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x;
  int y;
} galaxy;

int main(void) {
  
  FILE* fp = fopen("./input.txt", "r");                                                                                                                                                                          
  char * line = NULL;                                                                                                                                                                                            
  size_t len = 0;                                                                                                                                                                                                
  ssize_t read;                                                                                                                                                                                                  

  int lineCount = 0;
  int maxGalaxyLine = 0;
  size_t numGalaxies = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    int noGalaxies = 1;
    for (ssize_t i = 0; i <= read; ++i) {
      if (line[i] == '#') {
	++numGalaxies;
	noGalaxies = 0;
      }
    }
    if (noGalaxies && (int) read > maxGalaxyLine)
      maxGalaxyLine = read;
    lineCount++;
  }
  rewind(fp);

  int expansion = maxGalaxyLine * 2;
  char matrix[lineCount][expansion];

  size_t lineIndex = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    size_t nonExpansion = (expansion - read) / 2;
    
    for (size_t a = 0; a < nonExpansion; ++a) {
      matrix[lineIndex][a] = '.';
    }
    for (ssize_t i = nonExpansion; i <= read + (ssize_t) nonExpansion; ++i) {
      matrix[lineIndex][i] = line[i];
    }
    for(int b = (int) read + nonExpansion + 1; b < expansion; ++b) {
      matrix[lineIndex][b] = '.';
    }
    ++lineIndex;
  }
  fclose(fp);

  galaxy galaxies[numGalaxies];
  size_t currentGalaxyIndx = 0;
  for (int i = 0; i < lineCount; ++i) {
    for (int j = 0; j < expansion; ++j) {
      if (matrix[i][j] == '#') {
	galaxy currentGalaxy = { .x = j, .y = i };
	galaxies[currentGalaxyIndx++] = currentGalaxy;
      }
    }
  }

  int shortestPathSum = 0;
  for (size_t i = 0; i < numGalaxies; ++i) {
    for (size_t j = i; ++j < numGalaxies;) {
      if (i != j) {
	galaxy left = galaxies[i];
	galaxy right = galaxies[j];

	int manhattan = abs(left.x - right.x) + abs(left.y - right.y);

	shortestPathSum += manhattan;
      }
    }
  }

  for (size_t i = 0; i < numGalaxies; ++i) {
    printf("%d, %d\n", galaxies[i].x, galaxies[i].y);
  }

  printf("Num galaxies is %zu and should be %d\n", currentGalaxyIndx, numGalaxies);
  printf("The sum is %d\n", shortestPathSum);
  
  return 0;
}

long factorial(int n)  
{  
  if (n == 0)  
    return 1;  
  else  
    return(n * factorial(n-1));  
}  
