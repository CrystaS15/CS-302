/*
* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 7
* Description: Analyze document containing words
* Input:
	T (number of test cases)
    Each test case will be denoted by 1/1+ lines (no more than 150 chars)
    Last line contains 'END'
    Assume document contains between 1 & 105 words
* Output: 
    Test Case Number
    Print p and q
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <regex>
#include <unordered_map>
#include "hashMap.h"
using namespace std;

void distinctWordHash(vector<string>&, int&);
void rangeHash (int&, int&, int&, vector<string>, int&);

int main () 
{
    // Variable declarations
    ifstream inFile;
    string fileName;
    int testCases;
    bool invalidFile = false;
    bool continueReading = true;

    // Prompt user for input file name
    cout << "You know the drill: ";
    cin >> fileName;

    // Open file
    inFile.open(fileName.c_str());

    /*  Set bool value to false if file successfully opens
        and true otherwise. */
    if (inFile.is_open())
        invalidFile = false;
    else
        invalidFile = true;

    // Repeat prompt until valid file name is entered
    while (invalidFile)
    {
        cout << "You know the drill: ";
        cin >> fileName;

        inFile.open(fileName.c_str());
        if (inFile.is_open())
            invalidFile = false;
        else
            invalidFile = true;
    }
    
    cout << endl;

    // Read in T (number of test cases)
    inFile >> testCases;

    string temp;
    regex pattern ("[a-zA-Z]+");

    
    for (int i = 0; i < testCases; i++)
    {
        vector <string> wordsVector;
        hashMap <string, bool> duplicate;
        int testNumber = 1;
        while (getline(inFile, temp))
        {
            regex_token_iterator <string::iterator> rend;
            regex_token_iterator <string::iterator> words (temp.begin(), temp.end(), pattern);
            
            while (words!=rend) 
            {
                int pValue;
                int qValue;

                if (*words == "END")
                {
                    continueReading = false;

                    // for (auto i = wordsVector.begin(); i != wordsVector.end(); i++)
                    //     cout << *i << endl;

                    int distinctWords = 0;
                    
                    distinctWordHash(wordsVector, distinctWords);

                    int windowSize = distinctWords;
                    int count = 0;
                    int startingIndex = 0;
                    int index = 0;
                    while (count != distinctWords)
                    {
                        count = 0;
                        pValue = index + 1;
                        qValue = index + windowSize;

                        rangeHash (startingIndex, index, qValue, wordsVector, count);

                        // cout << "count: " << count << endl;
                        // cout << "distinctWords: " << distinctWords << endl;

                        if (count != distinctWords)
                            index++;

                        if (index >= wordsVector.size())
                        {
                            index = 0;
                            windowSize++;
                        }
                    }

                    cout << "Test" << setw(7) << testNumber << ": ";
                    cout << pValue << " " << qValue << endl;

                    testNumber++;

                    wordsVector.clear();
                    // cout << "Distinct words: " << distinctWords << endl;
                    // cout << "New case: " << endl;
                }

                if (continueReading)
                    wordsVector.push_back(*words);

                words++;
            }
            
            continueReading = true;
        }
        
    }
    
    cout << endl;
    cout << "Before this program ends, just remember..." << endl;
    cout << "Words can in fact hurt >:(" << endl;

    return 0;
}

void distinctWordHash (vector<string>& stringVector, int& counter)
{
    unordered_map <string, bool> duplicate;

    counter = 0;
    for (unsigned int i = 0; i < stringVector.size(); i++)
    {
        if (!duplicate[stringVector[i]])
        {
            counter++;
            duplicate[stringVector[i]] = true;
        }
    }
}

void rangeHash (int& start, int& current, int& maximum, vector<string> stringVector, int& counter)
{
    unordered_map <string, bool> duplicate;
    
    for (start = current; start < maximum; start++)
    {
        if (!duplicate[stringVector[start]])
        {    
            counter++;
            duplicate[stringVector[start]] = true;
        }
        // cout << "count: " << count << endl;
    }
}