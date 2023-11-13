#ifndef GAMESTART_H
#define GAMESTART_H
// the class that start game execution

#include "PokemonDB.h"
#include "Trainer.h"
#include <string>
#include <vector>


class GameStart{

    private:

    // dataBase of every pokemon
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

    // Setters and getters

    // the currentDB
    void setCurrentDB(std::string);
    std::vector<Pokemon>getCurrentDB();

    // players choosing their starting pokemon
    void chooseStarter(Trainer&);

    // travel to another reigon
    void fastTravel(Trainer&);

    // awarding exp for the Trainer
    void giveExp(Trainer&);

    // where player looks for items (pokeballs, health potions, etc)
    void forage(Trainer&);
    // dialouge for finding stuff while foraging
    void forageDialouge(int, std::string);

    // main hub of the game
    void menu(Trainer&);

    // dialouge to start the game
    void startGame(Trainer&);

    // to clear terminal based to OS
    void clear();

    // to validate user choice
    void choiceCheck(int, int&, int, std::string);


};

#endif
