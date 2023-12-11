#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define ROWS 140
#define COLS 141

typedef struct {
  int numberOne;
  int numberTwo;
  int isValid;
} gearRatio;

FILE* getFilePointer(char*);
char* getRowsAndColumns(FILE*);
gearRatio calculateGearRatio(int, int);

char* schematicMatrix;

int main(void) {
  FILE* fp = getFilePointer("./input.txt");

  schematicMatrix = getRowsAndColumns(fp);

  fclose(fp);

  int gearRatioSum = 0;
  for (int i=0; i<=ROWS; ++i) {
    for (int j=0; j<=COLS; ++j) {
      char currentVal = schematicMatrix[i * COLS + j];
      if (currentVal == '*') {
	gearRatio currentRatio = calculateGearRatio(i, j);
	if (currentRatio.isValid)
	  gearRatioSum += (currentRatio.numberOne * currentRatio.numberTwo);
      }
    }
  }

  printf("The gear ratio sum is %d\n", gearRatioSum);

  return 0;
}

gearRatio calculateGearRatio (int rowIndx, int colIndx) {
  gearRatio currentRatio;
  currentRatio.numberOne = -1;
  currentRatio.numberTwo = -1;
  currentRatio.isValid = 0;

  for (int i=-1; i<=1; ++i) {
    for (int j=-1; j<=1; ++j) {
      int neighborRow = rowIndx + i;
      int neighborCol = colIndx + j;

      if (neighborRow < 0 || neighborRow > ROWS)
        continue;
      if (neighborCol < 0 || neighborCol > COLS)
	continue;
      if (i == 0 && j == 0)
	continue;

      char value = schematicMatrix[neighborRow * COLS + neighborCol];
      if (isdigit(value)) {
	int digitCol=neighborCol;
	while (digitCol >= 0 && isdigit(schematicMatrix[neighborRow * COLS + digitCol])) {
	  digitCol -= 1;
	}
	digitCol += 1;

	int candidate = atoi(schematicMatrix + (neighborRow * COLS + digitCol));
	int size = floor(log10(abs(candidate))) + 1;

	if (currentRatio.numberOne == -1)
	  currentRatio.numberOne = candidate;
	else if (currentRatio.numberTwo == -1) {
	  currentRatio.numberTwo = candidate;
	  currentRatio.isValid = 1;
	}
	else
	  currentRatio.isValid = 0;

	if (i != 0 && digitCol + size - 1 <= COLS && digitCol + size - 1 > neighborCol)
	  j = digitCol + size - 1;
      }
    }
  }
  return currentRatio;
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
