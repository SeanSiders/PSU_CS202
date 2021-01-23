/* STRING LIBRARY IMPLEMENTATION */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
All applications of char* are handled by |String| with dynamic memory. |Int| is a
solution to handling user input as char*, then converting to it's respective int value.
*/

#include "String.h"

/////////////////////////////////////////////////// GLOBAL OVERLOADS 

std::ostream& operator<<(std::ostream& out, const String& string)
{
    string.display(out);

    return out;
}

std::istream& operator>>(std::istream& in, String& string)
{
    string.getInput(string.maxLength, string.delimiter, in);

    return in;
}

/////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

//all args have default values, overriding this constructor as a default
String::String(const char* _string, const int _maxLength, const char _delimiter) :
    maxLength(_maxLength), delimiter(_delimiter), string(nullptr)
{
    if (maxLength < 0) maxLength = DEFAULT_LENGTH;

    copy(_string);
}

Int::Int(const int _min, const int _max) : min(_min), max(_max) {}

/////////////////////////////////////////////// COPY CONSTRUCTOR

String::String(const String& source) :
    maxLength(source.maxLength), delimiter(source.delimiter), string(nullptr)
{
    copy(source.string);
}

/////////////////////////////////////////////// DESTRUCTORS 

String::~String() { clear(); }

/////////////////////////////////////////////// STRING 

String& String::operator=(const String& source)
{
    //check for self assignment
    if (this != &source)
    {
        delimiter = source.delimiter;
        copy(source.string);
    }

    return *this;
}

String& String::operator=(const char* _string)
{
    copy(_string);
    return *this;
}

bool String::operator==(const String& other) const
{
    return ((empty() || other.empty()) ?
    false : !strcmp(string, other.string));
}

bool String::operator==(const char* _string) const
{
    return ((empty() || !_string) ?
    false : !strcmp(string, _string));
}

bool String::operator<(const String& other) const
{
    return (((empty() || other.empty()) ?
    false : strcmp(string, other.string) < 0));
}

bool String::operator<(const char* _string) const
{
    return ((empty() || !_string) ?
    false : strcmp(string, _string) < 0);
}

bool String::operator>(const String& other) const
{
    return ((empty() || other.empty()) ?
    false : strcmp(string, other.string) > 0);
}

bool String::operator>(const char* _string) const
{
    return ((empty() || !_string) ?
    false : strcmp(string, _string) > 0);
}

bool String::operator<=(const String& other) const
{
    return ((empty() || other.empty()) ?
    false : strcmp(string, other.string) <= 0);
}

bool String::operator<=(const char* _string) const
{
    return ((empty() || !_string) ?
    false : strcmp(string, _string) <= 0);
}

bool String::operator>=(const String& other) const
{
    return ((empty() || other.empty()) ?
    false : strcmp(string, other.string) >= 0);
}

bool String::operator>=(const char* _string) const
{
    return ((empty() || !_string) ?
    false : strcmp(string, _string) >= 0);
}

//insert |string| into ostream |out|
void String::display(std::ostream& out) const
{
    if (string) out << string;
}

//deep copy |string| into |_string|
//if |_string| is null, get input from the user
void String::copy(const char* _string)
{
    if (string) clear();

    if (!_string) return;

    maxLength = strlen(_string) + 1;

    string = new char[maxLength];
    strcpy(string, _string);
}

//get valid input from the user using |maxLength| and |delimiter|, inserting into istream |in|
void String::getInput(int _maxLength, char _delimiter, std::istream& in)
{
    //defaulted to |maxLength| if value is negative or just not provided
    if (_maxLength < 0) _maxLength = maxLength;

    //|_maxLength| is not expected to factor in the terminating null '\0'
    else ++_maxLength;

    //defaulted to |delimiter| if the char is not provided
    if ('\0' == _delimiter) _delimiter = delimiter;

    //temporary input buffer
    char buffer[_maxLength];

	in.get(buffer, _maxLength, delimiter);

	char peek = in.peek();

	while (delimiter != peek && '\0' != peek)
	{
		std::cerr << "\nString WARNING: your input was too long\n\n"
        << "MAX INPUT LENGTH: " << _maxLength << "\n\n>>> ";

		in.ignore(100, '\n');

		in.get(buffer, _maxLength, delimiter);
		peek = in.peek();
	}

	in.ignore(100, '\n');

    copy(buffer);
}

//deallocate |string|
void String::clear()
{
    delete [] string;
    string = nullptr;
}

//true if |string| is null
bool String::empty() const
{
    return !string;
}

/////////////////////////////////////////////// INT

//insert |value| into ostream |out|
void Int::display(std::ostream& out) const
{
    out << value;
}

//get integer input from the user between |min| and |max|, inserting into istream |in|
//|in| defaulted to |std::cin|
//return the int value from input back to the calling routine
int Int::getInput(int _min, int _max, std::istream& in)
{
    //check for invalid |min| |max| values
    if (_min >= _max || _min < 0)
    {
        _min = min;
        _max = max;
    }

    String::getInput(maxLength, '\n', in);
    
    value = stringToInt(string);

    //if the input string is not an integer or an integer that is out of range
    while (!isInt() || value < _min || value > _max)
    {
        std::cerr << "\nINVALID INPUT : ENTER AN INTEGER\n"
        << "range : (" << _min << ", " << _max << ")\n";

        String::getInput(maxLength, '\n', in);

        value = stringToInt(string);
    }

    return value;
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
