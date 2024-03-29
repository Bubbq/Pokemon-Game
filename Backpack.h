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
    

    public:
        // the pokemon collection every user has
        std::vector<Pokemon> pokemonCollection;

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

        // health pots
        void setHealthPot(int);
        int getHealthPot();

        // mana pots
        void setManaPot(int);
        int getManaPot();

        // pokemonCollection
        void addPokemon(Pokemon);
        std::vector<Pokemon> getPokemonCollection();

        int getPokemon(std::string);

        // outputs all items the bag has
        void showContent(bool);
        // searches for a pokemon
        bool searchPokemon(Pokemon);
};

#endif