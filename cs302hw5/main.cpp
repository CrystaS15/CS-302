#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "myStack.h"
#include "binaryTree.h"
using namespace std;


int main()
{
	string		fileName;
	ifstream	inFile;
	bool		invalid = true;
	
	binTreeNode<int> * root;
	
	while (invalid)
	{
		// Prompt the user for input file
		cout << "Enter LISP file (All those parenthesis...): ";
		cin >> fileName;
		cin.clear();
		cin.ignore(1000, '\n');

		//cout << endl;
		inFile.open(fileName.c_str());

		if (inFile.is_open())
		{
			invalid = false;

			while (!inFile.eof())
			{
				int				targetSum;
				char			ch;
				int				x;
				myStack<int>	path;

				inFile >> targetSum;
				inFile >> ch; // '('

				if (ch != '(')
					continue;

				inFile >> ch; // ')'
				
				// Tree with no root or nodes
				if (ch == ')')
				{
					root		= new binTreeNode<int>;
					root->left	= new binTreeNode<int>;
					root->right = new binTreeNode<int>;
					root = root->left = root->right = NULL;

					if (evaluate(root, 0, targetSum, path) == false)
						cout << "\nNo such path exists, LISP is a pain anyway" << endl;
				}

				// Tree contains root or nodes
				if (ch != ')')
				{
					// Put back character and read integer as root->item
					inFile.putback(ch);
					inFile >> x;

					// Allocate new nodes for tree
					root		= new binTreeNode<int>;
					root->left	= new binTreeNode<int>;
					root->right = new binTreeNode<int>;
					
					// Set root->item to integer read in
					root->item = x;

					// Start building binary tree with root->item
					readLISP(root, inFile);
					
					// Determine if solution is possible
					if (evaluate(root, 0, targetSum, path) == false)
						cout << "\nNo such path exists, LISP is a pain anyway" << endl;
					else
					{
						// Output set of numbers along the path whose sum equals targetSum
						cout << "\nPath in tree exists" << endl;
						while (!(path.isEmpty())) {
							cout << path.top();
							path.pop();
							if (!(path.isEmpty()))
								cout << " + ";
							else
								cout << " = ";
						}
						cout << targetSum << endl;
					}
					
					// Destroy tree
					destroyTree(root);
				}
			}
		}
		else // Re-prompt for input file if invalid file is given
			invalid = true;
			
	}
	
	return 0;
}

