#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define ROWS 140
#define COLS 141

FILE* getFilePointer(char*);
char* getRowsAndColumns(FILE*);
char* calculateNeighbors(int, int);
int bufferContainsSymbol(char*);

char* schematicMatrix;

int main(void) {
  FILE* fp = getFilePointer("./input.txt");

  schematicMatrix = getRowsAndColumns(fp);

  fclose(fp);

  int schematicSum = 0;
  for (int i=0; i<ROWS; ++i) {
    for (int j=0; j<COLS; ++j) {
      char currentVal = schematicMatrix[i * COLS + j];
      if (isdigit(currentVal)) {
	int candidate = atoi(schematicMatrix + (i * COLS + j));
	int candidateLength = floor (log10 (abs (candidate))) + 1;
	
	// For each digit, if has a symbol neighbor, add to sum
	for (int k=j; k<=j+candidateLength-1; k++) {
	  char* neighbors = calculateNeighbors(i, k);
	  if (bufferContainsSymbol(neighbors)) {
	    schematicSum += candidate;
	    break;
	  }
	  free(neighbors);
	}
	
	j += candidateLength - 1;
      }
    }
  }

  printf("The schematic sum is %d\n", schematicSum);

  return 0;
}

int bufferContainsSymbol(char* buf) {
  while(*buf) {
    if (!isdigit(*buf) && *buf != '.' && *buf != '\n' && *buf != '\0')
      return 1;
    ++buf;
  }
  return 0;
}

// rowIndx + 1, rowIndx - 1, colIndx + 1, colIndx - 1
char* calculateNeighbors(int rowIndx, int colIndx) {
  char* neighbors = malloc(sizeof(char) * 9);
  int neighborIndex = 0;
  for (int i=-1; i<=1; ++i) {
    for (int j=-1; j<=1; ++j) {
      int neighborRow = rowIndx + i;
      int neighborCol = colIndx + j;

      if (neighborRow <= 0 || neighborRow > ROWS)
        continue;
      if (neighborCol <= 0 || neighborCol > COLS)
	continue;
      if (i == 0 && j == 0)
	continue;

      char value = schematicMatrix[(rowIndx+i) * COLS + (colIndx+j)];
      neighbors[neighborIndex++] = value;
    }
  }
  neighbors[neighborIndex] = '\0';
  return neighbors;
}

char* getRowsAndColumns(FILE* fp) {
  char* matrix = malloc(sizeof(char) * ROWS * COLS);
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  
  int row = 0;
  while ((read = getline(&line, &len, fp)) != -1) {

    for (int i=0; i<len; ++i) {
      matrix[row * COLS + i] = line[i];
    }
    ++row;
  }
  
  return matrix;
}

FILE* getFilePointer(char* filePath) {
  FILE* fp;
  fp = fopen(filePath, "r");
  if (fp == NULL)
    return -1;
  return fp;
}
