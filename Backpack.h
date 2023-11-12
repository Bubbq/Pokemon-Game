#ifndef BACKPACK_H
#define BACKPACK_H

#include "Pokemon.h"
#include <vector>

// representing the storage a trainer has 
class Backpack{
    
    private:
    
    // quantifiable items
    int pokeBalls;
    int greatBalls;
    int ultraBalls;
    int healthPot;
    int manaPot;
    
    // the pokemon collection every user has
    std::vector<Pokemon> pokemonCollection;

    public:

    // constructor
    Backpack();
    // destructor
    ~Backpack();

    // Setters and Getters

    //pokeball
    void setPokeBalls(int);
    int getPokeBalls();

    // greatball
    void setGreatBalls(int);
    int getGreatBalls();

    // ultraball
    void setUltraBalls(int);
    int getUltraBalls();

    // pokemonCollection
    void addPokemon(Pokemon);
    Pokemon getPokemon(int);

    // other functionality

    // outputs all items the bag has
    void showContent();
    // searches for a pokemon
    bool searchPokemon(Pokemon);
};

#endif