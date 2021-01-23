//Sean Siders
//CS202
//Program 1 : Support System
//Oct 16, 2020

/*
All data structures are implemented in this file. Any algorithms involving traversal through a
linear list are implemented with recursive functions. Display, insert, remove, retrieval and
complete deallocation are implemented for both the template circular linked list, and the linear
linked list that is used for search history.
*/

#include "DataStructures.h"

/////////////////////////////////////// DEFAULT CONSTRUCTORS

template <typename T>
Node<T>::Node() : next(nullptr) {}

CountingNode::CountingNode() : name(nullptr), count(0), next(nullptr) {}

template <typename T>
CircularList<T>::CircularList() : rear(nullptr) {}

Database::Database() : head(nullptr) {}

/////////////////////////////////////// COPY CONSTRUCTORS

CountingNode::CountingNode(const CountingNode& other) : count(other.count)
{
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

template <typename T>
CircularList<T>::CircularList(const CircularList& other) : rear(nullptr)
{
    other.duplicate(rear);
}

Database::Database(const Database& other) : shelterList(other.shelterList),
    foodList(other.foodList), clothingList(other.clothingList), head(nullptr)
{
    other.duplicate(head);
}

/////////////////////////////////////// INITIALIZATION CONSTRUCTORS

template <typename T>
Node<T>::Node(const T& source) : T(source), next(nullptr) {}

CountingNode::CountingNode(const char* _name) : name(nullptr), count(1), next(nullptr)
{
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

/////////////////////////////////////// DESTRUCTORS

template <typename T>
Node<T>::~Node()
{
    delete next;
    next = nullptr;
}

CountingNode::~CountingNode()
{
    delete [] name;

    delete next;
    next = nullptr;
}

template <typename T>
CircularList<T>::~CircularList()
{
    if (!rear) return;

    Node<T>* front = rear->getNext();
    rear->setNext(nullptr);

    delete front;
    front = nullptr;
    rear = nullptr;
}

Database::~Database()
{
    delete head;
    head = nullptr;
}

/////////////////////////////////////// NODE 

//return |next|
template <typename T>
Node<T>*& Node<T>::getNext()
{
    return next;
}

//set |next| to |_next|
template <typename T>
void Node<T>::setNext(Node* _next)
{
    next = _next;
}

/////////////////////////////////////// COUNTING NODE 

//return |next|
CountingNode*& CountingNode::getNext()
{
    return next;
}

//set |next| to |_next|
void CountingNode::setNext(CountingNode* _next)
{
    next = _next;
}

//display |name| and |count|
void CountingNode::display() const
{
    if (!name) return;
    std::cout << name << "\nSEARCH COUNT : " << count << "\n\n";
}

//compare |name| and |_name|
//if they match, return true;
bool CountingNode::isMatch(const char* _name) const
{
    return !strcmp(name, _name);
}

//return the difference of |count| and |other.count|
int CountingNode::compareCount(CountingNode& other)
{
    return count - other.count;
}

//add 1 to the count for this node
void CountingNode::incrementCount()
{
    ++count;
}

/////////////////////////////////////// CIRCULAR LIST

//display all items of type |T| in the list
//wrapper
template <typename T>
void CircularList<T>::display() const
{
    if (!rear) return;

    display(rear->getNext());
}

//recursive
template <typename T>
void CircularList<T>::display(Node<T>* rear) const
{
    rear->display();
    if (rear == this->rear) return;

    display(rear->getNext());
}

//insert |toInsert| into the front of the circular list
template <typename T>
void CircularList<T>::insert(const T& toInsert)
{
    Node<T>* alloc = new Node<T>(toInsert);

    if (!rear)
    {
        rear = alloc;
        rear->setNext(rear);
        return;
    }

    alloc->setNext(rear->getNext());
    rear->setNext(alloc);
}

//attempt to remove an item from the list by name
//true if removal was successful
template <typename T>
bool CircularList<T>::remove(const char* toRemove)
{
    if (!toRemove || !rear) return false;

    return remove(toRemove, rear->getNext());
}

//recursive
template <typename T>
bool CircularList<T>::remove(const char* toRemove, Node<T>*& rear)
{
    if (rear == this->rear)
    {
        //if the match is at this->rear
        if (rear->isMatch(toRemove))
        {
            //hold onto rest of the list
            Node<T>* hold = rear->getNext();

            //delete the node
            rear->setNext(nullptr);
            delete rear;

            //link the rest of the list
            rear = hold;
            this->rear = hold;

            return true;
        }

        return false;
    }

    if (rear->isMatch(toRemove))
    {
        //hold onto rest of the list
        Node<T>* hold = rear->getNext();

        //delete the node
        rear->setNext(nullptr);
        delete rear;

        //link the rest of the list
        rear = hold;

        return true;
    }

    return remove(toRemove, rear->getNext());
}

//search for an item by name
//return true if a match is found
template <typename T>
bool CircularList<T>::search(const char* _supportName, T& retrieveCopy)
{
    if (!rear) return false;
    return search(_supportName, retrieveCopy, rear->getNext());
}

//recursive
template <typename T>
bool CircularList<T>::search(const char* _supportName, T& retrieveCopy, Node<T>* rear)
{
    if (rear->isMatch(_supportName))
    {
        rear->duplicate(retrieveCopy);
        return true;
    }

    if (rear == this->rear) return false;

    return search(_supportName, retrieveCopy, rear->getNext());
}

//duplicate this list into |destination|
//wrapper
template <typename T>
void CircularList<T>::duplicate(Node<T>*& destination) const
{
    if (!rear) return;

    //allocate rear
    destination = new Node<T>(*rear);

    duplicate(destination, destination->getNext(), rear->getNext());
}

//duplicate this list into |destination| into |rear|
//after the entire list has been copied, link |destination| to |destRear|
template <typename T>
void CircularList<T>::duplicate(Node<T>* destRear, Node<T>*& destination, Node<T>* rear) const
{
    if (rear == this->rear)
    {
        destination = destRear;
        return;
    }

    destination = new Node<T>(*rear);
    duplicate(destRear, destination->getNext(), rear->getNext());
}

/////////////////////////////////////// DATABASE

//LLL INSERT FUNCTIONS

//check if this object already exists in the list
//if the match is found, |searchFrequency| will be incremented
//this will queue a sort algorithm to keep the list sorted by frequency
void Database::historyInsert(const char* toInsert)
{
    CountingNode* alloc = new CountingNode(toInsert);

    if (!head)
    {
        head = alloc;
        return;
    }

    //the new item is unique and will be inserted at the beginning of the list
    if (!previouslySearched(toInsert, head))
    {
        alloc->setNext(head);
        head = alloc;
    }
    else delete alloc;
}

//attempt to remove an item from the search history LLL
//false if removal fails
//wrapper
bool Database::historyRemove(const char* toRemove)
{
    if (!head) return false;

    return historyRemove(toRemove, head);
}

//recursive
bool Database::historyRemove(const char* toRemove, CountingNode*& head)
{
    //end of list, no match was found
    if (!head) return false;

    //if a match was found
    if (head->isMatch(toRemove))
    {
        //hold onto the rest of the list
        CountingNode* hold = head->getNext();

        //deallocate
        head->setNext(nullptr);
        delete head;

        //link the rest of the list
        head = hold;

        return true;
    }

    return historyRemove(toRemove, head->getNext());
}

//check to see if |name| already exists in a node in the list
//false if no match was found
//if a match is found, increment the search count within |CountingNode|
bool Database::previouslySearched(const char* name, CountingNode*& head)
{
    //no match was found
    if (!head) return false;

    //match found
    if (head->isMatch(name))
    {
        head->incrementCount();

        //if there is more list to possibly sort
        if (head->getNext())
        {
            //grab the node that needs to be sorted
            CountingNode* toSort = head;

            //link past that node
            head = head->getNext();

            toSort->setNext(nullptr);

            //find the new location for |toSort)
            sort(toSort, head);
        }

        return true;
    }
    
    return previouslySearched(name, head->getNext());
}

//find the new location for |toSort| in the list
//|CountingNode| internally counts the value that the list sorts by
//|sort| is called whenever a node's count is incremented
void Database::sort(CountingNode*& toSort, CountingNode*& head)
{
    //end of list
    if (!head)
    {
        head = toSort;
        return;
    }

    //point of insertion
    if (0 <= head->compareCount(*toSort))
    {
        //hold onto the list
        CountingNode* temp = head;

        //insert the node
        head = toSort;

        //link the rest of the list
        toSort->setNext(temp);

        return;
    }

    sort(toSort, head->getNext());
}

//insert an item into its respective list object
void Database::insert(const Shelter& toInsert)
{
    shelterList.insert(toInsert);
}

void Database::insert(const Food& toInsert)
{
    foodList.insert(toInsert);
}

void Database::insert(const Clothing& toInsert)
{
    clothingList.insert(toInsert);
}

//remove an item from its respective list object
//true if a match was found to remove
//this function will attempt removal from all 3 CLLs
bool Database::remove(const char* toRemove)
{
    if (shelterList.remove(toRemove) ||
        foodList.remove(toRemove) ||
        clothingList.remove(toRemove)) return true;

    return false;
}

//display all three of the lists in the database
void Database::display() const
{
    shelterList.display();
    foodList.display();
    clothingList.display();
}

//display the search history linear linked list
//wrapper
void Database::displaySearchHistory() const
{
    displaySearchHistory(head);
}

//recursive
void Database::displaySearchHistory(CountingNode* head) const
{
    //end of list
    if (!head) return;

    head->display();
    displaySearchHistory(head->getNext());
}

//search for a relief effort in all three CLLs
//return true if a match is found
//the search history list will then sort itself to have the most frequently search items at the
//front of the list
//|search| is overloaded to optionally retrieve a copy of the object if a match is found
bool Database::search(const char* supportName, Shelter& retrieveCopy)
{
    //if a match was found |retrieveCopy| is populated
    //insert |supportName| into the search history list as a successful search
    if (shelterList.search(supportName, retrieveCopy))
    {
        historyInsert(supportName);
        return true;
    }

    return false;
}

bool Database::search(const char* supportName, Food& retrieveCopy)
{
    if (foodList.search(supportName, retrieveCopy))
    {
        historyInsert(supportName);
        return true;
    }

    return foodList.search(supportName, retrieveCopy);
}

bool Database::search(const char* supportName, Clothing& retrieveCopy)
{
    if (clothingList.search(supportName, retrieveCopy))
    {
        historyInsert(supportName);
        return true;
    }

    return clothingList.search(supportName, retrieveCopy);
}

//duplicate the search history LLL into |destination|
void Database::duplicate(CountingNode*& destination) const
{
    if (!head) return;

    duplicate(destination, head);
}

//traverse the list with |head| copying into |destination|
void Database::duplicate(CountingNode*& destination, CountingNode* head) const
{
    if (!head) return;

    destination = new CountingNode(*head);

    duplicate(destination->getNext(), head->getNext());
}
