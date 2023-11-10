#ifndef TRAINER_H
#define TRAINER_H

// for use of strings
#include "Pokemon.h"
#include "PokemonDB.h"
#include <string>

// representing a human as well as AI player
class Trainer{
    
    private:
    std::string name;
    Pokemon * currentPokemon;
    int mana;
    PokemonDB reigon;
    int exp;
    int level;

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

    // current reigon
    void setReigon(PokemonDB);
    PokemonDB getReigon();

    // exp
    void setExp(int);
    int getExp();

    // level
    void setLevel(int);
    int getLevel();

    // showing trainer's stats
    void showStats();

    // dialouge switching a players currentPokemon
    void switchPokemon();

};

#endif