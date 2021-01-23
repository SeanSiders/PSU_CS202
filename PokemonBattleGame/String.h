/* STRING LIBRARY INTERFACES */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
The following hierarchy deals with char* input from the user. |String| is an abstraction
of all basic operations and procedures normally dealt with the char* data type. |Int| allows
the same basic char* input procedures, but also handles converting ASCII values back to a
true integral value.
*/

#ifndef STRING_H_ 
#define STRING_H_ 

#include <iostream>
#include <cstring>
#include <climits>

//// FORWARD DECLARATION
class String;

//// CONSTANTS
//the default length of |String::string|
const int DEFAULT_LENGTH = 1000;

/////////////////////////////////////////////////// GLOBAL OVERLOADS

std::ostream& operator<<(std::ostream&, const String&);

std::istream& operator>>(std::istream&, String&);

/////////////////////////////////////////////////// STRING 

/*
*/

class String 
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    friend std::ostream& operator<<(std::ostream&, const String&);
    friend std::istream& operator>>(std::istream&, String&);

    String& operator=(const String& source);
    String& operator=(const char* _string);
    
    bool operator==(const String& other) const;
    bool operator==(const char* _string) const;

    bool operator<(const String& other) const;
    bool operator<(const char* _string) const;

    bool operator>(const String& other) const;
    bool operator>(const char* _string) const;

    bool operator<=(const String& other) const;
    bool operator<=(const char* _string) const;

    bool operator>=(const String& other) const;
    bool operator>=(const char* _string) const;

    ///////////////////////////////// CONSTRUCTOR 

    String(const char* _string = nullptr, const int _maxLength = DEFAULT_LENGTH, const char _delimiter = '\n');
    String(const String& source);

    ~String();

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //insert |string| into ostream |out|
    //default is |std::cout|
    void display(std::ostream& out = std::cout) const;

    //get valid input from the user using |maxLength| and |delimiter|, inserting into istream |in|
    //|in| defaulted to |std::cin|
    void getInput(int _maxLength = -1, char _delimiter = '\0', std::istream& in = std::cin);

    //deep copy |string| into |_string|
    void copy(const char* _string);

    //deallocate |string|
    void clear();

    //true if |string| is null
    bool empty() const;

    protected:
    ///////////////////////////////// DATA 

    //the max length of accepted input 
    int maxLength;

    //the expected delimiter when taking input from the user
    char delimiter;

    //the string that is being contained
    char* string;
};

/////////////////////////////////////////////////// INT 

/*
This abstraction is designed to handle any integer input, with parameters specified by the
client. Input is extracted with |String|, and conversion to an integer is handled with |Int|.
|value| will hold the integer value, when valid digit input is read in.
*/

class Int : public String
{
    public:
    Int(const int _min = INT_MIN, const int _max = INT_MAX);

    ///////////////////////////////// PUBLIC FUNCTIONS

    //insert |value| into ostream |out|
    //default is |std::cout|
    void display(std::ostream& out = std::cout) const;

    //get integer input from the user between |min| and |max|, inserting into istream |in|
    //|in| defaulted to |std::cin|
    //return the int value from input back to the calling routine
    int getInput(int min = 0, int max = 0, std::istream& in = std::cin);

    private:
    ///////////////////////////////// DATA 

    //the min expected integer for input
    int min;

    //the max expected integer for input
    int max;

    //the integer that this class manages
    int value;

    ///////////////////////////////// PRIVATE FUNCTIONS

    //determine if |string| is an integer, false if it is not
    bool isInt() const;

    //return the int value of a char
    int digitToInt(const char digit) const;

    //convert |digitString| to an integer value and return it
    int stringToInt(const char* digitString) const;
};

#endif
