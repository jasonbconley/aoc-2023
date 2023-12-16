#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

typedef struct {
    long* readings;
    size_t reading_len;
} reading;

long computePrediction(reading);

reading* measurements;

int main(void) {

    FILE* fp;
    fp = fopen("./input2.txt", "r");
    char c;
    size_t numLines = 0;
    for (c = getc(fp); c != EOF; c = getc(fp))
	if (c == '\n')
	    numLines += 1;
    rewind(fp);

    measurements = malloc(sizeof(reading) * numLines);
    
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    
    size_t lineIndex = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
	reading* current_reading = malloc(sizeof(reading));
	current_reading->reading_len = 0;
	long* readings_store = malloc(sizeof(long) * 256);
	for (ssize_t i = 0; i <= read; ++i) {
	    if (isdigit(line[i])) {
	       long curr = atol(&line[i]);
	       readings_store[current_reading->reading_len++] = curr;
	       int size = floor(log10(labs(curr))) + 1;
	       i += size - 1;
	    }
	}
	current_reading->readings = malloc(sizeof(long) * current_reading->reading_len);
	memcpy(current_reading->readings, readings_store, sizeof(long) * current_reading->reading_len);
	measurements[lineIndex++] = *current_reading;  
    }
    fclose(fp);

    long sum = 0;
    for (size_t i=0; i<lineIndex; ++i) {
	for (size_t j=0; j<measurements[i].reading_len; ++j) {
	    printf("%ld ", measurements[i].readings[j]);
	}
	printf("\n");
	long pred = computePrediction(measurements[i]);
        sum += pred;
    }
    printf("Sum = %ld", sum);

    return 0;
}

long computePrediction(reading current_reading) {
    size_t len = current_reading.reading_len - 1;
    reading next_row = { .readings = malloc(sizeof(long) * 256), .reading_len = 0 };
    int not_all_zeroes = 0;

    for (size_t i=0; i < len; ++i) {
	long big = current_reading.readings[i + 1];
	long small = current_reading.readings[i];
	long current_num = big - small;

	if (current_num != 0L)
	    not_all_zeroes = 1;

	next_row.readings[next_row.reading_len++] = current_num;
    }
    
    if (not_all_zeroes == 0)
	return 0;
    
    long num_to_add = current_reading.readings[current_reading.reading_len - 1];
    long next_row_add = computePrediction(next_row);
    printf("Adding %ld to %ld\n", num_to_add, next_row_add);
    return num_to_add + next_row_add;
}
