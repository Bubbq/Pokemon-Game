#ifndef TRAINER_H
#define TRAINER_H

// for use of strings
#include "Backpack.h"
#include "Pokemon.h"
#include "PokemonDB.h"
#include <string>
#include <vector>

// representing a human as well as AI player
class Trainer{
    
    private:
   
    std::string name;
    int mana;
    int exp;
    int level;
    Pokemon * currentPokemon;
    Backpack * backpack;

    public:

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

    Backpack * getBackpack();

    // showing trainer's stats
    void showStats(int);

    // dialouge switching a players currentPokemon
    void switchPokemon();

    // to use a mana
    void useManaPot();

    // to use health pot, healing a pokemon
    void useHealthPot(std::vector<Pokemon>);

    // to run away from a pokemon fighting encounter, will lose random item in a random amout
    void flee();

};

#endif