/* Name: Kristy Nguyen, NSHE ID: 5006243601, Assignment 9
 * Description: 
 * Input:
	- 1st line contains source street name + destination street name
    - Then, each line contain a single edge (from and to street name followed by space)
 * Output: 
    - Output each path
 */

#include "adjacencyList.hpp"
#include "myStack.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <unordered_map>
#include <vector>
using namespace std;

// Function prototypes
bool getPaths(string, string, unordered_map < string, vertex<string> >, 
    unordered_map <string, bool>&, myStack <string>&, int&);

int main ()
{
    bool invalid = true;    // Bool to repeat prompt if invalid file given
    string inputFile;       // Name of input file to open and read
    ifstream inFile;        // Input file stream
    
    do
    {   // Prompt user for input file name & loop until valid input file given
        cout << "Last one ): ";
        cin >> inputFile;
        
        // Clear buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // Open file
        inFile.open(inputFile.c_str());
        
        // Set invalid to true to loop until valid file name given
        if (inFile.is_open())
            invalid = false;
        else
            invalid = true;
    } 
    while (invalid);
    
    // DO STUFF TO INPUT FILE
    // INSERT CODE BELOW
    string sourceStreet, finalStreet;           // First line: source and final street
    string fromStreet, toStreet;                // Per line: from and to streets

    inFile >> sourceStreet >> finalStreet;      // Read first line for source and final street
    
    unordered_map<string, vertex<string> > adjList;     // Declare adjacency list
    unordered_map<string, bool> nodePath;               // Declare nodePath
    
    // cout << "Source street: " << sourceStreet << endl << "Final street: " << finalStreet << endl;

    while (!inFile.eof())
    {
        inFile >> fromStreet >> toStreet;       // Read each line for the from and to street
        if (inFile.eof())                       // Break to avoid "duplicate" glitch
            break;
        adjList[fromStreet].addEdge(toStreet);  // Add the toStreet as a neighbor to the fromStreet
        
        // cout << "From street: " << fromStreet << endl << "To street: " << toStreet << endl;
    }

    // Declare iterators to loop through adjacency list for debugging
    // vertex<string>::edgeIterator it;
    // vertex<string>::edgeIterator nil(NULL);

    // for (it = adjList[sourceStreet].begin(); it != nil; it++)
    //     cout << *it << endl;
    
    // Declare recStack and numOfPaths
    myStack<string> recStack;
    int numOfPaths = 0;

    // Try to find paths from sourceStreet to finalStreet
    if(!getPaths(sourceStreet, finalStreet, adjList, nodePath, recStack,numOfPaths ))
        cout << "No path is found"<< endl;

    inFile.close();

    return 0;
}

bool getPaths(string current, string finalDestination, 
    unordered_map < string, vertex<string> > graph, 
    unordered_map <string, bool>& nodesInPath, 
    myStack <string>& recStack, int& pathNo)
{
    // INSERT CODE BELOW
    bool found = false;

    // Base case: return true if current == finalDestination
    if (current == finalDestination)
    {
        myStack<string> temp(recStack);
        myStack<string> result;
        pathNo++;                               // Increment pathNo if path is found
        cout << "Path " << pathNo << " : ";     // Display path

        while (!temp.isEmpty())                 // Push temp into results stack
        {                                       // for proper display results
            result.push(temp.top());
            temp.pop();
        }

        while (!result.isEmpty())               // Display results
        {
            cout << result.top();
            result.pop();
            cout << " <=> ";
        }
        cout << finalDestination << endl;       // Display final destination
        return true;
    }
    nodesInPath[current] = true;                // Set current path to true
    recStack.push(current);                     // Push current path
    
    // Declare iterators to loop through adjacency list
    vertex<string>::edgeIterator it;
    vertex<string>::edgeIterator nil(NULL);

    for (it = graph[current].begin(); it != nil; it++)
    {
        if (!nodesInPath[*it])                                  // If current is not visited
        {
            bool traceBack = false;

            // Declare iterator (it2) to loop through and trace back to find a path back to sourceStreet
            vertex<string>::edgeIterator it2;
            for (it2 = graph[*it].begin(); it2 != nil; it2++)
            {
                if (*it2 == current)
                {
                    traceBack = true;
                    break;
                }
            }
            
            // If trace back is true, and result is true, then a path is found
            if (traceBack == true)
            {
                bool result = getPaths(*it, finalDestination, graph, nodesInPath, recStack, pathNo);
                if (result == true)
                    found = true;
            }
        }
    }

    // Otherwise the path is not current anymore, pop current
    nodesInPath[current] = false;
    recStack.pop();

    // Return found
    return found;    
}