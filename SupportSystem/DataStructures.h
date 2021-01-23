//Sean Siders
//CS202
//Program 1 : Support System
//Oct 16, 2020

/*
This file contains all of the class interfaces that manage the data structures for this program. The
data structures store objects that exist within the support system class hierarchy. A class template
is implemented for a circular linked list, and it's respective node class. This allows the same
implementation of this data structure to support any of the classes in the hierarchy of the support
system. |Database| is a class that abstracts the managing of the 3 possible derived class circular
linked lists into one object. Also, when a retrieval function is called on one of the three lists, a
linear linked list is used to keep track of a history of data that has been retrieved.
*/

#include "SupportSystem.h"

#ifndef DATASTRUCTURES_H_
#define DATASTRUCTURES_H_

/////////////////////////////////////// NODE CLASSES

/*
This node class template is used for all 3 circular linked lists.  The basic operations of this
class allow initialization of data, and traversal through the linear data structures.
*/

template <typename T>
class Node : public T
{
    public:
    Node();

    //initialization constructor
    //invokes the copy constructor of |T|
    Node(const T& source);

    ~Node();

    ///////////// PUBLIC FUNCTIONS

    //return |next|
    Node*& getNext();

    //set |next| to |_next|
    void setNext(Node* _next);

    private:
    Node* next;
};

/*
|CountingNode| has the basic operations of a node, and has an internal counting feature. This is
used for the linear linked list managed by |Database| that hold the user's search history.
*/

class CountingNode
{
    public:
    CountingNode();

    //copy constructor
    CountingNode(const CountingNode& other);

    //initialization constructor
    CountingNode(const char* _name);

    ~CountingNode();

    //return |next|
    CountingNode*& getNext();

    //set |next| to |_next|
    void setNext(CountingNode* _next);

    //display |name| and |count|
    void display() const;

    //compare |name| and |_name|
    //if they match, return true;
    bool isMatch(const char* _name) const;

    //return the difference of |count| and |other.count|
    int compareCount(CountingNode& other);

    //add 1 to the count for this node
    void incrementCount();

    private:
    char* name;
    int count;
    CountingNode* next;
};

/////////////////////////////////////// DATA STRUCTURES CLASSES

/*
|ShelterList|, |FoodList|, and |ClothingList| are separate implementations of a circular linked list
that all use the template |Node| as a node in their data structures. The three structures are
abstracted due to some of the unique operations involving the underlying data that the list is
holding. |display|, and |insert| are identical for all 3 however.
*/

template <typename T>
class CircularList 
{
    public:
    CircularList();

    //copy constructor
    CircularList(const CircularList& other);

    ~CircularList();

    ///////////// PUBLIC FUNCTIONS

    //display all items of type |T| in the list
    void display() const;

    //insert |toInsert| into the front of the circular list
    void insert(const T& toInsert);

    //attempt to remove an item from the list by name
    //true if removal was successful
    bool remove(const char* toRemove);

    //search for an item by name
    //return true if a match is found
    bool search(const char* _supportName, T& retrieveCopy);

    //duplicate this list into |destination|
    void duplicate(Node<T>*& destination) const;

    private:
    Node<T>* rear;

    ///////////// PRIVATE FUNCTIONS

    void display(Node<T>* rear) const;
    bool remove(const char* toRemove, Node<T>*& rear);
    bool search(const char* _supportName, T& retrieveCopy, Node<T>* rear);
    void duplicate(Node<T>* destRear, Node<T>*& destination, Node<T>* rear) const;
};

class Database
{
    public:
    Database();

    //copy constructor
    Database(const Database& other);

    ~Database();

    ///////////// PUBLIC FUNCTIONS

    //insert at the beginning of the linear linked list
    //this is done whenever the user searches for a relief effort in the system
    void historyInsert(const char* toInsert);

    //attempt to remove an item from the search history LLL
    //false if removal fails
    bool historyRemove(const char* toRemove);

    //insert an item into its respective list object
    void insert(const Shelter& toInsert);
    void insert(const Food& toInsert);
    void insert(const Clothing& toInsert);

    //remove an item from its respective list object
    //true if a match was found to remove
    //this function will attempt removal from all 3 CLLs
    bool remove(const char* toRemove);

    //display all three of the lists in the database
    void display() const;

    //display the search history linear linked list
    void displaySearchHistory() const;

    //search for a relief effort in a respective CLL
    //return true if a match is found
    //|search| is overloaded for each derived class to retrieve a copy of the object if a match is found
    bool search(const char* supportName, Shelter& retrieveCopy);
    bool search(const char* supportName, Food& retrieveCopy);
    bool search(const char* supportName, Clothing& retrieveCopy);

    //duplicate the search history LLL into |destination|
    void duplicate(CountingNode*& destination) const;

    private:

    //circular linked list objects
    CircularList<Shelter> shelterList;
    CircularList<Food> foodList;
    CircularList<Clothing> clothingList;

    //head of the linear linked list for search history
    CountingNode* head;

    ///////////// PRIVATE FUNCTIONS

    bool historyRemove(const char* toRemove, CountingNode*& head);

    //check to see if |name| already exists in a node in the list
    //false if no match was found
    //if a match is found, increment the search count within |CountingNode|
    bool previouslySearched(const char* name, CountingNode*& head);

    //find the new location for |toSort| in the list
    //|CountingNode| internally counts the value that the list sorts by
    //|sort| is called whenever a node's count is incremented
    void sort(CountingNode*& toSort, CountingNode*& head);

    void displaySearchHistory(CountingNode* head) const;
    void duplicate(CountingNode*& destination, CountingNode* head) const;
};

#endif
