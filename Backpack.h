#ifndef BACKPACK_H
#define BACKPACK_H

#include "Pokemon.h"
#include <vector>

// representing the storage a trainer has 
class Backpack{
    
    private:
    
    int pokeBalls;
    int greatBalls;
    int ultraBalls;
    std::vector<Pokemon> pokemonCollection;
    int healthPot;
    int manaPot;

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