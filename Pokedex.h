#ifndef POKEDEX_H
#define POKEDEX_H
#include "Pokemon.h"


struct node{

    Pokemon* pokemonInfo;
    node* next;

};



class Pokedex
{
    public:
        //node consts
        node* head; // the first node of a linked list
        node* tail; // the last element of a linked list.

        //method to print all the trainers  active pokemon
        void printCurrPokemon();

        //method to add pokemon to the trainers pokedex
        void appendPokemon(Pokemon * data);

        //method to remove pokemon by name (if the user chooses to)
        bool removePokemonByName(char* name);

        //methods to read file info into array of pokemon and into the linked list
        int getNumberOfRecords(char filename[]);
        void readPokemonDataBase(char filename[], Pokemon*&arr);

        //constructor and destructor
        Pokedex();
        ~Pokedex();




};

#endif // POKEDEX_H
