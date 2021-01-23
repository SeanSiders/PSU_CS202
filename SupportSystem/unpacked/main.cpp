//Sean Siders
//CS202
//Program 1 : Support System
//Oct 16, 2020

/*
The support system is tested by reading in a data from 3 separate external files. 1 file for each of
the unique derived classes. By running the program, this data will be read in, and inserted into
their respective classes, and then inserted into a |Database| object; which manages all data
structures involved with the program. The user can test most of features of this program via a menu,
to verify the integrity of data structures, and properly managed memory.
*/

#include <fstream>
#include "SupportSystem.h"
#include "DataStructures.h"

/////////////////////////////////////// CONSTANTS 

/*
The automated testing interface will accept 3 different external files to read
in entries for each of the 3 respective objects :
|SHELTER| |FOOD| |CLOTHING|

The interface will read in all of the unique entries in these files, and input
them into the system.
*/

//Set these constants to their respective filepaths
const char* SHELTER_FILENAME = "dataset/shelter.txt";
const char* FOOD_FILENAME = "dataset/food.txt";
const char* CLOTHING_FILENAME = "dataset/clothing.txt";

//The most fields that each class is expecting
const int FIELDS_MAX = 7;

//The max number of chars that can be read in for each field
const int BUFFER_MAX = 100;

/////////////////////////////////////// PROTOTYPES 

void inputShelter(std::ifstream& i_file, Database& database);
void inputFood(std::ifstream& i_file, Database& database);
void inputClothing(std::ifstream& i_file, Database& database);

bool readField(std::ifstream& i_file, char* strBuffer, const char delimiter);

void getStringInput(char* str, const char delimiter);
int strToInt(const char* str);
int digitToInt(const char digit);
int getIntValue();

void getSupportInfo(char strBuffer[FIELDS_MAX][BUFFER_MAX]);

void test_insert_shelter(Database& database);
void test_insert_food(Database& database);
void test_insert_clothing(Database& database);

void test_search(Database& database);
void test_remove(Database& database);
void test_history_remove(Database& database);
void test_copy_database(Database& database);

int main()
{
    std::ifstream shelter_file(SHELTER_FILENAME);
    std::ifstream food_file(FOOD_FILENAME);
    std::ifstream clothing_file(CLOTHING_FILENAME);

    Database database;

    inputShelter(shelter_file, database);
    inputFood(food_file, database);
    inputClothing(clothing_file, database);

    std::cout << "EXTERNAL DATA READ IN FROM : " << SHELTER_FILENAME << " "
    << FOOD_FILENAME << " " << CLOTHING_FILENAME << "\n\n";

    //true when it is time to terminate the main program test loop
    bool terminate = false;

    do
    {
        std::cout << "TESTING INTERFACE\n"
        << "SELECT AN OPTION BY INTEGER INPUT\n"
        << "=================================\n"
        << "0) quit\n"
        << "1) display all relief efforts\n"
        << "2) create a |Shelter| object and manually input data\n"
        << "3) create a |Food| object and manually input data\n"
        << "4) create a |Clothing| object and manually input data\n"
        << "5) search for a relief effort by name (retrieval)\n"
        << "6) display search history (sorted by frequency)\n"
        << "7) remove a relief effort by name\n"
        << "8) remove an item from search history\n"
        << "9) make a complete copy of the data base (all data structures)\n\n";

        switch (getIntValue())
        {
            case 0 : terminate = true; break;
            case 1 : database.display(); break;
            case 2 : test_insert_shelter(database); break;
            case 3 : test_insert_food(database); break;
            case 4 : test_insert_clothing(database); break;
            case 5 : test_search(database); break;
            case 6 : database.displaySearchHistory(); break;
            case 7 : test_remove(database); break;
            case 8 : test_history_remove(database); break;
            case 9 : test_copy_database(database); break;

            default : std::cout << "INVALID INPUT\n\n"; break;
        }

    } while (!terminate);


    return 0;
}

/////////////////////////////////////// INPUT FUNCTIONS

/*
The following recursive functions are used to read entries from an external file and insert them
into their respective classes. |buffer| is an array of strings, which will serve as the buffer for
all of the data that will be inserted into an object. For integer members, string to int conversion
is performed via |strToInt| just before being passed into the object initialization constructor.
The new object will then be inserted into the |CircularList| data structure, where the tester can
perform further manual testing.
*/

void inputShelter(std::ifstream& i_file, Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];

    //base case : end of file has been reached
    if (!readField(i_file, buffer[0], '|')) return;
    readField(i_file, buffer[1], '|');
    readField(i_file, buffer[2], '|');

    readField(i_file, buffer[3], '|');
    readField(i_file, buffer[4], '|');
    readField(i_file, buffer[5], '|');

    readField(i_file, buffer[6], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Shelter shelter(support, strToInt(buffer[4]), strToInt(buffer[5]), buffer[6]);

    database.insert(shelter);

    inputShelter(i_file, database);
}

void inputFood(std::ifstream& i_file, Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];

    if (!readField(i_file, buffer[0], '|')) return;
    readField(i_file, buffer[1], '|');
    readField(i_file, buffer[2], '|');

    readField(i_file, buffer[3], '|');

    readField(i_file, buffer[4], '|');
    readField(i_file, buffer[5], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Food food(support, buffer[4], buffer[5]);

    database.insert(food);

    inputFood(i_file, database);
}

void inputClothing(std::ifstream& i_file, Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];

    if (!readField(i_file, buffer[0], '|')) return;
    readField(i_file, buffer[1], '|');
    readField(i_file, buffer[2], '|');

    readField(i_file, buffer[3], '|');

    readField(i_file, buffer[4], '|');
    readField(i_file, buffer[5], '|');
    readField(i_file, buffer[6], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Clothing clothing(support, buffer[4], buffer[5], buffer[6]);

    database.insert(clothing);

    inputClothing(i_file, database);
}

//attempt to read in a field from |i_file| into |strBuffer|
//return false if the end of file is reached
bool readField(std::ifstream& i_file, char* strBuffer, const char delimiter)
{
    strBuffer[0] = '\0';

    i_file.get(strBuffer, BUFFER_MAX, delimiter);
    if (i_file.eof()) return false;

    i_file.ignore(BUFFER_MAX, delimiter);
    return true;
}

void getStringInput(char* str, const char delimiter)
{
	std::cin.get(str, BUFFER_MAX, delimiter);
	char peek = std::cin.peek();

	while (delimiter != peek && '\0' != peek)
	{
		std::cout << "\nTI :: WARNING: your input was too long\n\nMAX INPUT LENGTH: "
		<< BUFFER_MAX << "\n\n";

		std::cin.ignore(100, '\n');

		std::cin.get(str, BUFFER_MAX, delimiter);
		peek = std::cin.peek();
	}

	std::cin.ignore(100, '\n');
}

//convert |str| to an integer value and return it
int strToInt(const char* str)
{
    int lastChar = strlen(str) - 1;
    int factor = 1;
    int intVal = 0;

    //calculate integer value starting at the last char of the string
    //this last char will be the 1's place
    for (int i = lastChar; i >= 0; --i)
    {
        intVal += digitToInt(str[i]) * factor;
        factor *= 10;
    }

    return intVal;
}

//convert |digit| char to an integer value and return it
int digitToInt(const char digit)
{
    return digit - '0';
}

int getIntValue()
{
    char strInput[BUFFER_MAX] = "\0";
    std::cin.get(strInput, BUFFER_MAX, '\n');
    std::cin.ignore(100, '\n');

    return strToInt(strInput);
}

void getSupportInfo(char strBuffer[FIELDS_MAX][BUFFER_MAX])
{
    std::cout << "INPUT THE FOLLOWING INFORMATION\n"
    << "DATE OF DONATION : ";
    getStringInput(strBuffer[0], '\n');

    std::cout << "SUPPORT NAME : ";
    getStringInput(strBuffer[1], '\n');

    std::cout << "DONOR NAME : ";
    getStringInput(strBuffer[2], '\n');

    std::cout << "QUANTITY : ";
    getStringInput(strBuffer[3], '\n');
}

/////////////////////////////////////// TESTING FUNCTIONS

void test_insert_shelter(Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];
    getSupportInfo(buffer);

    std::cout << "CAPACITY : ";
    getStringInput(buffer[4], '\n');

    std::cout << "CURRENT RESIDENT COUNT : ";
    getStringInput(buffer[5], '\n');

    std::cout << "LOCATION : ";
    getStringInput(buffer[6], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Shelter shelter(support, strToInt(buffer[4]), strToInt(buffer[5]), buffer[6]);

    database.insert(shelter);

    std::cout << "SHELTER INSERTED\n\n";
}

void test_insert_food(Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];
    getSupportInfo(buffer);

    std::cout << "EXPIRATION DATE : ";
    getStringInput(buffer[4], '\n');

    std::cout << "ALLERGENS : ";
    getStringInput(buffer[5], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Food food(support, buffer[4], buffer[5]);

    database.insert(food);

    std::cout << "FOOD INSERTED\n\n";
}

void test_insert_clothing(Database& database)
{
    char buffer[FIELDS_MAX][BUFFER_MAX];
    getSupportInfo(buffer);

    std::cout << "GENDER\n"
    << "VALID INPUTS : not case sensitive\n"
    << "============\n"
    << "Not Specified, Female, Male, Neutral, Non-Binary\n";

    getStringInput(buffer[4], '\n');

    std::cout << "SIZE : ";
    getStringInput(buffer[5], '\n');

    std::cout << "CONDITION : ";
    getStringInput(buffer[6], '\n');

    Support support(buffer[0], buffer[1], buffer[2], strToInt(buffer[3]));
    Clothing clothing(support, buffer[4], buffer[5], buffer[6]);

    database.insert(clothing);

    std::cout << "CLOTHING INSERTED\n\n";
}

void test_search(Database& database)
{
    char str[BUFFER_MAX];
    std::cout << "INPUT THE RELIEF EFFORT BY NAME\n";
    getStringInput(str, '\n');

    Shelter retrieveShelter;
    Food retrieveFood;
    Clothing retrieveClothing;

    if (database.search(str, retrieveShelter))
    {
        std::cout << "\nSHELTER RETRIEVED\n\n";
        retrieveShelter.display();
    }
    else if (database.search(str, retrieveFood))
    {
        std::cout << "\nFOOD RETRIEVED\n\n";
        retrieveFood.display();
    }
    else if (database.search(str, retrieveClothing))
    {
        std::cout << "\nCLOTHING RETRIEVED\n\n";
        retrieveClothing.display();
    }
    else std::cout << "\nNO RELIEF EFFORT WAS FOUND\n\n";
}

void test_remove(Database& database)
{
    char str[BUFFER_MAX];
    std::cout << "INPUT THE RELIEF EFFORT TO REMOVE\n";
    getStringInput(str, '\n');

    if (database.remove(str)) std::cout << "SUCCESSFULLY REMOVED\n\n";
    else std::cout << "NOTHING WAS REMOVED\n\n";
}

void test_history_remove(Database& database)
{
    char str[BUFFER_MAX];
    std::cout << "INPUT THE SEARCH TERM TO REMOVE FROM HISTORY\n";
    getStringInput(str, '\n');

    if (database.historyRemove(str)) std::cout << "SUCCESSFULLY REMOVED\n\n";
    else std::cout << "NOTHING WAS REMOVED\n\n";
}

void test_copy_database(Database& database)
{
    Database copy = database;

    std::cout << "ORIGINAL DATABASE MEMORY : " << &database
    << "\nCOPY DATABASE MEMORY ADDRESS : " << &copy << "\n\n";

    std::cout << "would you like to display the copied database? : 1 for \"yes\" 0 for \"no\"";

    if (getIntValue())
    {
        std::cout << "COPY SUPPORT LISTS\n\n";
        copy.display();

        std::cout << "COPY SEARCH HISTORY\n\n";
        copy.displaySearchHistory();
    }
}
