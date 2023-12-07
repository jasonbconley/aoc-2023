#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

#define BUF_SIZE 100000
#define SEED_SIZE 20
#define NUM_MAPS 7

char* maps[] = {
  "seed-to-soil map:\n", "soil-to-fertilizer map:\n",
  "fertilizer-to-water map:\n", "water-to-light map:\n",
  "light-to-temperature map:\n", "temperature-to-humidity map:\n",
  "humidity-to-location map:\n"
};

size_t getLineCount(FILE*);

int main(void) {
    FILE * fp;
    fp = fopen("./input.txt", "r");
    if (fp == NULL)
      return -1;

    size_t lineCount = getLineCount(fp);
    char** lines = malloc(sizeof(char*)* lineCount - 1);
    for(size_t i = 0; i < lineCount; ++i){
        size_t size = 256;
        lines[i] = malloc(size);
        getline(&lines[i], &size, fp);
    }
    fclose(fp);

    //Get seeds
    long* seeds = malloc(sizeof(long) * SEED_SIZE);
    char* seedLine = lines[0];
    int seedCounter = 0;
    while(*seedLine) {
      if (isdigit(*seedLine)) {
	  long digit = atol(seedLine);
	  seeds[seedCounter++] = digit;
	  while (isdigit(*seedLine)) ++seedLine; 
      }
      ++seedLine;
    }


    // Move over the maps and store the locations for each seed
    long* seedLocations = malloc(sizeof(long) * SEED_SIZE);
    for (int sd = 0; sd<SEED_SIZE; ++sd) {
      size_t line = 1;
      seedLocations[sd] = seeds[sd];
      for (int i=0; i<NUM_MAPS; ++i) {
	while (lines[line] && !strcmp(lines[line], maps[i]) == 0) ++line;
	++line;

	while(line < lineCount && isdigit(lines[line][0])) {
	  char* currentSpec = lines[line++];
	  long destStart, sourceStart, range;
	  sscanf(currentSpec, "%ld %ld %ld", &destStart, &sourceStart, &range);
	  if (seedLocations[sd] >= sourceStart && seedLocations[sd] <= sourceStart + range - 1) {
	    seedLocations[sd] = seedLocations[sd] + (destStart - sourceStart);
	    break;
	  }
	}
      }
    }

    long smallestLocation = seedLocations[0];
    for (int i=0; i<SEED_SIZE; ++i) {
      if (seedLocations[i] < smallestLocation)
	smallestLocation = seedLocations[i];
    }
    printf("The closest seed location is %ld\n", smallestLocation);
}

size_t getLineCount(FILE* file) {
    char buf[BUF_SIZE];
    size_t counter = 0;
    while(1) {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        for(size_t i = 0; i < res; ++i) {
            if (buf[i] == '\n')
                counter++;
	}

        if (feof(file))
            break;
    }

    rewind(file);

    return counter;
}
