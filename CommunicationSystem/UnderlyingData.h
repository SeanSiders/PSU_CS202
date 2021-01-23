/***** CLASS INTERFACE FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
All class interfaces in this file manage underlying data that is used in the communication system
class hierarchy. The classes in this hierarchy are in "CommunicationSystem.h/.cpp". Most of this
underlying data is in the form of a char*, and in different contexts, must uphold a particular
format to be valid data. These classes are designed to handle the formatting of this data to keep
everything valid with respect to the communcation class that is containing it.
*/

#ifndef UNDERLYING_DATA_H_
#define UNDERLYING_DATA_H_

#include <iostream>
#include <cstring>

//CONSTANT
//the max length |String| will handle
const int STRING_MAX = 1000;

/*
Any data that requires string input from the user from within the communication system, |String|
will be used to set parameters for expected valid input.
*/

class String 
{
    public:
    /////////////////// CONSTRUCTORS

    String();
    String(const String& other);
    String(const int _maxLength, const char _delimiter = '\n');
    String(const char* _string, const char _delimiter = '\n');

    ~String();

    /////////////////// PUBLIC FUNCTIONS

    //display |string|
    void display() const;

    //true if |string| is null
    bool isNull() const;

    //OVERLOADED FUNCTION
    //true if |string| and |_string| are a case-sensitive match
    //overloaded to handle another |String| object
    bool isMatch(const char* _string) const;
    bool isMatch(const String& other) const;

    //deep copy |string| into |_string|
    void setString(const char* _string);

    //get valid input from the user using |maxLength| and |delimiter| as parameters
    void getInput();

    //copy |source| into this class
    void copy(const String& source);

    protected:
    //the max length of accepted input 
    int maxLength;

    //the expected delimiter when taking input from the user
    char delimiter;

    //the string that is being contained
    char* string;

    /////////////////// PRIVATE FUNCTIONS

    //check if |str| is allocated, if so, deallocate, and set to null
    void checkAlloc(char*& str);
};

/*
The following class is for handling integer data input that is converted from string input in the
super class |String|.
*/

class Int : public String
{
    public:
    Int();

    /////////////////// PUBLIC FUNCTIONS

    //get integer input from the user between |min| and |max|, and return the value
    int getIntInput(const int min, const int max); 

    //convert |digitString| to an integer value and return it
    int stringToInt(const char* digitString) const;

    private:
    /////////////////// PRIVATE FUNCTIONS

    //determine if |string| is an integer, false if it is not
    bool isInt() const;

    //return the int value of a char
    int digitToInt(const char digit) const;
};

#endif
