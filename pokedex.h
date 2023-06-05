#ifndef POKEDEX_H
#define POKEDEX_H

#include "pokemon.h"

#include <iostream>
#include<vector>

struct node{

    Pokemon* pokemonInfo;
    node* next;

};

class Pokedex {
public:
    //node consts
    node* head; // the first node of a linked list
    node* tail; // the last element of a linked list.

    //method to print all the trainers  active pokemon
    void printCurrPokemon();
    void printPokemon();
    //method to find how many pokemon a trainer has
    int findNodeSize();

    //method to add pokemon to the trainers pokedex
    void appendPokemon(Pokemon * data);

    //method to remove pokemon by name (if the user chooses to)
    bool removePokemonByName(char* name);

    Pokemon * findPokemonAtIndex(int val);
    //constructor and destructor
    Pokedex();
    ~Pokedex();
};

#endif // POKEDEX_H
