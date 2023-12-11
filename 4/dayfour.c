#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define GAMES 204

typedef struct {
  int* winningNumbers;
  int winningNumbersLen;
  int* cardNumbers;
  int cardNumbersLen;
  int gameId;
} gameCard;

struct match_s 
{
    int value;
} match_default = {0};

typedef struct match_s match;

int main(void) {
  FILE* fp;
  fp = fopen("./input.txt", "r");
  if (fp == NULL)
    return 1;
  
  gameCard games[GAMES];
  
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int gameID = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    gameCard currentGame;
    currentGame.winningNumbers = malloc(sizeof(int) * read);
    currentGame.cardNumbers = malloc(sizeof(int) * read);
    int winningNumbersIndex = 0;
    int cardNumbersIndex = 0;
      
    char gameDelim = ':';
    char numsDelim = '|';
    char* numbersPtr;
    char* leftoverNumbersPtr;
    
    char* cardId = strtok_r(line, &gameDelim, &numbersPtr);
    currentGame.gameId = gameID++;
    
    int ptrIndex = 0;
    char* winningNumbers = strtok_r(numbersPtr, &numsDelim, &leftoverNumbersPtr);
    while (winningNumbers[ptrIndex]) {
	if (isdigit(winningNumbers[ptrIndex])) {
	    int nextValue = atoi(*(winningNumbers + ptrIndex));
	    int size = floor (log10 (abs (nextValue))) + 1;
	    currentGame.winningNumbers[winningNumbersIndex++] = nextValue;
	    ptrIndex += size - 2;
	}
	++ptrIndex;
    }
    currentGame.winningNumbersLen = winningNumbersIndex;

    ptrIndex = 0;
    char* cardNumbers = strtok_r(NULL, &numsDelim, &leftoverNumbersPtr);
    while (cardNumbers[ptrIndex]) {
	if (isdigit(cardNumbers[ptrIndex])) {
	    int nextValue = atoi(*(cardNumbers + ptrIndex));
	    int size = floor (log10 (abs (nextValue))) + 1; 
	    currentGame.cardNumbers[cardNumbersIndex++] = nextValue;
	    ptrIndex += size - 2;
	}
	++ptrIndex;
    }
    currentGame.cardNumbersLen = cardNumbersIndex;

    games[gameID - 1] = currentGame;
  }

  fclose(fp);

  float sum = 0;
  for (int i=0; i<GAMES; ++i) {
      gameCard currentGame = games[i];
      printf("ID: %d\n", currentGame.gameId);
      int matches = 0;
      for(int j=0; j<currentGame.cardNumbersLen; ++j) {
	  int currentCardNum = currentGame.cardNumbers[j];
	  for (int k=0; k<currentGame.winningNumbersLen; ++k) {
	      int currentWinningNum = currentGame.winningNumbers[k];
	      if (currentCardNum == currentWinningNum) {
		  printf("%d and %d match\n", currentCardNum, currentWinningNum);
		  ++matches;
	      }
	  }
      }
      sum += pow(2, matches);
      printf("Score: %f\n", pow(2, matches));
  }
  printf("The sum of the games played is %f", sum);
  
  return 0;
}
