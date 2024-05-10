/*
* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 2
* Description: Sudoku Solver
* Input: Prompt user for input file, re-prompt if invalid file is read, enter "NO" to terminate
* Output: Output initial puzzle and then the solved puzzle below
*/

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Function prototypes
void printBoard(int[][9], int, int);
bool recursiveSudoku(int[][9], int, int);

int main()
{
	string userResponse;
	bool invalid = false;
	bool continueGame = true;
	ifstream inFile;

	while (continueGame) {
		// Prompt user to enter initial sudoku board file
		cout << "Enter initial sudoku board file: ";
		cin >> userResponse;

		// Termminate program if user enters NO
		if (userResponse == "NO")
			return 0;

		// Open file
		inFile.open(userResponse.c_str());

		if (inFile.is_open()) {
			invalid = false;

			cout << endl << "Initial board read in" << endl << endl;

			int puzzleBoard[9][9];

			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {
					puzzleBoard[row][col] = 0;
				}
			}

			for (int row = 0; row < 9; row++) {
				for (int col = 0; col < 9; col++) {
					inFile >> puzzleBoard[row][col];
				}
			}

			// Print Board
			printBoard(puzzleBoard, 9, 9);

			// Recursively call function to solve sudoku board
			recursiveSudoku(puzzleBoard, 0, 0);

			// Print solved sudoku board
			cout << "Sudoku puzzle solved" << endl << endl;
			printBoard(puzzleBoard, 9, 9);

			// Close file
			inFile.close();
		}

		else 
		{
			invalid = true;

			// Re-prompt until valid file read
			while (invalid) {
				cout << "Enter initial sudoku board file: ";
				cin >> userResponse;

				// Terminate program if user enters NO
				if (userResponse == "NO")
					return 0;
				else 
				{
					// Open file
					inFile.open(userResponse.c_str());
					
					if (inFile.is_open())
						invalid = false;
					else
						invalid = true;
				}
			}
		}
	}

	return 0;
}

/*
* function_identifier: prints sudoku board
* parameters: board[][9] array, row index, column index
* return type: none
*/
void printBoard(int board[][9], int rowCount, int colCount)
{
	cout << "-------------------------------" << endl;
	int countCol = 0;
	int countRow = 0;
	for (int row = 0; row < rowCount; row++) {
		cout << "|";
		for (int col = 0; col < colCount; col++) {
			if (board[row][col] == 0) 
				cout << " - ";
			else
				cout << " " << board[row][col] << " ";
			
			countCol++;
			if (countCol == 3) {
				cout << "|";
				countCol = 0;
			}
		}
		cout << endl;
		countRow++;
		if (countRow == 3) {
			cout << "-------------------------------" << endl;
			countRow = 0;
		}
	}
	cout << endl;
}

/*
* function_identifier: recursive backtracking algorithm to solve sudoku board
* parameters: board[][9] array, row coordinate, column coordinate
* return type: bool
*/
bool recursiveSudoku(int board[][9], int r, int c)
{
	bool validCol = true;
	bool validRow = true;
	bool validSector = true;
	bool valid = true;
	// If the puzzle is already solved, return true
	if (r == 9)
		return true;

	// If non-blank cell at [i,j], recursively call function
	if (board[r][c] != 0) {

		// Traverse row by row
		if (c < 9)
			return recursiveSudoku(board, r, c + 1);
		
		// Row ++
		else
			return recursiveSudoku(board, r + 1, 0);
	}

	// Cell [i,j] is blank (If previous if condition didn't pass)
	if (board[r][c] == 0)
	{
		// Loop that ranges from 1 to 9
		for (int n = 1; n <= 9; n++) {

			validRow = true;
			validCol = true;
			validSector = true;

			// Check row
			for (int colCheck = 0; colCheck < 9; colCheck++) {
				if (board[r][colCheck] == n) {
					validRow = false;
					break;
				}
			}

			// Check column
			for (int rowCheck = 0; rowCheck < 9; rowCheck++) {
				if (board[rowCheck][c] == n) {
					validCol = false;
					break;
				}
			}
			
			// Check sector
			for (int rowSector = (r / 3 * 3); rowSector < ((r / 3 * 3)+3); rowSector++) {
				for (int colSector = (c / 3 * 3); colSector < ((c / 3 * 3)+3); colSector++) {
					if (board[rowSector][colSector] == n) {
						validSector = false;
						break;
					}
				}
			}
			
			// If row, column, and sector are valid, set valid to true
			if (validRow == true && validCol == true && validSector == true) {
				valid = true;
			}
			// Otherwise valid is false
			else {
				valid = false;
			}

			if (valid == true) {

				// cout << "R:" << r << " C:" << c << " N:" << n << endl;

				// Number is valid, so assign number to board
				board[r][c] = n;

				// Traverse row by row
				if (c < 9) {
					// Recursively call to process next
					// Return true if solved
					if (recursiveSudoku(board, r, c + 1) == true) {
						return true;
					}
					// Otherwise return false
					else
						return false;

				}

				// Row ++
				else {
					// Recursively call to process next
					// Return true if solved
					if (recursiveSudoku(board, r + 1, 0) == true) {
						return true;
					}
					// Otherwise return false
					else
						return false;
				}
			}
		}
	}
}