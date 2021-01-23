/* GAME INTERFACE IMPLEMENATION */

//Sean Siders
//CS202
//11/14/2020
//Program 3 : Pokemon!

/*
All interfaces for the game are implemented here. |Interface| is the primary game
interface that walks the |User| through the gameplay. Currently, the gameplay is basic
rng to determine 1 of 2 possiblities (a wild Pokemon spawn, or a Pokemon battle). In a
spawn, the user will have the opportunity to catch the Pokemon. In a battle, the user
will choose one of their Pokemon to battle another randomly generated Pokemon.
*/

#include "Interface.h"
#include "PokemonDatabase.h"

/////////////////////////////////////////////////// GLOBAL OVERLOADS 

//display the trainer and their current Pokemon with that Pokemon's stats
std::ostream& operator<<(std::ostream& out, const User& player)
{
    out << player.name;

    if (player.called) 
    {
        out << "'s " << "current Pokemon\n";
        out << *player.called;
    }

    std::cout << '\n';

    return out;
}

/////////////////////////////////////////////////// DEFAULT CONSTRUCTORS 

//seed the random number generator
RNG::RNG() 
{
    srand(time(nullptr));
}

//setup the database of moves
Interface::Interface() : moveDatabase(3)
{
    moveDatabase[ATTACK].insert(Move("ember", 25));
    moveDatabase[ATTACK].insert(Move("water gun", 25));
    moveDatabase[ATTACK].insert(Move("vine whip", 25));
    moveDatabase[ATTACK].insert(Move("thundershock", 50));

    moveDatabase[DEFEND].insert(Move("reflect", 40));
    moveDatabase[DEFEND].insert(Move("barrier", 20));
    moveDatabase[DEFEND].insert(Move("shield", 50));

    moveDatabase[BUFF].insert(Move("growl", 0));
    moveDatabase[BUFF].insert(Move("screech", 0));
    moveDatabase[BUFF].insert(Move("scary face", 0));
}

//get a username from the user
User::User() : called(nullptr)
{
    std::cout << "Enter a username...\n>>> ";
    name.getInput();
}


NPC::NPC() {}

/////////////////////////////////////////////////// COPY CONSTRUCTORS 

/////////////////////////////////////////////////// INITIALIZATION CONSTRUCTORS 

/////////////////////////////////////////////////// DESTRUCTORS 

Interface::~Interface()
{
}

/////////////////////////////////////////////////// USER 

//take damage from an opponent
User& User::operator-=(const int attackPower)
{
    if (called) *called -= attackPower;
    return *this;
}

//display the user's team of Pokemon, alphabetized by nickname
void User::displayTeam() const
{
    std::cout << team;
}

//display the current |called| Pokemon in battle
void User::battleDisplay() const
{
    if (called)
    {
        std::cout << "\nYOUR POKEMON\n================\n";
        std::cout << *called;
    }
}

//determine if the user's called Pokemon is dead
bool User::lost() const
{
    return called->isDead();
}

//when a pokemon was caught, give it a nickname and insert it into |team|
void User::addPokemon(const Pokemon& newPokemon)
{
    team.insert(newPokemon);
}

//attempt to call a Pokemon from |team| out by nickname with user input
//set |called| to the matching Pokemon once successfully retrieved from |team|
void User::callPokemon()
{
    //to hold user input for the Pokemon's nickname
    String nickname;

    std::cout << "call out one of your Pokemon by its nickname...\n\n" << team
    << "Pokemon nickname >>> ";

    nickname.getInput(DEFAULT_LENGTH);
    clearScreen();

    //catch the user's called Pokemon
    called = team.retrieve(nickname);

    //attempt to call a Pokemon out by its nickname until the user successfully calls one
    while (!called)
    {
        std::cout << "None of your Pokemon have that nickname, try again...\n\n" << team
        << "Pokemon nickname >>> ";

        nickname.getInput(DEFAULT_LENGTH);
        clearScreen();
        called = team.retrieve(nickname);
    }

    std::cout << "\nYOU : Go " << nickname << "!!!\n\n";
}

//do a battle formatted display of the |called| Pokemon
//call a move for |called| to use in battle
//return the calculated power of the move
int User::callMove()
{
    if (called) return called->callMove();

    return 0;
}

//teach the user's |called| Pokemon a new move after victory in battle
void User::teachMove(Move* newMove)
{
    if (called && newMove)
    {
        called->teachMove(newMove);

        std::cout << "\nOK, ";
        called->displayName();
        std::cout << " learned a new move...\n";
        std::cout << *newMove;
    }
}

//call the Pokemon back into its pokeball
//restore the Pokemon's hp
void User::callBack()
{
    if (!called) return;

    called->displayName();

    std::cout << "! Good job buddy! Return!!!\n\n";

    called->restore();
    called = nullptr;
}

/////////////////////////////////////////////////// RNG 

//generate a random number n where 0 <= n <= range, then add the minimum value 
int RNG::generate(const int min, const int max) const
{
	//get the range of possible numbers
	const int range = max - min;
	
	return (rand() % (range + 1)) + min;
}

/////////////////////////////////////////////////// INTERFACE 

//the game intro where the user selects their first Pokemon
void Interface::intro()
{
    clearScreen();

    std::cout
    << "================================\n"
    << "Welcome to the world of POKEMON!\n\n"
    << "================================\n"
    << "please select your starter Pokemon...\n\n"
    << "1) Torchic (The fire chicken)\n"
    << "2) Treecko (The grass lizard)\n"
    << "3) Mudkip (The water frog)\n"
    << "4) Pikachu (The electric mouse)\n\ninteger >>> ";

    //database starts at index 0, so |- 1| is needed to achieve the true Pokemon's index
    int pokemonIndex = intBuffer.getInput() - 1;

    std::cout << "Enter a nickname for your new Pokemon!\n>>> ";
    stringBuffer.getInput(DEFAULT_LENGTH);

    //add the new pokemon with passing in it's key index
    //a move will be retrieved by key from the database
    //|stringBuffer| will be the nickname of the Pokemon
    player.addPokemon(Pokemon(pokemonIndex, moveDatabase.retrieve(initialMoveKeys[pokemonIndex]), stringBuffer));
}

//a wild Pokemon was encountered, the |User| can attempt to catch it
void Interface::pokemonEncounter()
{
    //generate a random Pokemon
    int pokemonIndex = rng.generate(0, POKEMON_COUNT - 1);
    Pokemon wildPokemon(pokemonIndex, moveDatabase.retrieve(initialMoveKeys[pokemonIndex]));

    clearScreen();

    std::cout << "A wild " << Names[pokemonIndex] << " appeared!\n"
    << "0) flee\n"
    << "1) throw a pokeball\n\ninteger >>> ";

    if (intBuffer.getInput(0, 1))
    {
        //attempt to catch the Pokemon
        //|Pokemon::catchRate| will determine the overall odds of catching the Pokemon
        //if the Pokemon is caught, the user will be prompted for a nickname, then it will be added to the user's team
        if (wildPokemon.attemptCatch(rng.generate(1, 100))) player.addPokemon(wildPokemon);
    }
    else std::cout << "You fleed from " << Names[pokemonIndex] << "...\nit seems sad that you left ):\n\n";
}

//another Pokemon trainer |NPC| was encountered, the |User| must battle them
void Interface::trainerBattle()
{
    clearScreen();

    std::cout << "\n! You and another Pokemon trainer have locked eyes and it is time to battle!!!\n\n";

    //generate a random Pokemon
    int pokemonIndex = rng.generate(0, POKEMON_COUNT - 1);
    Pokemon opponent(pokemonIndex, moveDatabase.retrieve(initialMoveKeys[pokemonIndex]));

    std::cout << "OPPONENT : Go " << Names[pokemonIndex] << "!!!\n\n";

    //have the player call out their Pokemon
    player.callPokemon();

    //enter a battle between the 2 called Pokemon
    battle(opponent);
}

//conduct a battle between the |player| Pokemon and |opponent| Pokemon
void Interface::battle(Pokemon& opponent)
{
    //when the battle is over, set to true
    bool over = false;

    do
    {
        //display the opponent and the user Pokemon
        std::cout << "\nOPPONENT POKEMON\n================\n";
        opponent.battleDisplay();

        player.battleDisplay();

        //let the user attack the opponent
        opponent -= player.callMove();

        //if the opponent's hp dropped to or below 0
        if (opponent.isDead())
        {
            over = true;
            clearScreen();
            std::cout << "\nYOU WON THE POKEMON BATTLE!\n";

            learnNewMove();
        }

        //let the opponent attack the user's Pokemon
        else
        {
            clearScreen();

            std::cout << "\nTHE OPPONENT HAS ATTACKED!!!\n\n";
            player -= opponent.callMove(0);

            //if the user's called Pokemon is dead
            if (player.lost())
            {
                over = true;
                std::cout << "YOUR POKEMON HAS BEEN DEFEATED...\n\n";
            }
            else
            {
                //display the opponent and the user Pokemon
                std::cout << "\nOPPONENT POKEMON\n================\n";
                opponent.battleDisplay();

                player.battleDisplay();
            }
        }

        std::cout << "HIT ENTER TO CONTINUE\n\n";
        std::cin.get();
        clearScreen();
    }
    while (!over);

    //call the Pokemon back and heal
    player.callBack();
}

//upon user success in a Pokemon battle, the user's Pokemon can learn a new move
//the new move will be retrieved from |moveDatabase| with user input
void Interface::learnNewMove()
{
    std::cout << "your Pokemon wants to learn a new move!!!\n\n";

    player.battleDisplay();

    std::cout << "AVAILABLE MOVES\n\n";
    displayMoveDatabase();
    std::cout << "select a new move to teach your Pokemon...\nmove name >>> ";

    stringBuffer.getInput(DEFAULT_LENGTH);

    Move* newMove = moveDatabase.retrieve(stringBuffer);

    while (!newMove)
    {
        std::cout << "No move matches the input provided...\n\n";
        displayMoveDatabase();
        std::cout << "select a new move to teach your Pokemon...\nmove name >>> ";

        stringBuffer.getInput(DEFAULT_LENGTH);

        newMove = moveDatabase.retrieve(stringBuffer);
    }

    //have the user's Pokemon learn a new move
    player.teachMove(newMove);
}

//display |moveDatabase| in the 3 different move categories
//ATTACK, DEFEND, BUFF
void Interface::displayMoveDatabase() const
{
    std::cout
    << "\nOFFENSE\n" << moveDatabase[ATTACK]
    << "\nDEFENSE\n" << moveDatabase[DEFEND]
    << "\nBUFF\n" << moveDatabase[BUFF];
}

//play the |intro| then use |rng| to determine whether a:
//|pokemonEncounter()| has occured
//|pokemonBattle()| has occured
//loop the process of encounters and battles to simulate gameplay
void Interface::run()
{
    //play through the game intro where the user selects their first Pokemon
    intro();

    //// MAIN GAME LOOP
    do
    {
        // determine whether a pokemon encounter or trainer battle occurs
        if (50 > rng.generate(0, 100)) pokemonEncounter(); 
        else trainerBattle();

        std::cout << "continue playing? 1 for \"yes\" : 0 for \"no\"\n>>> ";
    }
    while (intBuffer.getInput(0, 1));
}


