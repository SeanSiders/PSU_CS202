//Sean Siders
//CS202
//Program 1 : Support System
//Oct 16, 2020

/*
This file contains all class interfaces that are a part of the support system class hierarchy. This
hierarchy is designed to be an object oriented solution to storing information about various relief
efforts. In addition to the class interfaces, there are 2 helper functions that deal with a common
data type that most of the classes manage (char*).
*/

#include <iostream>
#include <cstring>

#ifndef SUPPORTSYSTEM_H_
#define SUPPORTSYSTEM_H_

/////////////////////////////////////// HELPER FUNCTIONS

//deep copy |source| into |copy|
//used by all classes in the system to copy strings
inline void copyString(char*& copy, const char* source)
{
    if (!source) return;

    copy = new char[strlen(source) + 1];
    strcpy(copy, source);
}

//check if |str| is already pointing to dynamic memory
//if it is deallocate and set to null
//this is called before any deep copies in a previously existing class
inline void allocationCheck(char*& str)
{
    if (!str) return;

    delete [] str;
    str = nullptr;
}

/////////////////////////////////////// UNDERLYING DATA

/*
Any data that involves a date is managed by this class. Currently, the date is a simple string with
no expected formatting. It is up to the client to decide upon, then adhere to a particular date
format that works for the program and user.
*/

class Date
{
    public:
    //default constructor
    Date();

    //copy constructor
    Date(const Date& other);

    //initialization constructor
    Date(const char* _date);

    ~Date();

    ///////////// PUBLIC FUNCTIONS
    
    //duplicate this class into |other|
    void duplicate(Date& other);

    //display |date| if not null
    void display() const;

    //deep copy |date| as |_date|
    void setDate(const char* _date);

    //true if |date| is equivalent to |_date|
    bool isToday(const char* _date) const;

    private:
    char* date;
};

/*
Information about a gender is managed by this class. An instance of this class will be used by
|Clothing| which is part of the system's class hierarchy.
*/
class Gender
{
    public:
    //default constructor
    Gender();

    //initialization constructor
    Gender(const char* _gender);

    ///////////// PUBLIC FUNCTIONS

    //attempt to set |genderIndex| by comparing |gender| to the array of possible inputs |genders|
    //false if no match is found in the array
    bool input(const char* gender);

    //iterate through |genders|, displaying the possible inputs for gender
    //non-case sensitive
    void displayValidGenders() const;

    //display the current set gender
    void display() const;

    //compare |gender| with the current set gender string from |genders|
    //true it if a non-case sensitive match
    bool isMatch(const char* gender) const;

    private:
    //which index of |genders| reflects the state of this class
    //0 is the default
    int genderIndex;

    //all input is compared against this array, non-case sensitive
    //the gender can only be one of these items in the array
    //"Not Specified" is the default
    const char* genders[5] = { "Not Specified", "Female", "Male", "Neutral", "Non-Binary" };
};

/////////////////////////////////////// BASE CLASS

/*
Every type of donated relief effort that exists in this system will be a class that is derived from
the |Support| class. Each class will be individually responsible for operating on its own data.
Functions called from a subclass that are synonymous to a |Support| function such as |display|, will
call those functions for the base class, effectively showing all data in the hierarchy.
*/

class Support 
{
    public:
    //default constructor
    Support();

    //copy constructor
    Support(const Support& other);

    //initialization constructor
    Support(const char* _donationDate, const char* _supportName,
    const char* _donorName = nullptr, const int& _quantity = 1);

    ~Support();

    ///////////// PUBLIC FUNCTIONS

    //Display all members of this class except for |searchFrequency|
    //dynamic binding will be implemented in the data structures that handle
    //this system. This will allow the data structures to contain different
    //derived classes of support.
    void display() const;

    //display |supportName|
    void displaySupportName() const;

    //input the essential information about a donated relief effort
    //only the date and support name are required
    void input(const char* _donationDate, const char* _supportName,
    const char* _donorName = nullptr, const int& _quantity = 1);

    //duplicate an instance of this class into |other|
    void duplicate(Support& other);

    //return |quantity|
    //this can be used to determine if an item is still available, and if so how many
    int getQuantity() const;

    //to update the number of this relief effort is available
    //attempt to add |quantity| and |_quantity|
    //if the resulting addition is negative return false
    bool updateQuantity(const int& _quantity);

    //compare |supportName| and |_supportName|
    //if the string is a case-sensitive match, increment |searchFrequency| and return true
    //this function is used by the |Database| class to sort items by the number of times they
    //have been searched for
    bool isMatch(const char* _supportName);

    protected:

    ///////////// DATA

    //date of donation
    Date donationDate;
    
    //self-describing name for the relief effort donated
    char* supportName;

    //name of the donor (optional)
    char* donorName;

    //number of the donated relief effort (if duplicates exist)
    int quantity;
};

/////////////////////////////////////// SUB CLASSES

/*
The following classes are subclasses of the |Support| base class. The client program can use these
sub classes to implement a system that allows users to either donate, or recieve items that reflect
the name of the class. All sub classes will have an |input| function which takes in a |Support|
object, and optionally the data that is specific to that derived class.
*/

class Shelter : public Support
{
    public:
    //default constructor
    Shelter();

    //copy constructor
    Shelter(const Shelter& other);

    //initialization constructor
    Shelter(const Support& source, const int& _capacity = 1,
    const int& _residentCount = 0, const char* _location = nullptr);

    ~Shelter();

    ///////////// PUBLIC FUNCTIONS

    void display() const;

    //input the essential information about a donated shelter
    //only the base support support object is required
    //return false if |_capacity| or |_residentCount| are semantically invalid
    bool input(const Support& source, const int& _capacity = 1,
    const int& _residentCount = 0, const char* _location = nullptr);

    //input only the information about a shelter
    //return false if |_capacity| or |_residentCount| are semantically invalid
    bool input(const int& _capacity, const int& _residentCount = 0,
    const char* _location = nullptr); 

    //make a duplicate of this class into other
    //all dynamic memory will be deep copied
    void duplicate(Shelter& other);

    //to update the number of residents in a house
    //attempt to add |count| to |residentCount|
    //return false if the addition results in more than the capacity or a negative number
    bool updateResidents(const int& count);

    //returns the number of people that could reasonably move into the shelter
    //this will be 0 if the shelter is fully occupied
    int getVacancy() const;

    private:

    ///////////// DATA

    //the maximum capacity of the shelter
    int capacity;

    //the current number of residents
    int residentCount;

    //location or address of the shelter
    char* location;
};

class Food : public Support
{
    public:
    //default constructor
    Food();

    //copy constructor
    Food(const Food& other);

    //initialization constructor
    Food(const Support& source, const char* _expirationDate = nullptr,
    const char* _allergens = nullptr);

    ~Food();

    ///////////// PUBLIC FUNCTIONS

    //display all information about a food item
    void display() const;

    //input the essential information about a food item
    //only the base support support object is required
    void input(const Support& source, const char* _expirationDate = nullptr,
    const char* _allergens = nullptr);

    //input only the information about a food item
    void input(const char* _expirationDate, const char* _allergens = nullptr);

    //make a duplicate of this class into other
    //all dynamic memory will be deep copied
    void duplicate(Food& other);

    //true if |today| matches the food's expiration date 
    //|today| is expected to be in the same string format that all other dates are in for the system
    bool isExpired(const char* today) const;

    private:

    ///////////// DATA

    //an expiration date of the food
    Date expirationDate;

    //allergy or important dietary information
    char* allergens;
};

class Clothing : public Support
{
    public:
    //default constructor
    Clothing();

    //copy constructor
    Clothing(const Clothing& other);

    //initialization constructor
    Clothing(const Support& source, const char* _gender = nullptr,
    const char* _size = nullptr, const char* _condition = nullptr); 

    ~Clothing();

    ///////////// PUBLIC FUNCTIONS

    //display all information about a clothing item
    void display() const;

    //input the essential information about a clothing item
    //only the base support support object is required
    //false if the |_gender| was not a valid input
    bool input(const Support& source, const char* _gender = nullptr,
    const char* _size = nullptr, const char* _condition = nullptr); 

    //input only the information about a clothing item
    //false if the |_gender| was not a valid input
    bool input(const char* _gender, const char* _size = nullptr, const char* _condition = nullptr);

    //make a duplicate of this class into other
    //all dynamic memory will be deep copied
    void duplicate(Clothing& other);

    //take in at least a gender, but also optionally a size and condition
    //if the supplied arguments match the data members of this instance, return true
    bool categoryMatch(const char* _gender, const char* _size = nullptr, const char* _condition = nullptr);

    private:

    ///////////// DATA

    //the suggested gender for the clothing
    Gender gender;

    //the size of the clothing
    char* size;

    //the condition of the clothing
    char* condition;
};

#endif
