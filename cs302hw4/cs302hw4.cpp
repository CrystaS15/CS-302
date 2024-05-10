/*
* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 4
* Description: Use a set of threads to sort a given array.
* Input: 
	2 integers - 
		1. to denote the list of the list listSize
		2. amount of threads we wish to use denoted as numThreads
	Numbers
	Amount of Threads
* Output: List
*/

#include <iostream>
#include <thread>
#include <vector>
#include <iomanip>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

void insertionSort (int, int);
void mergeLists (int, int, int, int);

vector<int> list;

int main()
{
	chrono::time_point<chrono::system_clock> start, end;
	chrono::time_point<chrono::system_clock> sequentialStart, sequentialEnd;
	int listSize = 0;
	int subListSize = 0;
	int numThreads = 0;
	int counter = 0;
	unsigned int con_threads = thread::hardware_concurrency();
	vector<thread> insertionThreads;
	vector<thread> mergeThreads;

	// Prompt list size
	cout << "Enter list size: ";
	cin >> listSize;
	cin.clear();
	cin.ignore(1000, '\n');

	// Re-prompt if (cin.fail() || listSize <= 0)
	while (cin.fail() || listSize <= 0)
	{
		cout << "Enter list size: ";
		cin >> listSize;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	// Resize vector with listSize number of items
	//list.resize(listSize);

	srand(time(0));

	// Assign a random number into each element between 1 and listSize
	for (int i = 0; i < listSize; i++)
	{
		list.push_back(rand() % listSize + 1);
	}

	// Prompt amount of threads
	cout << "Enter amount of threads: ";
	cin >> numThreads;
	cin.clear();
	cin.ignore(1000, '\n');

	// Re-prompt if (cin.fail() || numThreads > con_threads)
	while (cin.fail() || numThreads > con_threads)
	{
		cout << "Enter amount of threads: ";
		cin >> numThreads;
		cin.clear();
		cin.ignore(1000, '\n');
	}

	if (listSize <= 512) {
		cout << endl << "List (unsorted): " << endl;
		counter = 0;
		for (auto it = list.begin(); it != list.end(); it++) {
			cout << right << setw(3) << *it << " ";

			counter++;

			if (counter == 10) {
				cout << endl;
				counter = 0;
			}
		}
		cout << endl << endl;
	}
	
	/*
	sequentialStart = chrono::system_clock::now();
	// Sequential Sort
	sort(list.begin(), list.end());
	sequentialEnd = chrono::system_clock::now();
	*/

	start = chrono::system_clock::now();

	subListSize = listSize / numThreads;

	// Create numThreads amount of threads
	for (int i = 0; i < listSize; i += subListSize)
	{
		// Run insertion sort on each listSize/numThreads sublist
		insertionThreads.push_back(thread(insertionSort, i, i + subListSize - 1));
	}

	for (int i = 0; i < insertionThreads.size(); i++) {
		insertionThreads[i].join();
	}
	insertionThreads.clear();

	do 
	{
		// Merge each adjacent pair of listSize/numThreads size sorted sublists
		for (int i = 0; i < listSize; i += (subListSize * 2))
		{
			mergeThreads.push_back(
				thread(
					mergeLists,
					i, i + subListSize - 1,
					i + subListSize, i + (subListSize * 2) - 1
				)
			);
		}

		for (int i = 0; i < mergeThreads.size(); i++) {
			mergeThreads[i].join();
		}
		mergeThreads.clear();

		subListSize *= 2;
	} while (subListSize != listSize);
	
	end = chrono::system_clock::now();

	if (listSize <= 512) {
		cout << "List (sort): " << endl;
		counter = 0;
		for (auto it = list.begin(); it != list.end(); it++) {
			cout << right << setw(3) << *it << " ";

			counter++;

			if (counter == 10) {
				cout << endl;
				counter = 0;
			}
		}
		cout << endl << endl;
	}

	chrono::duration<double> elapsed_seconds = end - start;
	chrono::duration<double> elapsed_sequential = sequentialEnd - sequentialStart;

	cout << "Runtime: " << elapsed_seconds.count() << " s" << endl;
	/*cout << "Runtime (sequential sort): " << elapsed_sequential.count() << " s" << endl;*/

	//subListSize *= subListSize * 2;
	//if (subListSize != listSize) 

	//unsigned int con_threads;
	//con_threads = thread::hardware_concurrency();
	//cout << "Num of concurrent threads supported are: " << con_threads << endl;

	return 0;
}

void insertionSort(int left, int right)
{
	int firstOutOfOrder, location;
	int temp;

	for (firstOutOfOrder = 1; firstOutOfOrder < (right - left) + 1; firstOutOfOrder++)
	{
		if (list[firstOutOfOrder] < list[firstOutOfOrder - 1])
		{
			temp = list[firstOutOfOrder];
			location = firstOutOfOrder;

			do
			{
				list[location] = list[location - 1];
				location--;
			} 
			while (location > 0 && list[location - 1] > temp);

			list[location] = temp;
		}
	}

	return;
}

void mergeLists(int leftLeft, int leftRight, int rightLeft, int rightRight)
{
	int sizeLeft = leftRight - leftLeft + 1;
	int sizeRight = rightRight - rightLeft + 1;
	
	vector<int> listLeft;
	vector<int> listRight;

	listLeft.resize(sizeLeft);
	listRight.resize(sizeRight);

	for (int i = 0; i < sizeLeft; i++)
		listLeft[i] = list[leftLeft + i];

	for (int i = 0; i < sizeRight; i++)
		listRight[i] = list[rightLeft + i];

	int index1 = 0;
	int index2 = 0;
	int indexMerged = leftLeft;

	while (index1 < sizeLeft && index2 < sizeRight)
	{
		if (listLeft[index1] <= listRight[index2]) {
			list[indexMerged] = listLeft[index1];
			index1++;
		} else {
			list[indexMerged] = listRight[index2];
			index2++;
		}
		indexMerged++;
	}

	while (index1 < sizeLeft)
	{
		list[indexMerged] = listLeft[index1];
		index1++;
		indexMerged++;
	}

	while (index2 < sizeRight)
	{
		list[indexMerged] = listRight[index2];
		index2++;
		indexMerged++;
	}

	return;
}