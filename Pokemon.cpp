#include "Pokemon.h"
#include <iostream>

// constructor
Pokemon::Pokemon(){

    this->name = "";
    this->baseAttackName = "";
    this->heavyAttackName = "";

    this->evoStage = 1;
    this->pokemonExp = 0;
    this->hp = 0;
    this->baseAttackDmg = 0;
    this->heavyAttackDmg = 0;

    this->type = NORMAL;
    this->rarity = COMMON;
}

// destructor
Pokemon::~Pokemon(){}

// setters and getters

// rarity
void Pokemon::setRarity(int val){this->rarity = (RARITY)val;}
RARITY Pokemon::getRarity(){return this->rarity;}

// name
void Pokemon::setName(std::string name) {this->name = name; }
std::string Pokemon::getName() {return this->name; }

// type
NATURE_TYPE Pokemon::getType(){return this->type;}
void Pokemon::setType(int type){this->type = (NATURE_TYPE)type;}
std::string Pokemon::getTypeAsString(){

    switch(this->type){
    case 1: return "Normal";
        break;
    case 2: return "Fire";
        break;
    case 3: return "Water";
        break;
    case 4: return "Electric";
        break;
    default: return "Grass";
        break;
    }
}

// evolution stage
void Pokemon::setEvoStage(int evoStage){this->evoStage = evoStage;}
int Pokemon::getEvoStage(){return this->evoStage;}

// exp
void Pokemon::setPokemonExp(int pokemonExp) {this->pokemonExp = pokemonExp;}
int Pokemon::getPokemonExp() { return this->pokemonExp; }

// hp
void Pokemon::setHp(double hp) {this->hp = hp;}
double Pokemon::getHp() { return this->hp; }

// base attack name
void Pokemon::setBaseAttackName(std::string baseAttackName) {this->baseAttackName = baseAttackName;}
std::string Pokemon::getBaseAttackName() { return this->baseAttackName;}

// base attack dmg
void Pokemon::setBaseAttackDmg(double baseAttackDmg) {this->baseAttackDmg = baseAttackDmg;}
double Pokemon::getBaseAttackDmg() {return this->baseAttackDmg;}

//heavy attack name
void Pokemon::setHeavyAttackName(std::string heavyAttackName) {this->heavyAttackName = heavyAttackName;}
std::string Pokemon::getHeavyAttackName() {return this->heavyAttackName;}

// heavy attack dmg
void Pokemon::setHeavyAttackDmg(double heavyAttackDmg) {this->heavyAttackDmg = heavyAttackDmg;}
double Pokemon::getHeavyAttackDmg() { return this->heavyAttackDmg; }

// to print the elements of a pokemon
void Pokemon::showStats() {
    std::cout << this->name;

    // only show fainted for dead pokemon 
    if (hp <= 0)
        std::cout << "(*FAINTED*)" << std::endl;
    else {
        std::cout << std::endl << std::endl
                  << "   HP: " << hp << std::endl
                  << "   Type: " << this->getTypeAsString() << std::endl
                  << "   Rarity: " << rarity << std::endl
                  << std::endl
                  << "   Normal Attack: " << this->baseAttackName << ", DMG: " << this->baseAttackDmg << std::endl
                  << "   Heavy Attack: " << this->heavyAttackName << ", DMG: " << this->heavyAttackDmg << std::endl
                  << std::endl;
    }
}


// dialouge once a pokemon evolves
void Pokemon::evolve(){
    this->pokemonExp = 0;
    std::cout << "Your pokemon has evolved into " << this->name << "!" << std::endl;
    std::cout << "Here are some of " << this->name << "'s stats: " << std::endl;
    this->showStats();

}
