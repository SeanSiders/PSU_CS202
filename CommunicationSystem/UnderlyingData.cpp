/***** CLASS IMPLEMENTATION FILE *****/

//Sean Siders
//CS202
//Program 2 : Communication System
//10/30/2020

/*
The implementation of underlying data classes are in this file. The underlying data classes are
meant to deal with user input of different data types, and storing that information.
*/

#include "UnderlyingData.h"

/////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

String::String() : maxLength(100), delimiter('\n'), string(nullptr) {}

Int::Int() {}

/////////////////////////////////////////////// COPY CONSTRUCTORS 

String::String(const String& other) :
    maxLength(other.maxLength), delimiter(other.delimiter), string(nullptr)
{
    setString(other.string);
}

/////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

String::String(const int _maxLength, const char _delimiter) :
    maxLength(_maxLength), delimiter(_delimiter), string(nullptr) {}

String::String(const char* _string, const char _delimiter) :
    delimiter(_delimiter), string(nullptr)
{
    if (!_string)
    {
        maxLength = STRING_MAX;
        getInput();
    }
    else
    {
        maxLength = strlen(_string) + 1;
        setString(_string);
    }
}

/////////////////////////////////////////////// DESTRUCTORS 

String::~String()
{
    delete [] string;
    string = nullptr;
}

/////////////////////////////////////////////// STRING 

//display |string|
void String::display() const
{
    if (string) std::cout << string;
}

//true if |string| is null
bool String::isNull() const
{
    return !string;
}

//true if |string| and |_string| are a case-sensitive match
bool String::isMatch(const char* _string) const
{
    return !strcmp(string, _string);
}

//overloaded to handle another |String| object
bool String::isMatch(const String& other) const
{
    return isMatch(other.string);
}

//deep copy |string| into |_string|
//if |_string| is null, get input from the user
void String::setString(const char* _string)
{
    if (!_string) return;
    checkAlloc(string);

    string = new char[strlen(_string) + 1];
    strcpy(string, _string);
}

//get string input from the user with |maxLength| and |delimiter| as parmeters
void String::getInput()
{
    //temporary input buffer
    char buffer[maxLength];

    std::cout << "\n>>> ";
	std::cin.get(buffer, maxLength, delimiter);

	char peek = std::cin.peek();

	while (delimiter != peek && '\0' != peek)
	{
		std::cout << "\nWARNING: your input was too long\n\n"
        << "MAX INPUT LENGTH: " << maxLength << "\n\n>>> ";

		std::cin.ignore(100, '\n');

		std::cin.get(buffer, maxLength, delimiter);
		peek = std::cin.peek();
	}

	std::cin.ignore(100, '\n');

    setString(buffer);
}

//check if |str| is allocated, if so, deallocate, and set to null
void String::checkAlloc(char*& str)
{
    if (str)
    {
        delete [] str;
        str = nullptr;
    }
}

//copy |source| into this class
void String::copy(const String& source)
{
    maxLength = source.maxLength;
    delimiter = source.delimiter;
    setString(source.string);
}

/////////////////////////////////////////////// Int 

//get integer input from the user between |min| and |max|, and return the value
int Int::getIntInput(const int min, const int max)
{
    //check for invalid |min| |max| values
    if (min >= max)
    {
        std::cout << "String::getIntInput -- invalid |min| |max| values\n\n";
        return 0;
    }

    getInput();
    
    int intValue = stringToInt(string);

    //if the input string is not an integer or an integer that is out of range
    while (!isInt() || intValue < min || intValue > max)
    {
        std::cout << "\nINVALID INPUT : ENTER AN INTEGER\n"
        << "range : (" << min << ", " << max << ")\n";
        getInput();

        intValue = stringToInt(string);
    }

    return intValue;
}

//determine if |string| is an integer, false if it is not
bool Int::isInt() const
{
    int length = strlen(string);

    bool isInteger = true;

    for (int i = 0; i < length && isInteger; ++i) isInteger = isdigit(string[i]);

    return isInteger;
}

//return the int value of a char
int Int::digitToInt(const char digit) const
{
    return digit - '0';
}

//convert |string| to an integer value and return it
int Int::stringToInt(const char* digitString) const
{
    if (!digitString) return 0;

    int lastChar = strlen(digitString) - 1;
    int factor = 1;
    int intVal = 0;

    //calculate integer value starting at the last char of the string
    //this last char will be the 1's place
    for (int i = lastChar; i >= 0; --i)
    {
        intVal += digitToInt(digitString[i]) * factor;
        factor *= 10;
    }

    return intVal;
}
