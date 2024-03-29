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

// rarity
void Pokemon::setRarity(int val){this->rarity = (RARITY)val;}
RARITY Pokemon::getRarity(){return this->rarity;}
std::string Pokemon::getRarityAsString(){
    switch (this->rarity) {
        case 1: return "Common"; break;
        case 2: return "Uncommon"; break;
        case 3: return "Rare"; break;
        case 4: return "Legendary"; break;
    }
}

// name
void Pokemon::setName(std::string name) {this->name = name; }
std::string Pokemon::getName() {return this->name; }

// type
NATURE_TYPE Pokemon::getType(){return this->type;}
void Pokemon::setType(int type){this->type = (NATURE_TYPE)type;}
std::string Pokemon::getTypeAsString(){
    switch(this->type){
    case 1: return "Normal"; break;
    case 2: return "Fire"; break;
    case 3: return "Water"; break;
    case 4: return "Electric"; break;
    default: return "Grass"; break;
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
std::string Pokemon::getBaseAttackName() {return this->baseAttackName;}

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

    // dont show stats for dead pokemon 
    if (hp <= 0)
        std::cout << "(*FAINTED*) \n\n";
    else {
        std::cout << "\n\t HP: " << hp << std::endl
                  << "\t Type: " << this->getTypeAsString() << std::endl
                  << "\t Rarity: " << this->getRarityAsString() << std::endl
                  << "\t Normal Attack: " << this->baseAttackName << " DMG: " << this->baseAttackDmg << std::endl
                  << "\t Heavy Attack: " << this->heavyAttackName << " DMG: " << this->heavyAttackDmg << std::endl << std::endl;
    }
}

// dialouge once a pokemon evolves
void Pokemon::evolve(){
    // reset the pokemon's exp
    this->pokemonExp = 0;
    std::cout << "Your pokemon has evolved into " << this->name << "!" << std::endl;
    std::cout << "Here are some of " << this->name << "'s stats: " << std::endl;
    // show the stats of the newly evolved pokemon
    this->showStats();
}
