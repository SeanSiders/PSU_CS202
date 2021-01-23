/* GAME INTERFACES */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
All interfaces managing the input and output between the user and game is in this file.
|Interface| will handle the top level game interface procedures, bouncing between 
wild Pokemon spawns where a |User| can attempt to catch a Pokemon, and a trainer battle
where the user can select one Pokemon to battle the opponent.
*/

#ifndef INTERFACE_H_ 
#define INTERFACE_H_ 

#include <iostream>
#include <cstdlib>
#include "String.h"
#include "list_library.h"
#include "tree_library.h"
#include "Pokemon.h"

//clear the console screen, (Linux and Posix Specific)
static inline void clearScreen()
{
    system("clear");
}

//// FORWARD DECLARATIONS

class Pokemon;
class Move;
class User;

/////////////////////////////////////////////////// MOVE ARRAY DLL ENUM 

/*
The following enum is designed to access the database of moves within the game. This
database is an array of DLL, found in |list_library.h|. There are 3 types of moves in
database, and 3 respective enum values to access them by type.
*/

enum MOVE_TYPE
{
    ATTACK, // ATTACK DLL
    DEFEND, // DEFEND DLL
    BUFF // BUFF DLL
};

/////////////////////////////////////////////////// GLOBAL OVERLOADS 

std::ostream& operator<<(std::ostream&, const User&);

/////////////////////////////////////////////////// USER 

/*
This class manages the User's Pokemon team, which is modifed upon catching a wild Pokemon,
and engaging in a Pokemon battle. Both of these events are determined by |Interface|.
*/

class User
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    //take damage from an opponent
    User& operator-=(const int attackPower);

    friend std::ostream& operator<<(std::ostream&, const User&);

    ///////////////////////////////// CONSTRUCTORS 

    User();

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //display the user's team of Pokemon, alphabetized by nickname
    void displayTeam() const;

    //display the current |called| Pokemon in battle
    void battleDisplay() const;

    //determine if the user's called Pokemon is dead
    bool lost() const;

    //when a pokemon was caught, give it a nickname and insert it into |team|
    void addPokemon(const Pokemon& newPokemon);

    //attempt to call a Pokemon from |team| out by nickname with user input
    //set |called| to the matching Pokemon once successfully retrieved from |team|
    void callPokemon();

    //do a battle formatted display of the |called| Pokemon
    //call a move for |called| to use in battle
    //return the calculated power of the move
    int callMove();

    //teach the user's |called| Pokemon a new move after victory in battle
    void teachMove(Move* newMove);

    //call the Pokemon back into its pokeball
    //restore the Pokemon's hp
    void callBack();

    private:
    ///////////////////////////////// DATA 

    //the trainer's name
    String name;

    //all Pokemon the user owns
    tree_library::Tree<Pokemon> team;

    //the users current Pokemon in battle
    Pokemon* called;
};

/////////////////////////////////////////////////// NPC 

class NPC
{
    public:
    ///////////////////////////////// CONSTRUCTORS 

    NPC();
};

/////////////////////////////////////////////////// RNG 

/*
This class will manage random number generation to simulate factors of chance during gameplay.
It is primarily used by |Interface| in simulating wild |Pokemon| spawns and catch rates.
*/

class RNG
{
    public:
    ///////////////////////////////// CONSTRUCTORS 

    RNG();

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //generate a random number n where 0 <= n <= range, then add the minimum value 
    int generate(const int min, const int max) const;
};

/////////////////////////////////////////////////// Interface 

/*
This is the top level interface for the user to interact with. All input is handled here,
And the primary calling routine of the game is managed within |run()|. A database of
all Pokemon moves is managed with |moveDatabase|.
*/

class Interface
{
    public:
    ///////////////////////////////// CONSTRUCTOR 

    Interface();

    ~Interface();

    ///////////////////////////////// PUBLIC FUNCTIONS

    //the game intro where the user selects their first Pokemon
    void intro();

    //a wild Pokemon was encountered, the |User| can attempt to catch it
    void pokemonEncounter();

    //another Pokemon trainer |NPC| was encountered, the |User| must battle them
    void trainerBattle();

    //play the |intro| then use |rng| to determine whether a:
    //|pokemonEncounter()| has occured
    //|pokemonBattle()| has occured
    //loop the process of encounters and battles to simulate gameplay
    void run();

    private:
    ///////////////////////////////// DATA 

    //the user string input buffer
    String stringBuffer;

    //the user int input buffer
    Int intBuffer;

    //all information about the user playing the game
    User player;

    //all moves that are available in the game
    list_library::ArrayDll<Move> moveDatabase;

    //random number generator
    RNG rng;

    ///////////////////////////////// PRIVATE FUNCTIONS 

    //conduct a battle between a user Pokemon and a opponent Pokemon
    void battle(Pokemon& opponent);

    //upon user success in a Pokemon battle, the user's Pokemon can learn a new move
    //the new move will be retrieved from |moveDatabase| with user input
    void learnNewMove();

    //display |moveDatabase| in the 3 different move categories
    //ATTACK, DEFEND, BUFF
    void displayMoveDatabase() const;
};

#endif
