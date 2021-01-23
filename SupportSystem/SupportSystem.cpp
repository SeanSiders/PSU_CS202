//Sean Siders
//CS202
//Program 1 : Support System
//Oct 16, 2020

/*
This file contains all implementations of the classes in the support system class hierarchy.
Default constructors, initialization constructors, and copy constructors are implemented for all of
the classes that manage dynamic memory. |Shelter|, |Food|, and |Clothing| are derived from
|Support|, and invoke the appropriate base constructor for each context. All classes have basic
input and display functions that are unique to their data.
*/

#include "SupportSystem.h"

/////////////////////////////////////// DEFAULT CONSTRUCTORS

Support::Support() : supportName(nullptr), donorName(nullptr), quantity(0) {}

Shelter::Shelter() : capacity(1), residentCount(0), location(nullptr) {}

Food::Food() : allergens(nullptr) {}

Clothing::Clothing() : size(nullptr), condition(nullptr) {}

Date::Date() : date(nullptr) {}

Gender::Gender() : genderIndex(0) {}

/////////////////////////////////////// INITIALIZATION CONSTRUCTORS

Support::Support(const char* _donationDate, const char* _supportName,
                 const char* _donorName, const int& _quantity) :
    donationDate(_donationDate), supportName(nullptr), donorName(nullptr), quantity(_quantity)
{
    copyString(supportName, _supportName);
    copyString(donorName, _donorName);
}

Shelter::Shelter(const Support& source, const int& _capacity, const int& _residentCount, const char* _location) :
    Support(source), capacity(_capacity), residentCount(_residentCount), location(nullptr)
{
    copyString(location, _location);
}

Food::Food(const Support& source, const char* _expirationDate, const char* _allergens) :
    Support(source), expirationDate(_expirationDate), allergens(nullptr)
{
    copyString(allergens, _allergens);
}

Clothing::Clothing(const Support& source, const char* _gender, const char* _size, const char* _condition) :
    Support(source), gender(_gender), size(nullptr), condition(nullptr)
{
    copyString(size, _size);
    copyString(condition, _condition);
}

Date::Date(const char* _date) : date(nullptr)
{
    copyString(date, _date);
}

Gender::Gender(const char* gender) : genderIndex(0)
{
    input(gender);
}

/////////////////////////////////////// COPY CONSTRUCTORS

Support::Support(const Support& other) :
    donationDate(other.donationDate), supportName(nullptr), donorName(nullptr),
    quantity(other.quantity)
{
    copyString(supportName, other.supportName);
    copyString(donorName, other.donorName);
}

Shelter::Shelter(const Shelter& other) :
    Support(other), capacity(other.capacity), residentCount(other.residentCount), location(nullptr)
{
    copyString(location, other.location);
}

Food::Food(const Food& other) : Support(other), expirationDate(other.expirationDate), allergens(nullptr)
{
    copyString(allergens, other.allergens);
}

Clothing::Clothing(const Clothing& other) : Support(other), size(nullptr), condition(nullptr)
{
    copyString(size, other.size);
    copyString(condition, other.condition);
}

Date::Date(const Date& other) : date(nullptr)
{
    copyString(date, other.date);
}

/////////////////////////////////////// DESTRUCTORS 

Support::~Support()
{
    delete [] supportName;
    delete [] donorName;

    supportName = nullptr;
    donorName = nullptr;
}

Shelter::~Shelter()
{
    delete [] location;
    
    location = nullptr;
}

Food::~Food()
{
    delete [] allergens;

    allergens = nullptr;
}

Clothing::~Clothing()
{
    delete [] size;
    delete [] condition;

    size = nullptr;
    condition = nullptr;
}

Date::~Date()
{
    delete [] date;
    date = nullptr;
}

/////////////////////////////////////// SUPPORT 

//display all members of this class except for |searchFrequency|
void Support::display() const 
{
    if (!supportName || !donorName) return;

    std::cout << "SUPPORT : " << supportName
    << "\nDONOR : " << donorName
    << "\nDONATION DATE : ";

    donationDate.display();

    if (quantity) std::cout << "\nQUANTITY : " << quantity;
}

//display |supportName|
void Support::displaySupportName() const
{
    if (!supportName) return;

    std::cout << supportName << "\n\n";
}

//input the essential information about a donated relief effort
//only the date and support name are required
void Support::input(const char* _donationDate, const char* _supportName,
                    const char* _donorName, const int& _quantity)
{
    donationDate.setDate(_donationDate);

    allocationCheck(supportName);
    allocationCheck(donorName);

    copyString(supportName, _supportName);
    copyString(donorName, _donorName);

    quantity = _quantity;
}

//duplicate an instance of this class into |other|
void Support::duplicate(Support& other)
{
    donationDate.duplicate(other.donationDate);

    copyString(other.supportName, supportName);
    copyString(other.donorName, donorName);

    other.quantity = quantity;
}

//return |quantity|
//this can be used to determine if an item is still available, and if so how many
int Support::getQuantity() const
{
    return quantity;
}

//to update the number of this relief effort is available
//attempt to add |quantity| and |_quantity|
//if the resulting addition is negative return false
bool Support::updateQuantity(const int& _quantity)
{
    if (quantity + _quantity < 0) return false;

    quantity += _quantity;
    return true;
}

//compare |supportName| and |_supportName|
//if the string is a case-sensitive match, increment |searchFrequency| and return true
bool Support::isMatch(const char* _supportName)
{
    return !strcmp(supportName, _supportName);
}

/////////////////////////////////////// SHELTER 

//display all information about a shelter
void Shelter::display() const 
{
    if (!location) return;

    //display base class information
    Support::display();

    //display shelter information
    std::cout << "\nCAPACITY : " << capacity
    << "\nCURRENT RESIDENT COUNT : " << residentCount
    << "\nLOCATION : " << location
    << "\n\n";
}

//input the essential information about a donated shelter
//only the base support support object is required
//return false if |_capacity| or |_residentCount| are semantically invalid
bool Shelter::input(const Support& source, const int& _capacity,
                    const int& _residentCount, const char* _location)
{
    //invoke the base copy constructor
    *this = source;

    return input(_capacity, _residentCount, _location);
}

//input only the information about a shelter
//return false if |_capacity| or |_residentCount| are semantically invalid
bool Shelter::input(const int& _capacity, const int& _residentCount, const char* _location)
{
    if (_capacity < _residentCount || _capacity < 0 || _residentCount < 0) return false;

    capacity = _capacity;
    residentCount = _residentCount;

    allocationCheck(location);
    copyString(location, _location);

    return true;
}

//make a duplicate of this class into other
//all dynamic memory will be deep copied
void Shelter::duplicate(Shelter& other)
{
    Support::duplicate(other);

    other.capacity = capacity;
    other.residentCount = residentCount;

    copyString(other.location, location);
}

//to update the number of residents in a house
//attempt to add |count| to |residentCount|
//return false if the addition results in more than the capacity or a negative number
bool Shelter::updateResidents(const int& count)
{
    if (residentCount + count < 0 || residentCount + count > capacity) return false;

    residentCount += count;
    return true;
}

//returns the number of people that could reasonably move into the shelter
//this will be 0 if the shelter is fully occupied
int Shelter::getVacancy() const
{
    return capacity - residentCount;
}

/////////////////////////////////////// FOOD 

//display all information about a food item
void Food::display() const
{
    if (!allergens) return;

    //display base class information
    Support::display();

    //display food information
    std::cout << "\nALLERGENS : " << allergens
    << "\nEXPIRATION DATE : ";

    expirationDate.display();

    std::cout << "\n\n";
}

//input the essential information about a food item
//only the base support support object is required
void Food::input(const Support& source, const char* _expirationDate,
                 const char* _allergens)
{
    //invoke the base copy constructor
    *this = source;

    input(_expirationDate, _allergens);
}

//input only the information about a food item
void Food::input(const char* _expirationDate, const char* _allergens)
{
    allocationCheck(allergens);
    
    expirationDate.setDate(_expirationDate);
    copyString(allergens, _allergens);
}

//make a duplicate of this class into other
//all dynamic memory will be deep copied
void Food::duplicate(Food& other)
{
    Support::duplicate(other);

    expirationDate.duplicate(other.expirationDate);
    copyString(other.allergens, allergens);
}

//true if |today| matches the food's expiration date 
//|today| is expected to be in the same string format that all other dates are in for the system
bool Food::isExpired(const char* today) const
{
    return expirationDate.isToday(today);
}

/////////////////////////////////////// CLOTHING 

//display all information about a clothing item
void Clothing::display() const
{
    if (!size || !condition) return;

    //display base class information
    Support::display();

    //display clothing information
    std::cout << "\nGENDER : ";
    gender.display();

    std::cout << "\nSIZE : " << size
    << "\nCONDITION : " << condition << "\n\n";
}

//input the essential information about a clothing item
//only the base support support object is required
bool Clothing::input(const Support& source, const char* _gender, const char* _size, const char* _condition)
{
    //invoke the base copy constructor
    *this = source;

    return input(_gender, _size, _condition);
}

//input only the information about a clothing item
bool Clothing::input(const char* _gender, const char* _size, const char* _condition)
{
    allocationCheck(size);
    allocationCheck(condition);

    copyString(size, _size);
    copyString(condition, _condition);
    
    return gender.input(_gender);
}

//make a duplicate of this class into other
//all dynamic memory will be deep copied
void Clothing::duplicate(Clothing& other)
{
    Support::duplicate(other);

    copyString(other.size, size);
    copyString(other.condition, condition);
}

//take in at least a gender, but also optionally a size and condition
//if the supplied arguments match the data members of this instance, return true
bool Clothing::categoryMatch(const char* _gender, const char* _size, const char* _condition)
{
    if (!gender.isMatch(_gender)) return false;
    if (!_size) return true;
    
    if (strcasecmp(size, _size)) return false;
    if (!condition) return true;

    return !strcasecmp(condition, _condition);
}

/////////////////////////////////////// DATE 

//duplicate this class into |other|
void Date::duplicate(Date& other)
{
    copyString(other.date, date);
}

//display |date| if not null
void Date::display() const
{
    if (date) std::cout << date;
}

//deep copy |date| as |_date|
void Date::setDate(const char* _date)
{
    allocationCheck(date);
    copyString(date, _date);
}

//true if |date| is equivalent to |_date|
bool Date::isToday(const char* _date) const
{
    return !strcmp(date, _date);
}

/////////////////////////////////////// GENDER 

//attempt to set |genderIndex| by comparing |gender| to the array of possible inputs |genders|
//false if no match is found in the array
bool Gender::input(const char* gender)
{
    if (!gender) return false;

    //true if a match is found
    bool matched = false;

    for (int i = 0; i < 5 && !matched; ++i)
    {
        if (!strcasecmp(genders[i], gender))
        {
            matched = true;
            genderIndex = i;
        }
    }

    return matched;
}

//iterate through |genders|, displaying the possible inputs for gender
//non-case sensitive
void Gender::displayValidGenders() const
{
    for (const char* g : genders) std::cout << g << std::endl;

    std::cout << std::endl;
}

//display the current set gender
void Gender::display() const
{
    std::cout << genders[genderIndex];
}

//compare |gender| with the current set gender string from |genders|
//true it if a non-case sensitive match
bool Gender::isMatch(const char* gender) const
{
    return !strcasecmp(genders[genderIndex], gender);
}

