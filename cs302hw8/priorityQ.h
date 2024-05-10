template <class Type>
class priorityQ
{
public :
    priorityQ (int = 10);
    priorityQ ( const priorityQ < Type >&);
    ~ priorityQ ();
    const priorityQ < Type >& operator =( const priorityQ < Type >&);
    void insert ( const Type &);
    void deleteHighestPriority ();
    Type getHighestPriority () const ;
    bool isEmpty () const ;
    void bubbleUp (int );
    void bubbleDown (int );
    int getSize () const ;
private :
    int capacity ;
    int items ;
    Type * heapArray ;
};

template <class Type>
priorityQ<Type>::priorityQ(int capacity) {
    this->capacity = capacity;
    items = 0;

    heapArray = new Type[this->capacity];

    // for (int i = 0; i < this->capacity; i++) {
    //     heapArray[i] = NULL;
    // }
}

template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy) {
    *this = copy;
}

template <class Type>
priorityQ<Type>::~priorityQ() {
    delete [] heapArray;
}

template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs) {
    if (this != &rhs) // check for self assignment
    {
        delete [] this->heapArray;                  // destroy heapArray

        this->capacity  = rhs.capacity;             // Copy member variables
        this->items     = rhs.items;

        this->heapArray = new int [this->capacity]; // allocate new heapArray

        for (int i = 0; i < this->capacity; i++)    // copies rhs.heapArray into
            this->heapArray[i] = rhs.heapArray[i];  //      this->heapArray
    }
    return *this;
}

template <class Type>
void priorityQ<Type>::insert(const Type& element) {
    items++;
    heapArray[items] = element;
    bubbleUp(items);
}

template <class Type>
void priorityQ<Type>::deleteHighestPriority() {
    if (!isEmpty()) {
        heapArray[1] = heapArray[items];
        items--;
        bubbleDown(1);
    }
}

template <class Type>
Type priorityQ<Type>::getHighestPriority() const {
    return heapArray[1];
}

template <class Type>
bool priorityQ<Type>::isEmpty() const {
    return heapArray == NULL;
}

template <class Type>
void priorityQ<Type>::bubbleUp(int index) {
    Type temp;

    while (heapArray[index] < heapArray[index/2]) {
        temp = heapArray[index];
        heapArray[index] = heapArray[index/2];
        heapArray[index/2] = temp;
        index /= 2;
    }
}

template <class Type>
void priorityQ<Type>::bubbleDown(int index) {
    int smaller;

    do 
    {
        if (index*2 <= items && index*2+1 <= items)
        {
            // Left child is smaller
            if (heapArray[index*2] < heapArray[index*2+1])
                smaller = index*2;
            // Right child is smaller
            if (heapArray[index*2+1] < heapArray[index*2])
                smaller = index*2+1;
        }
        else
        {   
            // Left child is in bounds but not right child
            if (index*2 <= items && index*2+1 > items)
                smaller = index*2;
            // Right child is in bounds but not left child
            if (index*2 > items && index*2+1 <= items)
                smaller = index*2+1;
        }

        Type temp = heapArray[index];
        heapArray[index] = heapArray[smaller];
        heapArray[smaller] = temp;
        index = smaller;
    } while (heapArray[smaller] < heapArray[index]);
}

template <class Type>
int priorityQ<Type>::getSize() const {
    return items;
}