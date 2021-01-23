/* POKEMON SYSTEM INTERFACES */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
The following interfaces manage all Pokemon and Pokemon moves in the game. A Pokemon
can either be spawned in the wild by |Interface|, found in |Interface.h| or owned by
the |User| and inserted into the 2-3 tree |User::team|. All moves are stored in an
Array of doubly linked lists found in |list_library.h|. To teach a Pokemon a move,
a move must be retrieved from the array of doubly linked lists which is contained
by |Interface|.
*/

#ifndef POKEMON_H_
#define POKEMON_H_ 

#include <iostream>
#include "String.h"

//// FORWARD DECLARATIONS

class Pokemon;
class Move;

//// CONSTANTS 

//the max number of moves a pokemon can have at once
const int POKEMON_MOVE_MAX = 4;

/////////////////////////////////////////////////// GLOBAL OVERLOADS 

std::ostream& operator<<(std::ostream&, const Pokemon&);

std::ostream& operator<<(std::ostream&, const Move&);

/////////////////////////////////////////////////// POKEMON

/*
A |Pokemon| is either wild, or owned by a pokemon |Trainer|, which is either the |User|, or
an |NPC|. The |Interface| will manage the spawning of wild pokemon for the |User| to catch.
Spawns will be randomly generated using |RNG| and a small database system managed within
|Interface|.
*/

class Pokemon
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    //insert all information about the pokemon into ostream |out| except |catchRate|
    friend std::ostream& operator<<(std::ostream&, const Pokemon&);

    //comparison of |Pokemon::nickname|
    bool operator==(const Pokemon& other) const;
    bool operator==(const String& _nickname) const;
    bool operator<(const Pokemon& other) const;
    bool operator<(const String& _nickname) const;
    bool operator>(const Pokemon& other) const;
    bool operator>(const String& _nickname) const;

    //take damage from an opponent's attack
    Pokemon& operator-=(const int& attackPower); 

    ///////////////////////////////// CONSTRUCTORS 

    Pokemon();

    Pokemon(const String& _name, const int _maxHealth, const int _attack,
    const int _defense, const int _catchRate = 100, const String& _nickname = nullptr);

    Pokemon(const int pokemonIndex, Move* initialMove, const String& _nickname = nullptr);

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //insert all information about the pokemon into ostream |out| except |catchRate|
    //defaulted to |std::cout|
    void display(std::ostream& out = std::cout) const;

    //display the pokemon's name 
    void displayName() const;

    //display the name, nickname, and hp in a format for Pokemon battles
    void battleDisplay() const;

    //true if |currentHealth <= 0|
    bool isDead() const;

    //change the nickname of this Pokemon
    void changeNickname(const String& _nickname);

    //attempt to catch the Pokemon
    //if the Pokemon is caught, prompt the user for a nick name
    //|rand| will be a random value between 1 and 100
    //this Pokemon will be caught if |rand <= catchRate|, then return true
    bool attemptCatch(const int rand = 100);

    //teach a move to the pokemon
    //|newMove| will point to a |Move| from within |Interface::moveDatabase|
    void teachMove(Move* newMove);

    //call a move for the pokemon to use by index with |moveIndex|
    //overloaded to override which move is called which |Interface| will use with NPC Pokemon
    int callMove();
    int callMove(const int moveIndex);

    //replenish this Pokemon's hp
    void restore();

    private:
    ///////////////////////////////// DATA 

    //the Pokemon's official name
    String name;

    //// STATS

    // MAX HEALTH
    int maxHealth;

    // CURRENT HEALTH
    int currentHealth;

    // ATTACK
    int attack;

    // DEFENSE
    int defense;

    //the percent chance a trainer will catch the Pokemon
    int catchRate;

    //the number of moves this Pokemon knows
    int moveCount;

    //to hold the moves that the Pokemon will have access to
    Move* moves[POKEMON_MOVE_MAX];

    //the Pokemon's name that the trainer has set
    //this is also the key that |Tree<Pokemon>| will insert and retrieve by
    String nickname;

    ///////////////////////////////// PRIVATE FUNCTIONS 
};

/////////////////////////////////////////////////// MOVE 

/*
This abstraction handles the moves that a |Pokemon| would use in battle. An array of DLL
will serve as a database of moves using |ArrayDll| from |list_library.h|
*/

class Move
{
    public:
    ///////////////////////////////// OPERATOR OVERLOADS 

    friend std::ostream& operator<<(std::ostream&, const Move&);

    bool operator==(const Move& other) const;
    bool operator==(const String& _name) const;

    ///////////////////////////////// CONSTRUCTORS 
    
    Move();

    //all moves must have a |name| and a |basePower|
    Move(const String& _name, const int _basePower, const int _healthBuff = 0,
    const int _attackBuff = 0, const int _defenseBuff = 0);

    ///////////////////////////////// PUBLIC FUNCTIONS 

    //insert all non-zero information about the move into ostream |out|
    //defaulted to |std::cout|
    void display(std::ostream& out = std::cout) const;

    //call the move, returning the value of |basePower|
    //overloaded to handle a stat buff, if a Pokemon's stat is passed in
    int call() const;
    int call(int& pokemonStat) const;

    private:
    ///////////////////////////////// DATA 
    
    //the move's name
    String name;

    //the base power of the move
    int basePower;

    //// MOVE BUFFS

    //a value that will increase the caller's health stat
    int healthBuff;

    //a value that will increase the caller's attack stat
    int attackBuff;

    //a value that will increase the caller's defense stat
    int defenseBuff;
};

#endif
