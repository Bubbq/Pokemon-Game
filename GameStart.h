#ifndef GAMESTART_H
#define GAMESTART_H
// the class that start game execution

#include "PokemonDB.h"
#include "Trainer.h"
#include <string>


class GameStart{

    private:

    // dataBase of entire pokemon
    PokemonDB * pokemonDB;
    
    // filenames of the pokemon
    std::string kantoFilename = "/home/bubbq/Documents/Pokemon Game/kanto_pokemon.txt";
    std::string honenFilename = "/home/bubbq/Documents/Pokemon Game/honen_pokemon.txt"; 
    std::string johtoFilename = "/home/bubbq/Documents/Pokemon Game/johto_pokemon.txt";

    // TODO: filename for previous players!

    public:

    // constructor
    GameStart();
    //desctructors
    ~GameStart();

    // players choosing their starting pokemon
    void chooseStarter(Trainer&);

    // travel to another reigon
    void fastTravel(Trainer&);

    // awarding exp for the Trainer
    void giveExp(Trainer&);

    // where player looks for items (pokeballs, health potions, etc)
    void forage(Trainer&);

    // checks if teh user's choice is valid or not
    bool checkChoice(int, int, int);

    // main hub of the game
    void menu();

};

#endif
