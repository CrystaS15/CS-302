template <class Type>
class myStack
{
public:
	myStack();
	myStack(const myStack<Type>&);
	const myStack<Type>& operator=(const myStack<Type>&);
	~myStack();

	void push(const Type&);
	void pop();
	Type top() const;
	bool isEmpty() const;

private:
	struct node
	{
		Type item;
		node * next;
	};

	node * topOfmyStack;
};


template <class Type>
myStack<Type>::myStack()
{
	topOfmyStack = NULL;
}

template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
	topOfmyStack = NULL;
	*this = copy; // calls assignment operator

}

template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
	if (this != &rhs) // check for self assignment
	{
		while (!isEmpty()) // destroy linked list
			pop();

		// create new linked list
		if (!rhs.isEmpty())
		{
			while (!rhs.isEmpty()) // traverse until the end of linked list
				rhs.topOfmyStack = rhs.topOfmyStack->next;
			
			// inserts each element from rhs into linked list reference
			// one node at a time
			myStack<Type> current = NULL;
			myStack<Type> temp;
			while (!rhs.isEmpty())
			{
				temp = rhs.top();
				current.push(temp);
				rhs.pop();
			}
			
		}
	}
	return *this;
}

template<class Type>
myStack<Type>::~myStack()
{
	// destory linked list
	while (!isEmpty())
		pop();
}

template <class Type>
void myStack<Type>::push(const Type& element)
{
	node * insert = new node;
	insert->item = element;
	
	// if list is empty, then this will be the only node in the list
	// so the head pointer points to this node
	if (isEmpty())
	{
		topOfmyStack = insert;
		topOfmyStack->next = NULL;
	}
	else // generic head insert
	{
		insert->next = topOfmyStack;
		topOfmyStack = insert;
	}
	return;
}

template <class Type>
void myStack<Type>::pop()
{
	// if list is empty, then there is nothing to remove
	// and we don't want a seg fault
	if (!isEmpty())
	{
		if (topOfmyStack->next == NULL)
		{
			delete topOfmyStack;
			topOfmyStack = NULL;
		}
		else // if there's more than one node in the linked list
		{
			node * del = topOfmyStack;
			topOfmyStack = topOfmyStack->next;
			delete del;
		}
	}
}

template <class Type>
Type myStack<Type>::top() const
{
	return topOfmyStack->item;
}

template <class Type>
bool myStack<Type>::isEmpty() const
{
	return topOfmyStack == NULL; // if topOfmyStack points to NULL, list has to be empty
}