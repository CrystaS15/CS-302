#include <fstream>
#include <cstdlib>
using namespace std;

template <class type>
struct binTreeNode
{
	//binTreeNode();
	type item; //stores the data in the node of the tree
	binTreeNode<type> * left;
	binTreeNode<type> * right;
};

template <class type>
void readLISP(binTreeNode<type>*,  ifstream&);

binTreeNode<int>* createNode(ifstream&);

template <class type>
bool evaluate(binTreeNode<type>*, int, int, myStack<type>&);

template <class type>
void destroyTree(binTreeNode<type>*);

////////////////////////////////////////////////////////////////////

template <class type>
void readLISP(binTreeNode<type> * r,  ifstream& infile)
{
	char	ch;
	int		x;
	
	// Leaf node reached
	if (r == NULL)
		return;

	infile >> ch; // '('
	infile >> ch; // ')' or integer
	
	// Character read is ')'
	if (ch == ')')
	{
		// Set left subtree to NULL
		r->left = NULL;
		readLISP(r->left, infile);
		
		// Check if next character is '('
		infile >> ch; // '('
		infile >> ch; // ')' or integer
		
		// Right subtree contains integer
		if (ch != ')')
		{
			infile.putback(ch);
			infile >> x;
			
			r->left		= new binTreeNode<int>;
			r->right	= new binTreeNode<int>;

			binTreeNode<int> * tmp;
			tmp			= r;
			tmp			= tmp->right;
			tmp->item	= x;
			readLISP(r->right, infile);
		}

		// Set right subtree to NULL
		if (ch == ')')
		{
			r->right = NULL;
			readLISP(r->right, infile);
		}

		// Parse remaining ')'
		infile >> ch;
		if (ch != ')')
			infile.putback(ch);

		// If number is found, return
		// readLisp for current expression is most likely done
		if (isdigit(ch))
			return;

		while (ch == ')')
		{
			infile >> ch;
			if (ch != ')')
				infile.putback(ch);
			
			// If number is found, return
			// readLisp for current expression is most likely done
			if (isdigit(ch))
				return;
		}
	}
	
	// Char read after '(' is an integer
	if (ch != ')' && ch != '(')
	{
		// Put back character and read as integer
		infile.putback(ch);
		infile >> x;
		
		// Assign NULL to left and right subtrees
		r->left		= new binTreeNode<int>;
		r->right	= new binTreeNode<int>;
		
		// Create tmp pointer pointing to r pointer
		binTreeNode<int> * tmp;
		tmp = r;

		// Build left subtree recursively in pre-order fashion
		tmp			= tmp->left;
		tmp->item	= x;
		readLISP(r->left, infile);

		// Build right subtree recursively in pre-order fashion
		infile >> ch; // '('
		infile >> ch; // ')' or integer
		
		// Set right subtree to NULL
		if (ch == ')')
		{
			r->right = NULL;
			readLISP(r->right, infile);
		}

		// Right subtree contains integer
		if (ch != ')')
		{
			infile.putback(ch);
			infile >> x;
			
			tmp			= r;
			tmp			= tmp->right;
			tmp->item	= x;
			readLISP(r->right, infile);
		}

		// Parse remaining ')'
		infile >> ch;
		if (ch != ')')
			infile.putback(ch);

		while (ch == ')')
		{
			infile >> ch;
			if (ch != ')')
				infile.putback(ch);
			
			// If number is found, return
			// readLisp for current expression is most likely done
			if (isdigit(ch))
				return;
		}

		if (ch == '(')
			return;

	}

	return;
}

template <class type>
bool evaluate(binTreeNode<type> * r, int runningSum, int targetSum, 
	myStack<type>& path)
{
	if (r == NULL || runningSum < 0)
		return false;

	// Current sum from the root to the current node r
	runningSum += r->item;

	// If true, path has been established
	if (runningSum == targetSum && (r->left == NULL && r->right == NULL))
	{
		path.push(r->item);
		return true;
	}

	// If true for left subtree, return true up function call
	if (evaluate(r->left, runningSum, targetSum, path))
	{
		path.push(r->item);
		return true;
	}

	// If true for right subtree, return true up function call
	if (evaluate(r->right, runningSum, targetSum, path))
	{
		path.push(r->item);
		return true;
	}

}

template <class type>
void destroyTree(binTreeNode<type> * r)
{
	// Leaf node reached
	if (r == NULL || r->item < 0)
		return;
	
	// Destroy tree in post-order fashion
	destroyTree(r->left);
	destroyTree(r->right);
	
	// Delete node
	delete r;

	return;
}