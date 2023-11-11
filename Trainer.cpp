#include <iostream>
#include "Backpack.h"
#include "Pokemon.h"
#include "Trainer.h"


// constructor
Trainer::Trainer(){
    
    this->name = "Ash Ketchum";
    this->mana = 100;
    this->exp = 0;
    this->level = 1;
    this->currentPokemon = new Pokemon();
    this->backpack = new Backpack();
}

// destructor
Trainer::~Trainer(){}

// Setters and Getters

// name
void Trainer::setName(std::string name){this->name = name;}
std::string Trainer::getName(){return this->name;}

// currentPokemon
void Trainer::setCurrentPokemon(Pokemon *currentPokemon){this->currentPokemon = currentPokemon;}
Pokemon* Trainer::getCurrentPokemon(){return this->currentPokemon;}

// mana
void Trainer::setMana(int mana){this->mana = mana;}
int Trainer::getMana(){return this->mana;}

//exp
void Trainer::setExp(int exp){this->exp = exp;}
int Trainer::getExp(){return this->exp;}

// level
void Trainer::setLevel(int level){this->level = level;}
int Trainer::getLevel(){return this->level;}

// dialouge to switch a players pokemon

void Trainer::switchPokemon(){
    std::cout << "Which Pokemon do you want to switch to?" << std::endl;
    // TODO: make Backpack class output all pokemon
    
    // based on the index of the choice, setCurrentPokemon(vector<Pokemon>[userIndexChosen])
}

Backpack* Trainer::getBackpack(){return this->backpack;}

// showing trainers stats
void Trainer::showStats(){

    std::cout << "Name: " << this->name << std::endl;
    std:: cout << "Level: " << this->level << std::endl;
    // TODO: make PokemonDB have method making reigon toString
    
    std::cout << std::endl;

    // output everything the backpack has
    this->backpack->showContent();
}
