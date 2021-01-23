/* LIST LIBRARY */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
///////////////////////////////////////////////////////////////////////////////////////////////////
CLIENT RESPONSIBILITIES

COPY CONSTRUCTOR : Insertion will invoke the underlying data's copy constructor

== : Collisions are not yet supported in the Dll data structures, therefore if a duplicate is found
an error message will be prompted.

<< : Display will use this with std::cout as the left operand
///////////////////////////////////////////////////////////////////////////////////////////////////
*/

#ifndef LIST_LIBRARY_H_ 
#define LIST_LIBRARY_H_ 

#include <iostream>

/////////////////////////////////////////////////// LIST LIBRARY NAMESPACE 

namespace list_library
{

//// FORWARD DECLARATIONS
template <typename T>
class Node;

template <typename T>
class Dll;

template <typename T>
class ArrayDll;

//// CONSTANT
//the default size of the array of lists
const int DEFAULT_SIZE = 2;

/////////////////////////////////////////////////// GLOBAL OVERLOADS

template <typename T>
std::ostream& operator<<(std::ostream&, const Dll<T>&);

template <typename T>
std::ostream& operator<<(std::ostream&, const ArrayDll<T>&);

/////////////////////////////////////////////////// DLL NODE 

template <typename T>
class Node
{
    public:
    ///////////////////////////////// CONSTRUCTORS 

    //DEFAULT
    Node() : next(nullptr), previous(nullptr), data(nullptr) {}

    //COPY
    Node(const Node& source) : next(nullptr), previous(nullptr), data(nullptr)
    {
        if (source.data) data = new T(*source.data);
    }

    //INITIALIZATION
    Node(const T& _data) : next(nullptr), previous(nullptr)
    {
        data = new T(_data);
    }

    //DESTRUCTOR
	~Node()
    {
        delete data;
        previous = nullptr;
        delete next;
        next = nullptr;
    }

    ///////////////////////////////// PUBLIC FUNCTIONS

    //insert |data| into the ostream |out|
    void display(std::ostream& out = std::cout) const
    {
        if (data) out << *data << '\n';
    }

    //set |next| and |previous| to null
    void unlink()
    {
        next = previous = nullptr;
    }

    ///////////////////////////////// GETTERS 

    Node*& _next() { return next; }
    Node*& _previous() { return previous; }

    T*& _data() { return data; }

    private:
    ///////////////////////////////// DATA 
    
    //the next node in the DLL
    Node* next;

    //the previous node in the DLL
    Node* previous;

    //the data that the list manages
    T* data;
};

/////////////////////////////////////////////////// DLL 

template <typename T>
class Dll
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    //make a deep copy of source into this list 
    Dll& operator=(const Dll& source)
    {
        //check for self-assignment
        if (this != &source) source.duplicate(*this);

        return *this;
    }

    //traverse the DLL, inserting all keys into |out|
    friend std::ostream& operator<<(std::ostream& out , const Dll& list)
    {
        list.display(list.head, out);
        return out;
    }

    ///////////////////////////////// CONSTRUCTORS 

    //DEFAULT
    Dll() : head(nullptr), tail(nullptr) {}

    //COPY
    Dll(const Dll& source) : head(nullptr), tail(nullptr)
    {
        source.duplicate(*this);
    }

    //DESTRUCTOR
	~Dll() { clear(); }

    ///////////////////////////////// PUBLIC FUNCTIONS

    //display the entire list
    void display() const
    {
        display(head);
    }

    //attempt to retrieve an item that matches |retrievalKey| of type |K|
    //if a match is found, return a pointer to the item
    // " == " operator must be overloaded by the data of type |T| to handle comparison with type |K|
    //|K| defaults to |T|
    template <typename K = T>
    T* retrieve(const K& retrievalKey) const
    {
        return retrieve(head, retrievalKey);
    }

    //insert |toInsert| into the list
    //if a duplicate of |toInsert| is found, throw an exception
    bool insert(const T& toInsert)
    {
        if (!head)
        {
            head = new Node<T>(toInsert);
            tail = head;

            return true;
        }

        return insert(head, toInsert);
    }
    
    //attempt to remove a key that matches |removalKey| of type |K|
    // " == " operator must be overloaded by the data of type |T| to handle comparison with type |K|
    //|K| defaults to |T|
    template <typename K = T>
    bool remove(const K& removalKey)
    {
        return remove(head, removalKey);
    }

    //make a duplicate of this list into |copy|
    void duplicate(Dll& copy) const
    {
        //check if copy already contains a list
        if (copy.head) copy.clear();

        duplicate(head, copy.head);
    }

    //deallocate the entire list
    void clear()
    {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    private:
    ///////////////////////////////// DATA 

    //the head of the doubly linked list
    Node<T>* head;

    //the tail of the doubly linked list
    Node<T>* tail;

    ///////////////////////////////// PRIVATE FUNCTIONS

    //traverse with |head| displaying with ostream |out|
    void display(Node<T>* head, std::ostream& out = std::cout) const
    {
        if (!head) return;

        head->display(out);
        display(head->_next());
    }

    //traverse the list with |head|
    //if a match to |retrievalKey| is found, return a pointer to the item
    template <typename K = T>
    T* retrieve(Node<T>* head, const K& retrievalKey) const
    {
        if (!head) return nullptr;

        //if a match is found, return a deep copy, otherwise continue traversal
        return (*head->_data() == retrievalKey ?
        head->_data() : retrieve(head->_next(), retrievalKey));
    }

    //traverse the list with |head|
    //if a duplicate to |toInsert| is found in the list, return false
    bool insert(Node<T>*& head, const T& toInsert)
    {
        if (toInsert == *head->_data()) return false;

        if (!head->_next())
        {
            //allocate a new tail
            tail = new Node<T>(toInsert);
            
            //link up the new tail
            head->_next() = tail;
            tail->_previous() = head;

            return true;
        }

        return insert(head->_next(), toInsert);
    }

    //traverse the list with |head|
    //if a match is found, remove it, and return true
    template <typename K = T>
    bool remove(Node<T>*& head, const K& removalKey)
    {
        //no match was found
        if (!head) return false;

        //a match was found
        if (*head->_data() == removalKey)
        {
            //hold onto the rest of the list
            Node<T>* hold = head->_next();
            if (hold) hold->_previous() = head->_previous();

            //reassign tail if removing at tail
            if (tail == head) tail = head->_previous();

            //unlink and deallocate
            head->unlink();
            delete head;

            //link back up
            head = hold;

            return true;
        }

        return remove(head->_next(), removalKey);
    }

    //traverse the list with |head| making deep copies into |copy|
    void duplicate(Node<T>* head, Node<T>*& copy, Node<T>* previous = nullptr) const
    {
       if (!head) return;

       copy = new Node<T>(*head);
       copy->_previous() = previous;
       previous = copy;

       duplicate(head->_next(), copy->_next(), previous);
    }
};

/////////////////////////////////////////////////// ARRAY OF DLL 

template <typename T>
class ArrayDll
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    //subscript operator will allow the client to access a specific DLL in the array
    Dll<T>& operator[](const int& index) const
    {
        if (index < 0 || index >= size) throw std::out_of_range("[] index out of bounds");
        
        return table[index];
    }

    //insert all contents of the array of lists into ostream |out|
    friend std::ostream& operator<<(std::ostream& out, const ArrayDll<T>& table)
    {
        table.display(out);

        return out;
    }

    ///////////////////////////////// CONSTRUCTORS 

    //DEFAULT : array size of 2
    ArrayDll() : table(nullptr), size(DEFAULT_SIZE)
    {
        //allocate an array of default size 2
        table = new Dll<T>[size];
    }

    //COPY
    ArrayDll(const ArrayDll& source) : table(nullptr)
    {
        source.duplicate(*this);
    }

    //INITIALIZATION
    ArrayDll(const int& _size) : table(nullptr), size(_size)
    {
        //check invalid init values
        if (size <= 0) size = DEFAULT_SIZE;

        //allocate an array of default size 2
        table = new Dll<T>[size];
    }

    //DESTRUCTOR
	~ArrayDll() { clear(); }

    ///////////////////////////////// PUBLIC FUNCTIONS

    //insert all contents of the array of lists into ostream |out|
    void display(std::ostream& out = std::cout) const
    {
        //to iterate through the array
        Dll<T>* iterator = table;

        for (int i = 0; i < size; ++i)
        {
            out << *iterator;
            ++iterator;
        }
    }

    //attempt to retrieve an item that matches |retrievalKey| of type |K|
    //if a match is found, return a pointer to the item
    // " == " operator must be overloaded by the data of type |T| to handle comparison with type |K|
    //|K| defaults to |T|
    template <typename K = T>
    T* retrieve(const K& retrievalKey) const
    {
        //to catch a retrieve item
        T* retrieved = nullptr;

        //to iterate through the array
        Dll<T>* iterator = table;

        for (int i = 0; !retrieved && i < size; ++i)
        {
            retrieved = iterator->retrieve(retrievalKey);
            ++iterator;
        }

        return retrieved;
    }

    //attempt to insert into the first list that |toInsert| is unique to
    //if |toInsert| is not unique to either list, prompt a warning message
    void insert(const T& toInsert)
    {
        //to determine if the insert succeeded
        bool success = false;

        //to iterate through the array
        Dll<T>* iterator = table;

        for (int i = 0; !success && i < size; ++i)
        {
            success = iterator->insert(toInsert);
            ++iterator;
        }

        if (!success)
        {
            std::cout << "ArrayDll WARNING : INSERT FAILED : duplicate data in array of dll\n"
            << "ATTEMPTED INSERT KEY : " << toInsert << "\n\n";
        }
    }

    //attempt to remove a key that matches |removalKey| of type |K|
    // " == " operator must be overloaded by the data of type |T| to handle comparison with type |K|
    //|K| defaults to |T|
    template <typename K = T>
    void remove(const K& removalKey)
    {
        //to determine if the remove succeeded at least in one list
        bool success = false;

        //to iterate through the array
        Dll<T>* iterator = table;

        for (int i = 0; i < size; ++i)
        {
            //set success, if it has not already been set to true once
            if (!success) success = iterator->remove(removalKey);
            else iterator->remove(removalKey);

            ++iterator;
        }

        if (!success)
        {
            std::cout << "Dll WARNING : REMOVAL FAILED : no matching key was found\n"
            << "ATTEMPTED REMOVAL KEY : " << removalKey << "\n\n";
        }
    }

    //make a deep copy of this array of DLL into |copy|
    void duplicate(ArrayDll& copy) const
    {
        //clear old array if one exists
        if (copy.table) copy.clear();

        copy.size = size;
        copy.table = new Dll<T>[size];

        //iterate throught the array, deep copying all lists from |source|
        Dll<T>* iterator = table;

        for (int i = 0; i < size; ++i)
        {
            copy[i] = *iterator;
            ++iterator;
        }
    }

    //deallocate the entire array of DLL
    void clear()
    {
        delete [] table;
        table = nullptr;
    }

    private:
    ///////////////////////////////// DATA 

    //the array of doubly linked lists
    Dll<T>* table;

    // the size of |table|
    int size;
};

} /////////////////////////////////////////////////// END LIST LIBRARY NAMESPACE 

#endif
