#include "Backpack.h"
#include <iostream>
#include <iterator>
#include <ostream>
    
// constructor
Backpack::Backpack(){

    this->pokeBalls = 10;
    this->greatBalls = 5;
    this->ultraBalls = 2;
    this->healthPot = 3;
    this->manaPot = 3;

};
// destructor
Backpack::~Backpack(){};

// Setters and Getters

//pokeball
void Backpack::setPokeBalls(int pokeBalls){this->pokeBalls = pokeBalls;};
int Backpack::getPokeBalls(){return this->pokeBalls;}

// greatball
void Backpack::setGreatBalls(int greatBalls){this->greatBalls = greatBalls;}
int Backpack::getGreatBalls(){return this->greatBalls;}

// ultraball
void Backpack::setUltraBalls(int ultraBalls){this->ultraBalls = ultraBalls;}
int Backpack::getUltraBalls(){return this->ultraBalls;}

// pokemonCollection
void Backpack::addPokemon(Pokemon pokemon){this->pokemonCollection.push_back(pokemon);}
Pokemon Backpack::getPokemon(int index){return this->pokemonCollection[index];}

// health pots
void Backpack::setHealthPot(int healthPot){this->healthPot = healthPot;}
int Backpack::getHealthPot(){return this->healthPot;}

// mana pots
void Backpack::setManaPot(int manaPot){this->manaPot = manaPot;}
int Backpack::getManaPot(){return this->manaPot;}

// other functionality

// outputs all items the bag has
void Backpack::showContent(){

    // output all the items
    std::cout << "Items: " << std::endl << std::endl;

    std::cout << "Pokeballs: " << this->pokeBalls << std::endl;
    std::cout << "Greatballs: " << this->greatBalls << std::endl;
    std::cout << "Ultraballs: " << this->ultraBalls << std::endl << std::endl;

    std::cout << "Health Pots: " << this->healthPot << std::endl;
    std:: cout << "Mana Pots: " << this->manaPot << std::endl << std::endl;

    //output all the users pokemon

    std::cout << "Pokemon Collection:" << std::endl << std::endl;

    for(int i = 0; i < this->pokemonCollection.size(); i++){
        // print the pokemoncount and the stats
        std::cout << i + 1 << ".) ";
        pokemonCollection[i].showStats();
    }


}
// searches for a pokemon
bool Backpack::searchPokemon(Pokemon pokemon){

    for(int i = 0; i < this->pokemonCollection.size(); i++){
        if(pokemon.getName() == this->pokemonCollection[i].getName())
            return true;
    }
    
    return false;
}
