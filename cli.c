// Minesweeper Project
// file: cli.c
// Brian Figueroa
// 03-11-2023

#include <stdio.h>
#include <string.h>

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

// prototype functions ---
void runGame();
void getLine(char tempLine[], int maxLineLen);
void getTokens(char tempLine[], char tempTokens[][MAXTOKENLENGTH], int* count);
void displayCell(cell* c);
void commandNew();
void commandShow();
int processCommand(char tokens[][MAXTOKENLENGTH], int* tokenCount);

int rungame() {
	// Variables
	char line[MAXSTRLENGTH];
	char tokens[MAXTOKENCOUNT][MAXTOKENLENGTH];
	char* subStr;
	char lineCopy[MAXSTRLENGTH];
	int count;
	int result;

	while (1) {
		printf("\n>> ");
		getLine(line, MAXSTRLENGTH);
//		getTokens(line, tokens, count);
		
// get tokens function-----------------------------------------------------------
		strcpy(lineCopy, line); // create copy of line into lineCopy

		// break lineCopy into tokens based on space " " separator
		subStr = strtok(lineCopy, " "); // initialize subStr to first token
		
		count = 0; // initialize token count to 0
		while (subStr != NULL) { // keep going until subStr is NULL
		strcpy(tokens[count], subStr);
		subStr = strtok(NULL, " "); // advance subStr to next token
		count++; 		
		}
//-------------------------------------------------------------------------------

		if (strcmp(tokens[0],"new") == 0) {
			rows = atoi(tokens[1]);
			cols = atoi(tokens[2]);
			mines = atoi(tokens[3]);
			commandNew();
		}
		else if(strcmp(tokens[0], "show") == 0) {
			commandShow();
		}
		else {
			printf("Bye!\n");
			return 0;
		}
		
	}
	return 1;
}


// helper functions
void getLine(char tempLine[], int maxLineLen) {
	fgets(tempLine, maxLineLen, stdin);
	int lineLen = strlen(tempLine);
	if (tempLine[lineLen - 1] == '\n')
		tempLine[lineLen - 1] = '\0';
}
/* void getTokens(char line[], char tokens[][MAXTOKENLENGTH], int* count) {
	char* subStr;
	char lineCopy[MAXSTRLENGTH];

	strcpy(lineCopy, line); // create copy of line into lineCopy

	// break lineCopy into tokens based on space " " separator
	subStr = strtok(lineCopy, " "); // initialize subStr to first token
	count = 0; // initialize token count to 0
	
	while (subStr != NULL) { 			// keep going until subStr is NULL
		strcpy(tokens[count], subStr); 		// copy latest token from subStr to tokens[] array
		subStr = strtok(NULL, " "); 		// advance subStr to next token
		printf("Token %d is %s\n", count, subStr);
		count++;
		
	}
}*/

// command functions for “new” and “show”
void displayCell(cell* c) {
	printf("%4d", c->position);
}
void commandNew() {
	board = (cell**)malloc(sizeof(cell*) * rows);

	//allocate new row vector
	for (int i = 0; i < rows; i++) {
		board[i] = (cell*)malloc(sizeof(cell) * cols);
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			board[i][j].position = i * cols + j;
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

/* // process command function
int processCommand(char tokens[][MAXTOKENLENGTH], int* tokenCount) {
	if (strcmp(tokens[0],"new") == 0) {
		rows = atoi(tokens[1]);
		cols = atoi(tokens[2]);
		mines = atoi(tokens[3]);

		commandNew();
	}
	else if(strcmp(tokens[0], "show") == 0) {
		commandShow();
	}
	else {
		printf("Bye!\n");
		return 0;
	}
	return 1;
}
*/

int main (void) {
	rungame();
	return 0;
}