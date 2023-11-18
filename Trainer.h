#ifndef TRAINER_H
#define TRAINER_H

#include "Backpack.h"

// representing a human
class Trainer{
    
    private:
   
        std::string name;
        int mana;
        int exp;
        int level;

    public:

        int pokemonIndex = 0;
        Backpack * backpack;
        Pokemon * currentPokemon;

        // construtor
        Trainer();
        //destructor
        ~Trainer();

        // Setters and Getters

        // trainer name
        void setName(std::string);
        std::string getName();

        // current pokemon
        void setCurrentPokemon(Pokemon*);
        Pokemon * getCurrentPokemon();

        // mana
        void setMana(int);
        int getMana();

        // exp
        void setExp(int);
        int getExp();

        // level
        void setLevel(int);
        int getLevel();

        // showing trainer's stats
        void showStats(std::string);

        // dialouge switching a players currentPokemon
        void switchPokemon();

        // to use a mana
        void useManaPot();

        // to use health pot, healing a pokemon
        void useHealthPot(std::vector<Pokemon>);

        // to run away from a pokemon fighting encounter, will lose random item in a random amout
        void flee();

        // validate user input
        void choiceCheck(int, int&, int, std::string);
};

#endif