#ifndef GameFunction_H
#define GameFunction_H
// the class that start game execution

#include "PokemonDB.h"
#include "Trainer.h"
#include <string>
#include <vector>


// provides the backend functionality of the game
class GameFunction{

    private:

        // dataBase of alll pokemon reigons
        PokemonDB * pokemonDB;

        // filenames of the pokemon, UPDATE FILEPATH HERE!!!
        std::string kantoFilename = "kanto_pokemon.txt";
        std::string honenFilename = "honen_pokemon.txt"; 
        std::string johtoFilename = "johto_pokemon.txt";

    public:

        // constructor
        GameFunction();
        //desctructors
        ~GameFunction();

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
        // error handiling if user is fighting with no mana
        bool attackWithNoMana(Trainer& player, bool);

        // generates a random number
        int randomNumber(int, int);
};

#endif
