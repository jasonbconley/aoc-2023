#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define COLORS_SIZE 3
char* colors[COLORS_SIZE] = {
  "red",
  "green",
  "blue"
};

typedef struct {
  int redDraw;
  int greenDraw;
  int blueDraw;
} set;

typedef struct { 
  set maxRedSet;
  set maxGreenSet;
  set maxBlueSet;
  int id;
} game;

game translateLineToGame(char* line, int lineId) {
  game currGame = {
    {0,0,0}, {0,0,0}, {0,0,0}, lineId
  };

  // Iterate passed the ID 
  while (*line && *line != '\0' && *line != '\n') {
    if (*line == ':') {
      ++line;
      break;
    }
    ++line;
  }

  // Iterate over the sets
  int i = 0;
  int numRed = 0;
  int numGreen = 0;
  int numBlue = 0;
  while (line[i]) {
    if (line[i] == ';' || line[i] == '\n' || line[i+1] == '\0') {
      set currentSet = { numRed, numGreen, numBlue };
      if (currGame.maxRedSet.redDraw < currentSet.redDraw) {
	currGame.maxRedSet = currentSet;
      }

      if (currGame.maxGreenSet.greenDraw < currentSet.greenDraw) {
	currGame.maxGreenSet = currentSet;
      }

      if (currGame.maxBlueSet.blueDraw < currentSet.blueDraw) {
	currGame.maxBlueSet = currentSet;
      }

      numRed = 0;
      numGreen = 0;
      numBlue = 0;
    }
    else if (isdigit(line[i])) {
      int numBalls = atoi(&line[i]);
      
      char* numAndColor = malloc(sizeof(char) * 256);
      int j = i;
      while (line[j] != ',' && line[j] != ';' && line[j] != '\0' && line[j] != '\n') ++j;
      strncpy(numAndColor, line + i, j - i);
      
      i += j - i;

      for (int i=0; i<COLORS_SIZE; ++i) {
	if (strstr(numAndColor, colors[i]) != NULL) {
	  if (i == 0)
	    numRed += numBalls;
	  else if (i == 1)
	    numGreen += numBalls;
	  else if (i == 2)
	    numBlue += numBalls;
	}
      }

      free(numAndColor);
      continue;
    }

    ++i;
  }

  return currGame;
  
}

int main(void) {
  int totalRed = 12;
  int totalGreen = 13;
  int totalBlue = 14;

  FILE * fp;
  char * line = NULL;
  size_t len = 0;
  ssize_t read;

  game gameResults[100];
 
  fp = fopen("./input.txt", "r");
  if (fp == NULL)
    return -1;
  
  int lineNum = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    gameResults[lineNum++] = translateLineToGame(line, lineNum);
  }
  fclose(fp);

  int gamePowerSums = 0;
  for (int i=0; i<100; ++i) {
    game currGame = gameResults[i];
    int maxRed, maxGreen, maxBlue;
    maxRed = currGame.maxRedSet.redDraw;
    maxGreen = currGame.maxGreenSet.greenDraw;
    maxBlue = currGame.maxBlueSet.blueDraw;

    printf("ID #%d: Max red %d, Max green %d, Max blue %d\n", currGame.id, maxRed, maxGreen, maxBlue);
    gamePowerSums += (maxRed * maxGreen * maxBlue);
  }

  printf("The sum of game powers are %d\n", gamePowerSums);
}
