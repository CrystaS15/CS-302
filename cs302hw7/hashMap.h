#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

template <class type1, class type2>
class hashMap
{
public:
	const int MAX_ELEMENTS;
	hashMap(int = 10);
	hashMap(const hashMap<type1, type2>&);
	const hashMap<type1, type2>& operator=(const hashMap<type1, type2>&);
	~hashMap();
	type2& operator[](std::string);
private:
	int hashFunction(std::string) const;
	void resize(int);

	struct node
	{
		type1 key;
		type2 value;
		node * next;
		node * prev;
	};

	struct list
	{
		node * head;
		node * middleElement;
		int amount;
	};
	
	int filledEntries;
	int tableSize;

	list * table;
};

template <class type1, class type2>
hashMap<type1, type2>::hashMap(int init) : MAX_ELEMENTS(10)
{
	tableSize 		= init;
	filledEntries 	= 0;

	// Allocate array of size tableSize to the table pointer
	table = new list[tableSize];

	for (int i = 0; i < tableSize; i++) 
	{
		table[i].head 			= NULL;
		table[i].middleElement 	= NULL;
		table[i].amount 		= 0;
	}
}

template <class type1, class type2>
hashMap<type1, type2>::hashMap(const hashMap<type1, type2>& copy) : MAX_ELEMENTS(10)
{
	*this = copy; // calls assignment operator
}

template <class type1, class type2>
const hashMap<type1, type2>& hashMap<type1, type2>::operator=(const hashMap<type1, type2>& rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		//YOUR CODE WOULD BE HERE
		for (int i = 0; i < tableSize; i++)
		{
			node * tmp1, * tmp2;
			tmp1 = table[i].head;

			while (tmp1 != NULL)
			{
				tmp2 = tmp1->next;
				delete tmp1;
				tmp1 = tmp2;
			}
		}
		delete [] table;

		tableSize 	= rhs.tableSize;

		table 		= new list[tableSize];

		for (int i = 0; i < tableSize; i++)
			table[i] = rhs.table[i];
	}
	return *this;
}

template <class type1, class type2>
hashMap<type1, type2>::~hashMap()
{
	for (int i = 0; i < tableSize; i++)
	{
		node * tmp1, * tmp2;
		tmp1 = table[i].head;

		while (tmp1 != NULL)
		{
			tmp2 = tmp1->next;
			delete tmp1;
			tmp1 = tmp2;
		}
	}
	delete [] table;
}

template <class type1, class type2>
type2& hashMap<type1, type2>::operator[](std::string key)
{
	int index = hashFunction(key);
	double loadFactor = filledEntries / tableSize;
	node * newNode;
	
	do
	{
		node * it;

		if (table[index].amount == MAX_ELEMENTS)
			index = (index + 1) % tableSize;

		it = table[index].middleElement;

		if (table[index].head == NULL)
		{
			newNode = new node;
			table[index].head = table[index].middleElement = newNode;
			table[index].head->prev = table[index].head->next = NULL;
			table[index].head->key = key;
			table[index].head->value = type2();
			table[index].amount++;
			return table[index].head->value;
		}

		else
		{
			if (it->key == key)
				return it->value;
			if (it->key < key)
			{
				while (it != NULL)
				{
					it = it->next;

					// Matching key found --> return value field
					if (it->key == key)
						return it->value;
					
					// Not in list
					else  
					{	
						// table[index].amount < MAX_ELEMENTS
						if (it->key > key && it->prev->key < key && table[index].amount < MAX_ELEMENTS)
						{
							node * insertNode;
							insertNode = new node;
							
							// Insert node before it
							insertNode->prev = it->prev;
							insertNode->next = it;
							it->prev->next = insertNode;
							it->prev = insertNode;

							// Set node's key, value, and increment table[index].amount
							insertNode->key = key;
							insertNode->value = type2();
							table[index].amount++;

							// Increment filledEntries if table[index].amount = MAX_AMOUNT
							if (table[index].amount == MAX_ELEMENTS)
								filledEntries++;
							
							loadFactor = filledEntries / tableSize;

							if (loadFactor >= 0.5)
								resize(tableSize*2);

							// If left insert causes an even amount, move middle 1 to the left
							if (table[index].amount % 2 == 0)
								table[index].middleElement = table[index].middleElement->prev;
							
							// Return value field
							return insertNode->value;
						}

						// if (table[index].amount == MAX_ELEMENTS)
						// 	it = table[(index + 1) % tableSize];
					}
				}
			}

			// Traverse left direction
			if (it->key > key)
			{
				while (it != NULL)
				{
					it = it->prev;

					// Matching key found --> return value field
					if (it->key == key)
						return it->value;
					
					// Not in list
					else  
					{	
						// table[index].amount < MAX_ELEMENTS
						if (it->key > key && it->prev->key < key && table[index].amount < MAX_ELEMENTS)
						{
							node * insertNode;
							insertNode = new node;
							
							// Insert node before it
							insertNode->prev = it->prev;
							insertNode->next = it;
							it->prev->next = insertNode;
							it->prev = insertNode;

							// Set node's key, value, and increment table[index].amount
							insertNode->key = key;
							insertNode->value = type2();
							table[index].amount++;

							// Increment filledEntries if table[index].amount = MAX_AMOUNT
							if (table[index].amount == MAX_ELEMENTS)
								filledEntries++;
							
							loadFactor = filledEntries / tableSize;

							if (loadFactor >= 0.5)
								resize(tableSize);

							// If left insert causes an even amount, move middle 1 to the left
							if (table[index].amount % 2 == 0)
								table[index].middleElement = table[index].middleElement->prev;
							
							// Return value field
							return insertNode->value;
						}

						// if (table[index].amount == MAX_ELEMENTS)
						// 	it = table[(index + 1) % tableSize];
					}
				}
			}

		}
	} while (table[index].amount == MAX_ELEMENTS);
}

template <class type1, class type2>
int hashMap<type1, type2>::hashFunction(std::string key) const
{
	int charCount;

	for (int i = int(key[0]); i < key.length(); i++)
		charCount += int(key[i]);

	return charCount % tableSize;
}

template <class type1, class type2>
void hashMap<type1, type2>::resize(int amt)
{
	list * oldTable = table;
	int oldSize = tableSize;
	tableSize += amt;
	filledEntries = 0;
	table = new list[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		table[i].head = NULL;
		table[i].middleElement = NULL;
		table[i].amount = 0;
	}

	node * it;

	//goes through each table entry of the oldTable (obsolete table)
	//and maps them to an element of the new table and stores the same
	//value into the location where it's found in the new table
	for (int i = 0; i < oldSize; i++)
		for (it = oldTable[i].head; it != NULL; it = it->next)
			(*this)[it->key] = it->value;


	//Deallocate old table
	for (int i = 0; i < oldSize; i++)
	{
		node * del1, * del2;
		del1 = oldTable[i].head;

		while (del1 != NULL)
		{
			del2 = del1->next;
			delete del1;
			del1 = del2;
		}
	}
	delete [] oldTable;
}