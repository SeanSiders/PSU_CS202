/* TREE LIBRARY */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
///////////////////////////////////////////////////////////////////////////////////////////////////
CLIENT RESPONSIBILITIES

COPY CONSTRUCTOR : Insertion will invoke the underlying data's copy constructor

== : Collisions are not yet supported in the data structures, therefore if a duplicate is found an
exception will be thrown.

< and > : Insertion will use these to compare the key value, and perform any necessary sorting

<< : Display will use this with std::cout as the left operand
///////////////////////////////////////////////////////////////////////////////////////////////////
*/

#ifndef TREE_LIBRARY_H_ 
#define TREE_LIBRARY_H_ 

#include <iostream>

/////////////////////////////////////////////////// TREE LIBRARY NAMESPACE 

namespace tree_library
{

//// FORWARD DECLARATIONS
template <typename T>
class Node;

template <typename T>
class Tree;

/////////////////////////////////////////////////// GLOBAL OVERLOAD 

template <typename T>
std::ostream& operator<<(std::ostream&, const Tree<T>&);

/////////////////////////////////////////////////// TREE NODE

/*
This is the node for the 2-3 tree implementation. The node will carry 2 keys, |keyL|, and |keyR|
which will be continously sorted so that |keyL| < |keyR| (duplicates are not supported). When
insertion is attempted on a full node, the median will be determined and returned as a pointer.
This in turn will signal the tree that the node needs to be split and the median needs to be
pushed up to the parent.
*/

template <typename T>
class Node
{
    public:
    ///////////////////////////////// CONSTRUCTORS 

    //DEFAULT
	Node()
    {
        //set all members to null
        keyL = keyR = nullptr;
        left = middle = right = nullptr;
    }

    //COPY
    Node(const Node& source) : keyL(nullptr), keyR(nullptr)
    {
        keyL = new T(*source.keyL);
        if (source.keyR) keyR = new T(*source.keyR);
    }

    //INITIALIZATION
    //allocate a new key in the default position |keyL|
    Node(const T& key)
    {
        //set all members to null
        keyL = keyR = nullptr;
        left = middle = right = nullptr;

        //allocate the new key, invoking the copy constructor
        keyL = new T(key);
    }

    //INITIALIZATION (move semantics)
    //move the memory of |key| into this node
    Node(T*& key)
    {
        //assign |key| to the first key |keys[0]|
        keyL = key;
        key = nullptr;

        //set all members to null
        keyR = nullptr;
        left = middle = right = nullptr;
    }

    //DESTRUCTOR
    //deallocate the keys, then recursively deallocate children
	~Node()
    {
        delete keyL;
        keyL = nullptr;

        delete keyR;
        keyR = nullptr;

        delete left;
        left = nullptr;

        delete middle;
        middle = nullptr;

        delete right;
        right = nullptr;
    }

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //display the 1 or 2 keys in this node
    void display(std::ostream& out = std::cout) const
    {
        if (keyL) out << *keyL;
        if (keyR) out << " " << *keyR;

        out << '\n';
    }
    
    //true if all child pointers are null
	bool isLeaf() const
    {
        return (!left && !middle && !right);
    }

    //true if |key| is a match to |keyL| or |keyR|
    bool isDuplicate(const T& key) const
    {
        return (key == *keyL || (keyR ? key == *keyR : false));
    }

    //compare |keyL| with |keyR| with |retrieveKey| of type |K|
    //if a key matches, return its address
    template <typename K>
    T* retrieve(const K& retrievalKey) const
    {
        if (*keyL == retrievalKey) return keyL;
        
        return ((keyR && *keyR == retrievalKey) ? keyR : nullptr);
    }

    //if the node is full determine the middle key and return its pointer
    //otherwise perform a sorted insert
    T* insert(const T& pushedKey)
    {
        //if the node is full determine the new median and split the current node
        if (isFull()) return median(pushedKey);

        //determine the greater value, which will be inserted in |keys[1]|
        if (pushedKey < *keyL)
        {
            keyR = keyL;
            keyL = new T(pushedKey);
        }
        else keyR = new T(pushedKey);

        return nullptr;
    }

    //if the node is full determine the new median, returning false
    //otherwise perform a sorted insert
    //move semantics are used here to shift the memory of |pushedKey| into this node
    bool push(T*& pushedKey)
    {
        if (!pushedKey) return true;

        //if the node is full determine the new median and split the current node
        if (isFull())
        {
            pushMedian(pushedKey);
            return false;
        }

        //determine the greater value, which will be inserted in |keyR|
        if (*pushedKey < *keyL)
        {
            keyR = keyL;
            keyL = pushedKey;
        }
        else keyR = pushedKey;

        pushedKey = nullptr;

        return true;
    }

    //adopt the given left and right subtrees as left and right children
    //|leftSubtree| and |rightSubtree| will be mutated to null as well 
    void adopt(Node*& leftSubtree, Node*& rightSubtree)
    {
        //adopt subtrees
        left = leftSubtree;
        right = rightSubtree;

        //set to null
        leftSubtree = nullptr;
        rightSubtree = nullptr;
    }

    ///////////////////////////////// GETTERS

    T*& _keyL() { return keyL; }
    T*& _keyR() { return keyR; }

    Node*& _left() { return left; }
    Node*& _middle() { return middle; }
    Node*& _right() { return right; }

    private:
    ///////////////////////////////// DATA 

    T* keyL;
    T* keyR;

    Node* left;
    Node* middle;
    Node* right;

    ///////////////////////////////// PRIVATE FUNCTIONS 

    //if |keyR| is not null then the leaf is full, return true
    bool isFull() const
    {
        return keyR;
    }
    
    //sort |pushedKey| with |keyL| and |keyR|
    //determine the new median and return it
    //allocate the newly |pushedKey|
    T* median(const T& pushedKey)
    {
        //to return
        T* median = nullptr;

        //keyL is the median 
        if (pushedKey < *keyL)
        {
            //assign the median and new 1st key
            median = keyL;
            keyL = new T(pushedKey);
        }

        //keyR is the median 
        else if (pushedKey > *keyR)
        {
            //assign the median and the new 2nd key
            median = keyR;
            keyR = new T(pushedKey);
        }

        //toInsert is the median
        else median = new T(pushedKey);

        return median;
    }

    //sort |pushedKey| with |keyL| and |keyR|
    //determine the new median and assign that back to |pushedKey|
    void pushMedian(T*& pushedKey)
    {
        //to hold the new median key which |pushedKey| will mutate to
        T* median = nullptr;

        //keyL is the median 
        if (*pushedKey < *keyL)
        {
            //assign the median and new 1st key
            median = keyL;
            keyL = pushedKey;

            //mutate |pushedKey| to the new median
            pushedKey = median;
        }

        //keyR is the median 
        else if (*pushedKey > *keyR)
        {
            //assign the median and the new 2nd key
            median = keyR;
            keyR = pushedKey;
            
            //mutate |pushedKey| to the new median
            pushedKey = median;
        }
    }
};

/////////////////////////////////////////////////// 2-3 TREE

template <typename T>
class Tree
{
	public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    //make a deep copy of source into this tree
    Tree& operator=(const Tree& source)
    {
        //check for self-assignment
        if (this != &source) source.duplicate(*this);

        return *this;
    }

    //in order traversal inserting all keys into |out|
    friend std::ostream& operator<<(std::ostream& out , const Tree& tree)
    {
        tree.display_inorder(tree.root, out);
        return out;
    }

    ///////////////////////////////// CONSTRUCTORS 

    //DEFAULT
    Tree() : root(nullptr) {}

    //COPY
    Tree(const Tree& source) : root(nullptr)
    {
        source.duplicate(*this);
    }

    //DESTRUCTOR
	~Tree() { clear(); }

    ///////////////////////////////// PUBLIC FUNCTIONS

    //display all keys in preorder traversal
    void display_preorder() const
    {
        display_preorder(root, 1);
    }

    //display all keys with in order traversal
    void display_inorder() const
    {
        display_inorder(root);
    }
    
    ////////// RETRIEVAL 

    //attempt to retrieve a key that yields a match to |retrievalKey| of type |K|
    //the following comparison operators must be overloaded by the data of type |T| to handle comparison with type |K|
    /* < > == */
    //|K| defaults to |T|
    template <typename K = T>
    T* retrieve(const K& retrievalKey) const
    {
        return retrieve(root, retrievalKey);
    }

    ////////// INSERTION

	//insert an key into the tree
    //if a duplicate of |toInsert| is found, throw an exception
	void insert(const T& toInsert)
    {
        //if the tree is empty
        if (!root) root = new Node<T>(toInsert);
        else
        {
            Node<T>* leftSplit = nullptr;
            Node<T>* rightSplit = nullptr;

            try
            {
                //insert into the tree
                T* pushedKey = insert(root, toInsert, leftSplit, rightSplit);

                if (pushedKey)
                {
                    //allocate a new root
                    Node<T>* newRoot = new Node<T>(pushedKey);

                    //adopt the split node
                    newRoot->adopt(leftSplit, rightSplit);

                    //grow the root
                    root = newRoot;
                }
            }
            catch (const T& attemptedKey)
            {
                std::cout << "Tree WARNING : INSERTION FAILURE : duplicate data found in tree\n"
                << "ATTEMPTED INSERT KEY : " << attemptedKey << "\n\n";
            }
        }
    }

    ////////// COPY 

    //make a deep copy of this tree into |copy|
    void duplicate(Tree& copy) const
    {
        //if the tree had existing memory, deallocate everything
        if (copy.root) copy.clear();

        if (!root) return;

        duplicate(copy.root, root);
    }

    ////////// DELETE 

    void clear()
    {
        delete root;
        root = nullptr;
    }

	private:

	Node<T>* root = nullptr;

    ///////////////////////////////// PRIVATE FUNCTIONS

    //display all keys in preorder traversal
    //default ostream is |std::cout|
	void display_preorder(Node<T>* root, int level, std::ostream& out = std::cout) const
    {
        if (!root) return;

        out << level << " :: ";

        root->display(out);
        ++level;

        display_preorder(root->_left(), level, out);
        display_preorder(root->_middle(), level, out);
        display_preorder(root->_right(), level, out);
    }

    //display all keys with in order traversal
    //default ostream is |std::cout|
	void display_inorder(Node<T>* root, std::ostream& out = std::cout) const
    {
        if (!root) return;
        
        display_inorder(root->_left(), out);

        out << *root->_keyL() << '\n';

        display_inorder(root->_middle(), out);

        if (root->_keyR()) out << *root->_keyR() << '\n';

        display_inorder(root->_right(), out);
    }

    //|K| defaults to |T|
    template <typename K = T>
    T* retrieve(Node<T>* root, const K& retrievalKey) const
    {
        if (!root) return nullptr;

        //to catch a retrieved key if a match is found
        T* retrieved = root->retrieve(retrievalKey);

        if (!retrieved)
        {
            //TRAVERSE LEFT
            if (*root->_keyL() > retrievalKey) retrieved = retrieve(root->_left(), retrievalKey);

            //TRAVERSE MIDDLE 
            else if (root->_keyR() && *root->_keyR() > retrievalKey) retrieved = retrieve(root->_middle(), retrievalKey);

            //TRAVERSE RIGHT 
            else retrieved = retrieve(root->_right(), retrievalKey);
        }

        return retrieved;
    }

    //traverse the tree in order to a leaf where |toInsert| belongs
    //attempt insertion, if the leaf is full, split the node using |leftSplit| and |rightSplit|
    //then return the resulting median key
    //continue to push the key and split nodes until vacancy is found
	T* insert(Node<T>*& root, const T& toInsert, Node<T>*& leftSplit, Node<T>*& rightSplit)
    {
        ////////////////// TAIL RECURSION

        //CHECK FOR DUPLICATE
        if (root->isDuplicate(toInsert)) throw (toInsert);

        //a leaf was found
        if (root->isLeaf())
        {
            T* pushedKey = root->insert(toInsert);

            //the leaf was full, and needs to be split
            if (pushedKey)
            {
                //allocate a new right node, moving |keyR| over
                rightSplit = new Node<T>(root->_keyR());
                leftSplit = root;
            }

            return pushedKey;
        }

        //to catch a key from a child node that needs to be split
        T* pushedKey = nullptr;

        ////////////////// HEAD RECURSION

        //TRAVERSE LEFT
        if (toInsert < *root->_keyL())
        {
            pushedKey = insert(root->_left(), toInsert, leftSplit, rightSplit);
            
            //if a key was pushed to the current root, attempt insertion, and split as needed
            if (pushedKey) pushSplitLeft(pushedKey, root, leftSplit, rightSplit);
        }

        //TRAVERSE MIDDLE 
        else if (root->_keyR() && toInsert < *root->_keyR())
        {
            pushedKey = insert(root->_middle(), toInsert, leftSplit, rightSplit);

            //if a key was pushed to the current root, attempt insertion, and split as needed
            if (pushedKey) pushSplitMid(pushedKey, root, leftSplit, rightSplit);
        }

        //TRAVERSE RIGHT 
        else
        {
            pushedKey = insert(root->_right(), toInsert, leftSplit, rightSplit);

            //if a key was pushed to the current root, attempt insertion, and split as needed
            if (pushedKey) pushSplitRight(pushedKey, root, leftSplit, rightSplit);
        }

        return pushedKey;
    }

    ///////////////////////////////// PUSH AND SPLIT 

    /*
    In head recursion during |insert|, if a key is pushed to a node, splitting must occur in 1 of
    2 possible ways, depending on the subtree origin of |pushedKey|. The algorithm attempts an
    insert at the current root. If the root is full, the node will be split, adopting the split
    child and subtrees as well. If the root had vacancy (2 node) then the child node will be split
    between it's orginal location, and the middle.
    */
    
    void pushSplitLeft(T*& pushedKey, Node<T>*& root, Node<T>*& leftSplit, Node<T>*& rightSplit)
    {
        if (!root->push(pushedKey))
        {
            //allocate a new right node, moving |keyR| over
            Node<T>* newRight = new Node<T>(root->_keyR());

            //adopt the right and middle subtrees
            newRight->adopt(root->_middle(), root->_right());
            
            //adopt the splits with the remaining |root|
            root->adopt(leftSplit, rightSplit);

            //set |root| to be the left split of this node
            leftSplit = root;

            //set |newRight| to be the right split of this node
            rightSplit = newRight;
        }
        else
        {
            root->_middle() = rightSplit;
            root->_left() = leftSplit;
        }
    }

    void pushSplitMid(T*& pushedKey, Node<T>*& root, Node<T>*& leftSplit, Node<T>*& rightSplit)
    {
        if (!root->push(pushedKey))
        {
            //allocate a new right node, moving |keyR| over
            Node<T>* newRight = new Node<T>(root->_keyR());

            //adopt the right subtree and the right split
            newRight->adopt(rightSplit, root->_right());

            //have |root| adopt the left split
            root->_right() = leftSplit;

            //the middle child was split
            root->_middle() = nullptr;

            //set |root| to be the left split of this node
            leftSplit = root;

            //set |newRight| to be the right split of this node
            rightSplit = newRight;
        }
    }

    void pushSplitRight(T*& pushedKey, Node<T>*& root, Node<T>*& leftSplit, Node<T>*& rightSplit)
    {
        if (!root->push(pushedKey))
        {
            //allocate a new right node, moving |keyR| over
            Node<T>* newRight = new Node<T>(root->_keyR());

            //adopt the splits
            newRight->adopt(leftSplit, rightSplit);
            
            //shift middle to right, making |root| the left split
            root->_right() = root->_middle();
            root->_middle() = nullptr;

            //set |root| to be the left split of this node
            leftSplit = root;

            //set |newRight| to be the right split of this node
            rightSplit = newRight;
        }
        else
        {
            root->_middle() = leftSplit;
            root->_right() = rightSplit;
        }
    }

    //make a deep copy of |source| tree into |copy| using in order traversal
    bool duplicate(Node<T>*& copy, Node<T>* source) const
    {
        if (!source) return false;

        copy = new Node<T>(*source->_keyL());

        duplicate(copy->_left(), source->_left());

        if (duplicate(copy->_middle(), source->_middle()))
        {
            copy->_keyR() = new T(*source->_keyR());
        }

        duplicate(copy->_right(), source->_right());

        return true;
    }
};

} /////////////////////////////////////////////////// END TREE LIBRARY NAMESPACE 

#endif
