#include <stdio.h>
#include <stddef.h>
#include <regex.h>
#include <string.h>

#define GAMES 204

typedef struct {
  char* winningNumbers;
  char* cardNumbers;
  int gameId;
} gameCard;

typedef struct {
  int cardScore;
  int winningNumbers;
  int gameId;
} cardScore;

gameCard translateLineToGameCard(char*);

int main(void) {
  FILE* fp;
  fp = fopen("./input.txt", "r");
  if (fp == NULL)
    return 1;
  
  gameCard games[GAMES];
  
  char * line = NULL;
  size_t len = 0;
  ssize_t read;
  int gameCount = 0;
  while ((read = getline(&line, &len, fp)) != -1) {
    gameCard currentGame = translateLineToGameCard(line);
    printf("%d, %s, %s\n", currentGame.gameId, currentGame.winningNumbers, currentGame.cardNumbers);
    games[gameCount++] = currentGame;
  }

  fclose(fp);
  
  return 0;
}


gameCard translateLineToGameCard(char* line) {
  gameCard currentGame;
  regex_t gameReg;
  int regComp = regcomp(&gameReg, "Card\s*([^:]+):\s*([^|]+)\s*\|\s*([^|]+)$", REG_EXTENDED);

  regmatch_t gameMatches[4];
  regComp = regexec(&gameReg, line, 4, gameMatches, 0);
  if (!regComp) {
    size_t match_len = gameMatches[1].rm_eo - gameMatches[1].rm_so;

    char cardNumberStr[match_len + 1];
    strncpy(cardNumberStr, line + gameMatches[1].rm_so, match_len);
    cardNumberStr[match_len] = '\0';

    int cardNumber;
    sscanf(cardNumberStr, "%d", &cardNumber);                                                                                                                                            
    currentGame.gameId = cardNumber;

    match_len = gameMatches[2].rm_eo - gameMatches[2].rm_so;
    char winningNumbers[match_len + 1];
    strncpy(winningNumbers, line + gameMatches[2].rm_so, match_len);
    winningNumbers[match_len] = '\0';
    currentGame.winningNumbers = &winningNumbers;

    match_len = gameMatches[3].rm_eo - gameMatches[3].rm_so;
    char gameNumbers[match_len + 1];
    strncpy(gameNumbers, line + gameMatches[3].rm_so, match_len);
    gameNumbers[match_len] = '\0';
    currentGame.cardNumbers = &gameNumbers;
  }
  
  regfree(&gameReg);
  return currentGame;
}
