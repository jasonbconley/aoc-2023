#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int calibration = 0;

typedef struct {
  char* word;
  int val;
} wordNum;

wordNum wordsToNums[10] = {
  { "one", 1 },
  { "two", 2 },
  { "three", 3 },
  { "four", 4 },
  { "five", 5 },
  { "six", 6 },
  { "seven", 7 },
  { "eight", 8 },
  { "nine", 9 },
  { "ten", 10 }
};

int transformWordsToNumbers(char* line) {
  for (int i=0; i<10; ++i) {
     if (strncmp(line, wordsToNums[i].word, strlen(wordsToNums[i].word)) == 0)
       return wordsToNums[i].val;
  }
  return 0;
}

void calibrateLeftMostAndRightMost(char* line) {
  uint32_t left = -1;
  uint32_t right = -1;

  for (int i=0; i<strlen(line); ++i) {
    int candidateWordToInt = transformWordsToNumbers(line + i);
    if (isdigit(line[i])) {
       char num = line[i];
       if (left == -1) {
         left = atoi(&num);
         right = atoi(&num);
       }
       else {
         right = atoi(&num);
       }
    }
    else if (candidateWordToInt != 0) {
      if (left == -1) {
	left = candidateWordToInt;
	right = candidateWordToInt;
      }
      else {
	right = candidateWordToInt;
      }
    }
  }
  calibration += (left * 10) + right;
}

int main(void) {
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
   
    fp = fopen("./input.txt", "r");
    if (fp == NULL)
        return -1;
    
    while ((read = getline(&line, &len, fp)) != -1) {
      calibrateLeftMostAndRightMost(line);
    }

    printf("The calibration is %d\n", calibration);
    
    fclose(fp);
    return 0;
}
