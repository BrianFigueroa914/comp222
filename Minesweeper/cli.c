// Minesweeper Project
// file: cli.c
// Brian Figueroa
// 03-11-2023

#include <stdio.h>

// ----------------------------------
// global definitions
cell** board;
int rows;
int cols;
int mines;
// sizing constants
#define MAXTOKENCOUNT 20
#define MAXTOKENLENGTH 20
#define MAXLINELENGTH 400


// definition of “cell” struct
struct cell {
	int position;
	int adjCount;
	int mined;
	int covered;
	int flagged;
};
typedef struct cell cell;
// function prototypes for all functions definedin this file
void runGame();
void getLine(char tempLine[], int maxLineLen);
void getTokens(char tempLine[], char tempTokens[][MAXTOKENLENGTH], int* count);
void commandNew(int r, int c, int m);
void commandShow();
void displayCell(cell* c);
int processCommand(char tokens[][MAXTOKENLENGTH], int tokenCount);
// ----------------------------------

// ---------------------------------
// input processing functions
void runGame() {
	char line[MAXLINELENGTH], lineCopy[100];
	char tokens[MAXTOKENCOUNT][MAXTOKENLENGTH];

	while (1) {
		int tokenCount;
		int result;
		printf(">> ");
		getLine(line, MAXLINELENGTH);
		getTokens(line, tokens, &tokenCount);
		result = processCommand(tokens, tokenCount);

		if (result == 0)
			break;
	}
}
void getLine(char tempLine[], int maxLineLen) {
	fgets(tempLine, maxLineLen, stdin);
	int lineLen = strlen(tempLine);
	if (tempLine[lineLen - 1] == '\n')
		tempLine[lineLen - 1] = '\0';
}
void getTokens(char line[], char tokens[][MAXTOKENLENGTH], int* count) {
	char* p;
	strcpy(linecopy, line); // create copy of line into linecopy

	// break linecopy into tokens based on space " " separator
	p = strtok(linecopy, " "); // initialize p to first token
	count = 0; // initialize token count to 0
	while (p != NULL) { // keep going until p is NULL
		strcpy(tokens[count], p); // copy latest token from p
		// to tokens[] array
		p = strtok(NULL, " "); // advance p to next token
		count++; // increment tokencount
	}
}


// ---------------------------------

// ---------------------------------
// command functions for “new” and “show”
void commandNew(int r, int c, int m) {
	rows = r;
	cols = c;
	mines = m;

	board = (cell**)malloc(sizeof(cell*) * rows);

	//allocate new row vector
	for (int i = 0; i < rows; i++) {
		board[i] = (cell*)malloc(sizeof(cell) * cols);
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			init_cell(&board[i][j]);
		}
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
void displayCell(cell* c) {
	printf(" %d", c->position);
}
int processCommand(char tokens[][MAXTOKENLENGTH], int tokenCount) {
	if (token)
	{

	}
}
// ---------------------------------

// ---------------------
// main function
int main(void) {
	runGame();
	return 0;
}

// ---------------------