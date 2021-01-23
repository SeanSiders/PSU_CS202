/* GAME INTERFACES */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
This file contains a database of all keys related to each Pokemon. RNG will generate a number between 0 and
|POKEMON_COUNT| - 1, where all information can be pulled from the arrays with that cooresponding index.
*/

#ifndef POKEMON_DATABASE_H_ 
#define POKEMON_DATABASE_H_ 

#include "Pokemon.h"

//// FORWARD DECLARATION

class Move;

//// CONSTANT 
const int POKEMON_COUNT = 4;

//all possible Pokemon names
const String Names[POKEMON_COUNT] =
{
    "Torchic",
    "Treecko",
    "Mudkip",
    "Pikachu"
};

//initial moves for each Pokemon
const String initialMoveKeys[POKEMON_COUNT] =
{
    "ember",
    "vine whip",
    "water gun",
    "thundershock"
};

//the health stats for each Pokemon
const int healthStats[POKEMON_COUNT] =
{
    100,
    120,
    90,
    80
};

//the attack stats for each Pokemon
const int attackStats[POKEMON_COUNT] =
{
    95,
    100,
    110,
    120
};

//the defense stats for each Pokemon
const int defenseStats[POKEMON_COUNT] =
{
    100,
    90,
    80,
    90
};

//the catch rates for each Pokemon
const int catchRates[POKEMON_COUNT] =
{
    45,
    45,
    45,
    25
};

#endif
