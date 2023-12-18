#include <stdio.h>
#include <math.h>
#include <assert.h>

char matrix[140][140];

typedef struct {
    char value;
    void (*action)(int*, int*, enum cardinal*);
} direction;

enum cardinal {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

void traversePipe(int*, int*, enum cardinal*);
void traverseHyphen(int*, int*, enum cardinal*);
void traverseL(int*, int*, enum cardinal*);
void traverseJ(int*, int*, enum cardinal*);
void traverseSeven(int*, int*, enum cardinal*);
void traverseF(int*, int*, enum cardinal*);
void traversePeriod(int*, int*, enum cardinal*);
void traverseS(int*, int*, enum cardinal*);

direction mappings[7] = {
    { '|', traversePipe },
    { '-', traverseHyphen },
    { 'L', traverseL },
    { 'J', traverseJ },
    { '7', traverseSeven },
    { 'F', traverseF },
    { '.', traversePeriod }
};

int main(void) {
    FILE* fp = fopen("./input.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    int currentXIndex = 0;
    int currentYIndex = 0;

    size_t lineIndex = 0;
    while ((read = getline(&line, &len, fp)) != -1) {
	for (ssize_t i = 0; i <= read; ++i) {
	    char curr = line[i];
	    if (curr == 'S') {
		currentXIndex = i;
		currentYIndex = lineIndex;
	    }
	    matrix[lineIndex][i] = curr;
	}
	lineIndex++;
    }
    
    int steps = 0;
    enum cardinal prevDirection = NULL;
    traverseS(&currentXIndex, &currentYIndex, &prevDirection);
    while (matrix[currentYIndex][currentXIndex] != 'S') {
	for (size_t i=0; i<7; ++i) {
	    if (mappings[i].value == matrix[currentYIndex][currentXIndex]) {
		mappings[i].action(&currentXIndex, &currentYIndex, &prevDirection);
		break;
	    }
	}
	++steps;
    }

    printf("Furthest point is %d steps away\n", steps/2 + 1);
    
    return 0;
}

void traversePipe(int* x, int* y, enum cardinal* dir) {
    if (*dir == SOUTH)
	*y = *y - 1;
    else if (*dir == NORTH)
	*y = *y + 1;
}

void traverseHyphen(int* x, int* y, enum cardinal* dir) {
    if (*dir == WEST)
	*x = *x + 1;
    else if (*dir == EAST)
	*x = *x - 1;
}

void traverseL(int* x, int* y, enum cardinal* dir) {
    if (*dir == EAST) {
	*y = *y - 1;
	*dir = SOUTH;
    }
    else if (*dir == NORTH) {
	*x = *x + 1;
	*dir = WEST;
    }
}

void traverseJ(int* x, int* y, enum cardinal* dir) {
    if (*dir == WEST) {
	*y = *y - 1;
	*dir = SOUTH;
    }
    else if (*dir == NORTH) {
	*x = *x - 1;
	*dir = EAST;
    }
}

void traverseSeven(int* x, int* y, enum cardinal* dir) {
    if (*dir == SOUTH) {
	*x = *x - 1;
	*dir = EAST;
    }
    else if (*dir == WEST) {
	*y = *y + 1;
	*dir = NORTH;
    }
}

void traverseF(int* x, int* y, enum cardinal* dir) {
    if (*dir == EAST) {
	*y = *y + 1;
	*dir = NORTH;
    }
    else if (*dir == SOUTH) {
	*x = *x + 1;
	*dir = WEST;
    }
}

void traversePeriod(int* x, int* y, enum cardinal* dir) {
    printf("Got into the ground somehow");
    assert(0);
}

void traverseS(int* x, int* y, enum cardinal* dir) {
    char north = matrix[*y - 1][*x];
    char south = matrix[*y + 1][*x];
    char west = matrix[*y][*x - 1];
    char east = matrix[*y][*x + 1];

    if ((north == '|' || north == '7' || north == 'F') && (south == '|' || south == 'J' || south == 'L')) {
	*dir = SOUTH;
	traversePipe(x, y, dir);
    }
    else if ((east == '-' || east == '7' || east == 'J') && (west == '-' || west == 'L' || west == 'F')) {
	*dir = EAST;
	traverseHyphen(x, y, dir);
    }
    else if ((north == '|' || north == '7' || north == 'F') && (east == '-' || east == '7' || east == 'J')) {
	*dir = NORTH;
	traverseL(x, y, dir);
    }
    else if ((north == '|' || north == '7' || north == 'F') && (west == '-' || west == 'L' || west == 'F')) {
	*dir = WEST;
	traverseJ(x, y, dir);
    }
    else if ((south == '|' || south == 'J' || south == 'L') && (east == '-' || east == '7' || east == 'J')) {
	*dir = EAST;
	traverseF(x, y, dir);
    }
    else if ((south == '|' || south == 'J' || south == 'L') && (west == '-' || west == 'L' || west == 'F')) {
	*dir = WEST;
	traverseSeven(x, y, dir);
    }
}
