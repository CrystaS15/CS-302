/*
* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 6
* Description: Use a hash map to tally up assignments (without counting duplicates).
* Input:
	2 files -
		1. one that has all the students' names
		2. a set of assignments containing the following string "studentName_A#"
			where # will be a number from 1-9
* Output: amount of missing assignments for each student
*/

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

int main()
{
	bool		invalidFile;	// bool to re-prompt until valid
	ifstream	inFile;			// input file stream
	
	string			studentFile;	// names file
	string			studentName;	// string that contains student name
	char			ch;				
	vector<string>	namesVector;	// vector of strings that contains student names
	
	// Prompt for names file until valid input
	do	
	{	
		cout	<< "Enter students file: ";
		cin		>> studentFile;
		
		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear input buffer
		
		inFile.open(studentFile.c_str());						// Open file

		invalidFile = true;
		if (inFile.is_open())
		{
			invalidFile = false;

			while (!inFile.eof())
			{
				// Push student name into names vector of strings
				while (getline(inFile, studentName))
					namesVector.push_back(studentName);
			}

			inFile.close();		// Close file
		}
	} 
	while (invalidFile);		// Loop if invalid file name input

	cout << endl;				// Output endline in between prompting
	
	string							astFile;		// User input file name
	string							astName;		// Read in assignment file name
	string							astStudentName;	// Substring of student name from assignment file name
	vector<string>					astVector;		// Vector of strings containing assignment file names
	unordered_map <string, bool>	duplicate;		// duplicate["string"] = false
	unordered_map <string, int>		astTotalNum;	// astTotalNum["string"] = 0
	
	// Prompt for file with assignment submissions until valid input.
	do	
	{	
		cout << "Enter assignments file: ";
		cin >> astFile;

		cin.ignore(numeric_limits<streamsize>::max(), '\n');	// Clear input buffer

		inFile.open(astFile.c_str());							// Open file

		invalidFile = true;
		if (inFile.is_open())
		{
			invalidFile = false;

			while (!inFile.eof())
			{	
				// Push assignment file name into assignment vector of strings
				while (getline(inFile, astName))
					astVector.push_back(astName);
			}

			for (unsigned int i = 0; i < astVector.size(); i++)
			{
				if (!duplicate[astVector[i]])
				{
					// Get the substring of the name
					size_t underScore = astVector[i].find("_");
					astStudentName = astVector[i].substr(0, underScore);

					astTotalNum[astStudentName]++;	// Total number of assignments for each student ++

					duplicate[astVector[i]] = true; // Set assignment file name = true for duplicates
				}
			}

			inFile.close();		// Close file
		}
	} 
	while (invalidFile);		// Loop if invalid file name input

	// Output title
	cout << endl << "NAME" << setw(30);
	cout << "MISSING ASSIGNMENTS" << endl;
	
	int missingAstNum = -1;
	for (unsigned int i = 0; i < namesVector.size(); i++)
	{	
		// Output names and total number of missing assignments
		cout << namesVector[i] << setw(16-namesVector[i].length());
		missingAstNum = 9 - astTotalNum[namesVector[i]];
		cout << missingAstNum << endl;
	}
	
	return 0;
}