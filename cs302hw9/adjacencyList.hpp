template <class Type>
class vertex
{
    struct node
    {
        Type item ;
        node * link ;
    };
    public :
        class edgeIterator
        {
            public :
                friend class vertex ;
                edgeIterator ();
                edgeIterator ( node *);
                edgeIterator operator ++( int );
                Type operator *();
                bool operator ==( const edgeIterator &);
                bool operator !=( const edgeIterator &);
            private :
                node * current ;
        };
        vertex ();
        vertex ( const vertex < Type >&);
        const vertex & operator =( const vertex < Type >&);
        ~ vertex ();
        edgeIterator begin ();
        edgeIterator end ();
        void addEdge ( const Type &);
    private :
        node * neighbors ;
};

// constructor_identifier: default constructor that sets current to NULL
template <class Type>
vertex<Type>::edgeIterator::edgeIterator() 
{
    current = nullptr;
}

/* constructor_identifier: constructor that assigns current to node object
 * parameters: node object (edge) 
 */
template <class Type>
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge) 
{
    current = edge;
}

/* function_identifier: sets iterator to point to next node
 * parameters: int to denote postfix operator
 * return value: current object pointing to next node 
 */
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int) 
{
    current = current->link;
    return *this;
}

/* function_identifier: dereferences the iterator
 * return value: item field of the node that current points to 
 */
template <class Type>
Type vertex<Type>::edgeIterator::operator*() 
{
    return current->item;
}

/* function_identifier: compares address of iterator on left side with 
                        iterator on right side
 * parameters: edgeIterator object (rhs)
 * return value: true if both point to the same node, false otherwise 
 * */
template <class Type>
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs) 
{
    if (this->current == rhs.current)
        return true;
    return false;
}

/* function_identifier: compares address of iterator on left side with 
                        iterator on right side
 * parameters: edgeIterator object (rhs)
 * return value: returns false if both point to same node, true otherwise 
 */
template <class Type>
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs) 
{
    if (this->current == rhs.current)
        return false;
    return true;
}

// constructor_identifier: default constructor that sets neighbors to NULL
template <class Type>
vertex<Type>::vertex() 
{
    neighbors = nullptr;
}

/* constructor_identifier: copy constructor that deep copies the neighbor list 
                           of object passed into the constructor to 
                           the object that calls the constructor
 * parameters: vertex object (copy) 
 */
template <class Type>
vertex<Type>::vertex(const vertex<Type>& copy) 
{
    neighbors = nullptr;
    *this = copy;
}

/* function_identifier: performs deep copy of right side object with 
                        left side object 
                        (the object that calls the operator function)
 * parameters: right side vertex object (rhs) */
template <class Type>
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs) 
{
    node *newNode, *current, *last;
    if (this != &rhs) 
    {   // Check for self assignment
        
        while (neighbors != nullptr)
        {   // Destroy linked list
            if (neighbors != nullptr)
            {   // Only remove if list is NOT empty, otherwise seg fault occurs
                if (neighbors->link == nullptr)
                {   // Only 1 node in linked list
                    delete neighbors;
                    neighbors = nullptr;
                }
                else
                {   // More than 1 node in linked list
                    node * del = neighbors;
                    neighbors = neighbors->link;
                    delete del;
                }
            }
        }

        if (rhs.neighbors == nullptr)
            neighbors = nullptr;
        else
        {   // Create new linked list
            current = rhs.neighbors;    // current points to linked list to copy
            
            // Copy the head of the linked list
            neighbors = new node;                   // create node
            neighbors->item = rhs.neighbors->item;  // copy the info
            neighbors->link = nullptr;              // set next field to null
            last = neighbors;                       // set last to point to the node
            current = current->link;                // set current to point to next node to be copied

            while (current != nullptr)
            {   // Copy the remaining stack
                newNode = new node;             // create node
                newNode->item = current->item;  // copy the info into new node
                newNode->link = nullptr;           // set next field to null
                last->link = newNode;           // set the previous node's next field to node just created
                last = newNode;                 // set last to point to the node
                current = current->link;        // set current to point to next node to be copied
            }

        }

    }
}

// destructor_identifier: deallocates all the nodes in its neighbor list
template <class Type>
vertex<Type>::~vertex() 
{
    node * temp;                        // pointer to delete node

    while (neighbors != nullptr)           // while there are elements in
    {                                   // the stack
        temp = neighbors;               // temp points to current node
        neighbors = neighbors->link;    // advance current node to next node
        delete temp;                    // deallocate memory occupied by temp
    }
}

/* function_identifier: returns edgeIterator object whose current 
                        will be the head of neighbor list for the vertex object
 * return value: edgeIterator (current) pointing to 
                 head of neighbor list for vertex object 
 */
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::begin() 
{
    return vertex<Type>::edgeIterator(neighbors);
}

/* function_identifier: returns edgeIterator object whose current 
                        will be assigned to NULL
 * return value: edgeIterator (current) assigned to NULL 
 */
template <class Type>
typename vertex<Type>::edgeIterator vertex<Type>::end() 
{
    return vertex<Type>::edgeIterator(nullptr);
}

/* function_identifier: adds a new node into neighbor list (head insert)
 * parameters: const Type object (edge) 
 */
template <class Type>
void vertex<Type>::addEdge(const Type& edge) 
{
    node * newNode;             // pointer to create new node

    newNode = new node;         // create new node

    newNode->item = edge;       // store edge in newNode
    newNode->link = neighbors;  // insert new node before head
    neighbors = newNode;        // set head to point to top node
}