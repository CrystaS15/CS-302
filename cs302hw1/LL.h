/*
* Name: Kristy Nguyen, 5006243601, Assignment #1
* Description: (LL header file) A game board in which the game 15 puzzle can be played
* Input: input file name, single char to make a move, response char to continue or not
* Output: puzzle
*/

#include <iostream>
using namespace std;

/*
* class_identifier: a doubly linked list
* constructors:
	LL();
	LL(const LL&);
	~LL();
* public functions:
	const LL& operator=(const LL&);
	iterator begin() const;
	iterator end() const;
	void headRemove();
	void tailRemove();
	void removeNode(const iterator&);
	bool isEmpty() const;
	void headInsert(const Type&);
	void tailInsert(const Type&);
	void update(const iterator&, const Type&);
*/
template <class Type>
class LL
{
	struct node
	{
		Type item;
		node * next;
		node * prev;
	};
public:
	
	/*
	* class_identifier: iterator
	* constructors: 
		iterator();
		iterator(node*);
	* public functions:
		Type operator*();
		iterator operator++(int);
		iterator operator--(int);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	*/
	class iterator
	{
	public:
		friend class LL;
		iterator();
		iterator(node*);
		Type operator*();
		iterator operator++(int);
		iterator operator--(int);
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;
	private:
		node * current;
	};

	LL();
	LL(const LL&);
	const LL& operator=(const LL&);
	~LL();
	iterator begin() const;
	iterator end() const;
	void headRemove();
	void tailRemove();
	void removeNode(const iterator&);
	bool isEmpty() const;
	void headInsert(const Type&);
	void tailInsert(const Type&);
	void update(const iterator&, const Type&);
private:
	node * head;
	node * tail;
};

// constructor_identifier: iterator default constructor
template <class Type>
LL<Type>::iterator::iterator() {
	current = nullptr;
}

// constructor_identifier: iterator non-default constructor
template <class Type>
LL<Type>::iterator::iterator(node * pointer) {
	current = pointer;
}

/*
* function_identifier: returns item field of node that current points to
* return value: Type
*/
template <class Type>
Type LL<Type>::iterator::operator*() {
	return current->item;
}

/*
* function_identifier: sets current pointer to next node
* return value: typename
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator++ (int) {
	current = current->next;
	return *this;
}

/*
* function_identifier: sets current pointer to previous node
* return value: typename
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator-- (int) {
	current = current->prev;
	return *this;
}

/*
* function_identifier: returns true if (*this==*rhs) and false otherwise
* parameters: rhs object
* return value: bool
*/
template <class Type>
bool LL<Type>::iterator::operator==(const iterator& rhs) const {
	if (*this == *rhs)
		return true;
	return false;
}

/*
* function_identifier: returns false if (*this==*rhs) and true otherwise
* parameters: rhs object
* return value: bool
*/
template <class Type>
bool LL<Type>::iterator::operator!=(const iterator& rhs) const {
	if (*this == *rhs)
		return false;
	return true;
}

// constructor_identifier: LL default constructor, assigns NULL to head and tail
template <class Type>
LL<Type>::LL() {
	head = nullptr;
	tail = nullptr;
}

// constructor_identifier: LL copy constructor, performs deep copy of copy object to *this object
template <class Type>
LL<Type>::LL(const LL& copy) {
	this->head = nullptr;
	this->tail = nullptr;
	node * newNode;

	if (this->current != nullptr) {
		iterator temp = iterator(head);

		while (head != nullptr) {
			temp.current = this->head;
			this->head = this->head->next;
			delete temp.current;
		}
		this->tail = nullptr;
	}

	if (copy->head == nullptr) {
		this->head = nullptr;
		this->tail = nullptr;
	}
	else
	{
		this->current = copy->head;

		this->head = new node;

		this->head->item = this->current->item;
		this->head->next = nullptr;

		this->tail = this->head;
		this->current = this->current->next;

		while (this->current != nullptr) {
			newNode = new node;
			newNode->item = this->current->item;
			newNode->next = nullptr;

			this->tail->next = newNode;
			this->tail = newNode;

			this->current = this->current->next;
		}
	}
}

/*
* function_identifier: assignment operator, performs deep copy of rhs object to *this object
* parameters: rhs object
* return value: const
*/
template <class Type>
const LL<Type>& LL<Type>::operator=(const LL& rhs) {
	if (this != &rhs)
	{
		node * newNode;

		if (this->current != nullptr) {
			iterator temp = iterator(head);

			while (head != nullptr) {
				temp.current = this->head;
				this->head = this->head->next;
				delete temp.current;
			}
			this->tail = nullptr;
		}

		if (rhs->head == nullptr) {
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			this->current = rhs->head;

			this->head = new node;

			this->head->item = this->current->item;
			this->head->next = nullptr;

			this->tail = this->head;
			this->current = this->current->next;

			while (this->current != nullptr) {
				newNode = new node;
				newNode->item = this->current->item;
				newNode->next = nullptr;

				this->tail->next = newNode;
				this->tail = newNode;

				this->current = this->current->next;
			}
		}
	}
	return *this;
}

// destructor_identifier: deallocates the linked list
template <class Type>
LL<Type>::~LL() {
	iterator it = iterator(head);
	node * temp;

	while (it.current != nullptr) {
		temp = it.current;
		it++;
		delete temp;
	}
	tail = nullptr;
}

/*
* function_identifier: returns iterator object whose current is assigned with head pointer
* return type: typename
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::begin() const {
	iterator it = iterator(head);
	return it;
}

/*
* function_identifier: returns iterator object whose current is assigned with tail pointer
* return type: typename
*/
template <class Type>
typename LL<Type>::iterator LL<Type>::end() const {
	iterator it = iterator(tail);
	return it;

}

/*
* function_identifier: removes node from linked list
* parameters: iterator that points to node to be removed
*/
template <class Type>
void LL<Type>::removeNode(const iterator& it) {
	iterator traverse = iterator(head);
	// node * traverse;
	node * trailTraverse;

	// traverse = head;
	while (traverse != it)
		traverse++;
	
	trailTraverse = traverse->prev;
	trailTraverse->next = traverse->next;

	// if (traverse->next != nullptr)
	traverse->next->prev = trailTraverse;

	// if (traverse == tail)
	// 	tail = trailTraverse;

	delete traverse;
}

// function_identifier: removes front node
template <class Type>
void LL<Type>::headRemove() {
	iterator it = iterator(head);
	head = head->next;
	
	if (head != nullptr)
		head->prev = nullptr;
	else
		tail = nullptr;

	delete it.current;
}


// function_identifier: removes end node
template <class Type>
void LL<Type>::tailRemove() {
	iterator it = iterator(head);
	node * trailCurrent;

	while (it.current->next != nullptr)
		it++;

	trailCurrent = it.current->prev;
	trailCurrent->next = it.current->next;

	// if (it.current->next != nullptr)
	// 	it.current->next->back = trailCurrent;
	
	tail = trailCurrent;

	delete it.current;
}

/*
* function_identifier: returns true if list is empty and false otherwise
* return type: bool
*/
template <class Type>
bool LL<Type>::isEmpty() const {
	iterator it = iterator(head);
	
	return (it.current == nullptr);
}

/*
* function_identifier: inserts new node to front of linked list
* parameters: element to be inserted
*/
template <class Type>
void LL<Type>::headInsert(const Type& element) {
	iterator it = iterator(head);
	node * insert;
	insert = new node;
	insert->item = element;
	insert->next = NULL;
	head = insert;
	insert = NULL;	
}

/*
* function_identifier: inserts new node to end of linked list
* parameters: element to be inserted
*/
template <class Type>
void LL<Type>::tailInsert(const Type& element) {
	iterator it = iterator(head);
	// node * traverse;
	// traverse = head;

	while (it.current->next != NULL)
		it++;
	// while (traverse->next != NULL)
	// 	traverse = traverse->next;

	node * insert;
	insert = new node;
	insert->item = element;
	insert->next = it.current->next;
	it.current->next = insert;
	insert->prev = it.current;
	tail = insert;
	tail->next = NULL;
	
	
}

/*
* function_identifier: assigns item field of iterator object with element passed in
* parameters: iterator object, element
*/
template <class Type>
void LL<Type>::update(const LL<Type>::iterator & it, const Type& element) {
	it.current->item = element;
}