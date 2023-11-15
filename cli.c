// Minesweeper Project
// file: cli.c
// Brian Figueroa
// 03-11-2023

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// definition of “cell” struct
struct cell {
	int position;
	int adjCount;
	int mined;
	int covered;
	int flagged;
};
typedef struct cell cell;

// global definitions ----
cell** board;
int rows;
int cols;
int mines;

// sizing constants ------
#define MAXTOKENCOUNT 20	// max num of substr
#define MAXTOKENLENGTH 20	// substr length
#define MAXSTRLENGTH 400	// max str length
#define PERCENTAGEOFSHUFFLE 1.25

// prototype functions ---
void runGame();
void getLine(char tempLine[], int maxLineLen);
void getTokens(char tempLine[], char tempTokens[][MAXTOKENLENGTH], int* count);
void displayCell(cell* c);
void commandNew();
void commandShow();
int processCommand(char tokens[][MAXTOKENLENGTH], int tokenCount);

void rungame() {
	// Variables
	char line[MAXSTRLENGTH];
	char tokens[MAXTOKENCOUNT][MAXTOKENLENGTH];
	int count;
	int result;

	while (1) {
		printf(">> ");
		getLine(line, MAXSTRLENGTH);
		getTokens(line, tokens, &count);

		result = processCommand(tokens, count);
		if (result == 0)
			break;
	}
}
// helper functions
void getLine(char tempLine[], int maxLineLen) {
	fgets(tempLine, maxLineLen, stdin);
	tempLine[strlen(tempLine) - 1] = '\0';
}
void getTokens(char line[], char tokens[][MAXTOKENLENGTH], int* count) {
	char* subStr;
	char lineCopy[MAXSTRLENGTH];
	int tokenCount = 0; // initialize token count to 0
	strcpy(lineCopy, line);

	subStr = strtok(lineCopy, " "); // initialize subStr to first token based on space " " separator
	while (subStr != NULL) { 			// keep going until subStr is NULL
		strcpy(tokens[tokenCount], subStr); 		// copy latest token from subStr to tokens[] array
		tokenCount++;
		subStr = strtok(NULL, " "); 		// advance subStr to next token
	}
	count = &tokenCount;
}
int getRandom(int range){
	return ((int)floor((float)range*rand()/RAND_MAX))%range;
}
// command functions for “new” and “show”
void displayCell(cell* c) {
	if (c->mined == 1) {
		printf("%4s", "M");
	}
	else
		printf("%4d", c->position);
}
void commandNew() {
	board = (cell**)malloc(sizeof(cell*) * rows);

	// allocate new row vector
	for (int i = 0; i < rows; i++) {
		board[i] = (cell*)malloc(sizeof(cell) * cols);
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].position = i * cols + j;
		}
	}

	// initial placement of mines
	for (int p = 0; p < mines; p++) {
		int r = p/cols;
		int c = p%cols;
		board[r][c].mined = 1;
	}
	// shuffle placement of mines
	for (int s = 1; s < rows * cols * PERCENTAGEOFSHUFFLE; s++) {
		int row1 = getRandom(rows);
		int row2 = getRandom(rows);
		int col1 = getRandom(cols);
		int col2 = getRandom(cols);

		// Swap mined values between two random cells
		int tempMined = board[row1][col1].mined;
		board[row1][col1].mined = board[row2][col2].mined;
		board[row2][col2].mined = tempMined;
	}

}
void commandShow() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			displayCell(&board[i][j]);
		}
		printf("\n");
	}
}
// process command function
int processCommand(char tokens[][MAXTOKENLENGTH], int tokenCount) {
	if (strcmp(tokens[0],"new") == 0) {
		rows = atoi(tokens[1]);
		cols = atoi(tokens[2]);
		mines = atoi(tokens[3]);

		commandNew();
	}
	else if (strcmp(tokens[0], "show") == 0) {
		commandShow();
	}
	else {
		printf("Bye!\n");
		return 0;
	}
	return 1;
}

int main (void) {
	srand(time(0));
	rungame();
	return 0;
}
