/* POKEMON SYSTEM IMPLEMENATION */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
All Pokemon and Pokemon moves are managed by these implementations. A Pokemon can have up to
4 moves, and contains various stats (health, attack, defense, catch rate). The |Interface| can
use its |rng| to randomly calculate a |pokemonIndex|, which is then passed into a new Pokemon object.
From here, the |Poe
*/

#include "Pokemon.h"
#include "PokemonDatabase.h"

/////////////////////////////////////////////////// GLOBAL OVERLOADS 

//insert all information about the pokemon into ostream |out| except |catchRate|
std::ostream& operator<<(std::ostream& out, const Pokemon& pokemon)
{
    pokemon.display(out);
    return out;
}

std::ostream& operator<<(std::ostream& out, const Move& move)
{
    move.display(out);
    return out;
}

/////////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

Pokemon::Pokemon() : name("NONE"), maxHealth(0), attack(0), defense(0), catchRate(0), moveCount(0) {}

/////////////////////////////////////////////////// COPY CONSTRUCTORS 

/////////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

Pokemon::Pokemon(const String& _name, const int _maxHealth, const int _attack,
    const int _defense, const int _catchRate, const String& _nickname) :
    
    name(_name), maxHealth(_maxHealth), currentHealth(_maxHealth), attack(_attack),
    defense(_defense), catchRate(_catchRate), nickname(_nickname) {}

Pokemon::Pokemon(const int pokemonIndex, Move* initialMove, const String& _nickname) : moveCount(1), nickname(_nickname)
{
    //set the initial move
    moves[0] = initialMove;

    //set the name
    name = Names[pokemonIndex];

    //set the unique stats
    maxHealth = currentHealth = healthStats[pokemonIndex];
    attack = attackStats[pokemonIndex];
    defense = defenseStats[pokemonIndex];
    catchRate = catchRates[pokemonIndex];
}

Move::Move(const String& _name, const int _basePower, const int _healthBuff,
    const int _attackBuff, const int _defenseBuff) :

    name(_name), basePower(_basePower), healthBuff(_healthBuff),
    attackBuff(_attackBuff), defenseBuff(_defenseBuff) {}

/////////////////////////////////////////////////// DESTRUCTORS 

/////////////////////////////////////////////////// POKEMON 

//return the resulting comparison of the Pokemon nicknames
bool Pokemon::operator==(const Pokemon& other) const
{
    return nickname == other.nickname;
}

//return the resulting comparison of the Pokemon's nickname with |_nickname|
bool Pokemon::operator==(const String& _nickname) const
{
    return nickname == _nickname;
}

//return the resulting comparison of the Pokemon nicknames
bool Pokemon::operator<(const Pokemon& other) const
{
    return nickname < other.nickname;
}

//return the resulting comparison of the Pokemon's nickname with |_nickname|
bool Pokemon::operator<(const String& _nickname) const
{
    return nickname < _nickname;
}

//return the resulting comparison of the Pokemon nicknames
bool Pokemon::operator>(const Pokemon& other) const
{
    return nickname > other.nickname;
}

//return the resulting comparison of the Pokemon's nickname with |_nickname|
bool Pokemon::operator>(const String& _nickname) const
{
    return nickname > _nickname;
}

//take damage from an opponent's attack
//factoring in the defense
Pokemon& Pokemon::operator-=(const int& attackPower)
{
    //in the event |defense| is stronger than |attackPower|
    //a measly 10 damage points will still be subtracted
    currentHealth -= (attackPower / defense) + 10;
    return *this;
}

//insert all information about the pokemon into ostream |out| except |catchRate|
//defaulted to |std::cout|
void Pokemon::display(std::ostream& out) const
{
    out << name;

    if (!nickname.empty()) out << " // " << nickname;

    out << " // HP  : " << currentHealth << " / " << maxHealth
    << "\nATK : " << attack
    << "\nDEF : " << defense
    << "\nMOVES";

    for (int i = 0; i < moveCount; ++i) std::cout << '\n' << i + 1 << ") " << *moves[i];
}

//display the pokemon's name 
void Pokemon::displayName() const
{
    std::cout << name;
}

//display the name, nickname, and hp in a format for Pokemon battles
void Pokemon::battleDisplay() const
{
    std::cout << name << " // " << nickname
    << " HP : " << currentHealth << " / " << maxHealth << "\n\n";
}

//true if |currentHealth <= 0|
bool Pokemon::isDead() const
{
    return 0 >= currentHealth;
}

//change the nickname of this Pokemon
void Pokemon::changeNickname(const String& _nickname)
{
    nickname = _nickname;
}

//attempt to catch the Pokemon
//if the Pokemon is caught, prompt the user for a nick name
//|rand| will be a random value between 1 and 100
//this Pokemon will be caught if |rand <= catchRate|, then return true
bool Pokemon::attemptCatch(const int rand)
{
    if (rand <= catchRate)
    {
        std::cout << "You caught " << name
        << "!\nplease enter a nickname for your Pokemon\n>>> ";
        nickname.getInput();

        return true;
    }
    else std::cout << "You did not catch " << name << " and it fleed...\n\n";

    return false;
}

//teach a move to the pokemon
//|newMove| will point to a |Move| from within |Interface::moveDatabase|
void Pokemon::teachMove(Move* newMove)
{
    if (!newMove) return;

    //if the Pokemon already knew 4 moves, ask the user if they want to replace one with |newMove|
    if (moveCount == POKEMON_MOVE_MAX)
    {
        std::cout << '\n' << name << "already knows 4 moves...\n"
        << "would you like to replace one of the 4 moves? 1 for \"yes\" : 0 for \"no\"\n>>> ";

        Int intBuffer;

        if (intBuffer.getInput(0, 1))
        {
            //prompt another option to quit the process
            std::cout << "0) Nevermind!\n";

            //display the 4 moves the Pokemon currently knows
            for (int i = 0; i < POKEMON_MOVE_MAX; ++i) std::cout << i + 1 << ") " << *moves[i];

            std::cout << "which move would you like to replace with " << *newMove << "?\n>>> ";

            switch (intBuffer.getInput(0, 4))
            {
                case 0:
                    std::cout << '\n' << name << " did not learn " << *newMove << "...\n\n";
                    break;

                case 1: moves[0] = newMove; break;
                case 2: moves[1] = newMove; break;
                case 3: moves[2] = newMove; break;
                case 4: moves[3] = newMove; break;

                default: break;
            }
        }
    }

    //there was room for the new move, insert it
    else
    {
        moves[moveCount] = newMove;
        ++moveCount;
    }
}

//get user input to determine which Pokemon move to use
int Pokemon::callMove()
{
    //get a desired move index from the user
    Int moveIndex;
    std::cout << "call a move\ninteger >>> ";

    //return a factor of the move's base power and the Pokemon's attack stat
    return (callMove(moveIndex.getInput(1, moveCount) - 1) * attack);
}

//call a move for the pokemon to use by index with |moveIndex|
//overloaded to override which move is called which |Interface| will use with NPC Pokemon
int Pokemon::callMove(const int moveIndex)
{
    return ((0 <= moveIndex && moveCount > moveIndex) ?
    moves[moveIndex]->call() : 0);
}

//replenish this Pokemon's hp
void Pokemon::restore()
{
    currentHealth = maxHealth;
}

/////////////////////////////////////////////////// MOVE 

bool Move::operator==(const Move& other) const
{
    return name == other.name;
}

bool Move::operator==(const String& _name) const
{
    return name == _name;
}

//insert all non-zero information about the move into ostream |out|
//defaulted to |std::cout|
void Move::display(std::ostream& out) const
{
    std::cout << name;

    if (basePower) std::cout << " || PWR : "  << basePower;
    if (healthBuff) std::cout << " || HP+ : "  << healthBuff;
    if (attackBuff) std::cout << " || ATK+ : " << attackBuff;
    if (defenseBuff) std::cout << " || DEF+ : " << defenseBuff;

    std::cout << "\n\n";
}

//call the move, returning the value of |basePower|
//overloaded to handle a stat buff, if a Pokemon's stat is passed in
int Move::call() const
{
    return basePower;
}

//only 1 buff can be non-zero, resulting in the correct Pokemon stat being modified
int Move::call(int& pokemonStat) const
{
    pokemonStat += healthBuff + attackBuff + defenseBuff;
    return basePower;
}
