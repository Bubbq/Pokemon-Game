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
    PokemonDB * getCurrentDB();

    // awarding exp for the Trainer
    void giveExp(Trainer&, int);


    // to clear terminal based to OS
    void clear();

    // to validate user choice
    void choiceCheck(int, int&, int, std::string);

    // where player looks for items (pokeballs, health potions, etc)
    void forageSim(Trainer&);
    // dialouge for finding stuff while foraging
    void forageDialouge(int, std::string);
   
    // simulates the catch chance
    bool catchSim(Trainer&, int, int&, int, Pokemon&);

    // simulating the attacking interation 
    bool attackSim(Pokemon&, Pokemon&, Trainer&, int, int&);
    // dialouge of the fight interaction
    bool attackDialouge(Trainer&, Pokemon&, Pokemon&, int, int&, std::string, double);
    // error handling if user is trying to fight w no HP
    bool attackWithNoHP(Pokemon);

    // generates a random number
    // used for forage and catch simulation and  
    int randomNumber(int, int);

};

#endif
