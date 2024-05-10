/*
* Name: Kristy Nguyen, 5006243601, Assignment #1
* Description: (main.cpp) A game board in which the game 15 puzzle can be played
* Input: input file name, single char to make a move, response char to continue or not
* Output: puzzle
*/

#include "LL.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

int main() {
	string inputFile;
	bool invalid = true;

	// Ask user for an input file
	cout << "Enter puzzle file: ";
	cin >> inputFile;
	cin.clear();
	cin.ignore(1000, '\n');

	cout << endl;

	ifstream inFile;

	// Open input file
	inFile.open(inputFile.c_str());

	int x = 0;

	if (inFile.is_open()) { // File open = Valid file
		invalid = false;
		
		LL<int> board[4];
		
		// Read contents of file and build linked list
		int count = 0;
		while (count < 4) {
			for (int i = 0; i < 4; i++) {
				inFile >> x;
				board[count].headInsert(x);
				for (int j = 0; j < 3; j++) {
					inFile >> x;
					board[count].tailInsert(x);
				}
				count++;
			}
		}

		// Output the puzzle
		count = 0;
		LL <int>::iterator it;
		while (count < 4) {
			for (int i = 0; i < 4; i++) {
				it = board[count].begin();

				if (*it == 0) {
					cout << setw(3) << "-";
					it++;
				} else {
					cout << setw(3) << *it;
					it++;
				}

				for (int j = 0; j < 3; j++) {
					if (*it == 0) {
						cout << setw(4) << "-";
						it++;
					} else {
						cout << setw(4) << *it;
						it++;
					}
				}
				cout << endl;
				count++;
			}
		}

		
		char userMove;
		bool continueGame = true;
		while (continueGame) {
			
			// Ask user to make a move
			// Repeat if invalid input given
			cout << endl;
			cout << "Please make your choice, (L)eft, (R)ight, (U)p, (D)own, (Q)uit: ";
			cin >> userMove;
			cin.clear();
			cin.ignore(1000, '\n');
			
			cout << endl;

			/* For the following character selections for the user to make a move,
			   the (L)eft, (R)ight, (U)p, and (D)own selections do not actually do
			   anything. I simply made sure that the code was able to (Q)uit and
			   outputted the same initial board after reading in a character for 
			   making a move. */

			switch (toupper(userMove))
			{
			case 'L':
				break;
			case 'R':
				break;
			case 'U':
				break;
			case 'D':
				break;
			case 'Q':
				cout << "Quitter..." << endl << endl;
				return 0;
				break;
			default:
				cout << "Invalid selection!" << endl;
				continue;
			}

			// Outputs the puzzle after making a move
			count = 0;
			LL <int>::iterator it;
			while (count < 4) {
				for (int i = 0; i < 4; i++) {
					it = board[count].begin();

					if (*it == 0) {
						cout << setw(3) << "-";
						it++;
					}
					else {
						cout << setw(3) << *it;
						it++;
					}

					for (int j = 0; j < 3; j++) {
						if (*it == 0) {
							cout << setw(4) << "-";
							it++;
						}
						else {
							cout << setw(4) << *it;
							it++;
						}
					}
					cout << endl;
					count++;
				}
			}

			int arrayNum = 0;
			int counter = 1;
			int correctValue = 0;

			// Check if game is over
			while (arrayNum < 4) {
				for (int i = 0; i < 4; i++) {
					it = board[arrayNum].begin();

					for (int j = 0; j < 4; j++) {
						if (*it == counter) {
							it++;
							counter++;
							correctValue++;
						}
					}
					arrayNum++;
				}
			}

			/* I commented out the following code because I'm not sure if it works properly,
			   but this is my plan for testing to see if the game is over. Of course, this
			   is assuming that the "making a move" from steps 4-9 works properly. */

			//char playResponse;
			//bool continuePrompt = true;
			//// If number of correct values = 15, the game is over
			//if (correctValue == 15) {
			//	continueGame = false;
			//	cout << "You win!!!" << endl << endl;
			//	
			//	while (continuePrompt) {
			//		cout << "Play again? (Y/N): ";
			//		cin >> playResponse;
			//		cin.clear();
			//		cin.ignore(1000, '\n');

			//		switch (toupper(playResponse)) {
			//		case 'Y':
			//			continuePrompt = false;
			//			break;
			//		case 'N':
			//			continuePrompt = false;
			//			cout << endl << "Yeah I don't blame you for not wanting to play anymore" << endl;
			//			cout << "This game is like league... except it actually makes sense :D" << endl;
			//			return 0;
			//			break;
			//		default:
			//			continuePrompt = true;
			//			cout << "Invalid selection!" << endl;
			//		}
			//	}
			//}

			//continueGame = true;
		}
	}

	else
	{
		while (invalid) {
			cout << "Enter puzzle file: ";
			cin >> inputFile;
			cin.clear();
			cin.ignore(1000, '\n');

			inFile.open(inputFile.c_str());

			if (inFile.is_open()) {
				invalid = false;
			}
			else {
				invalid = true;
			}
		}
	}

	inFile.close();

	return 0;
}