#include <iostream>
#include <string>
#include <vector>
#include "Backpack.h"
#include "GameStart.h"
#include "Pokemon.h"
#include "PokemonDB.h"
#include "Trainer.h"


// constructor
Trainer::Trainer(){
    
    this->name = "Ash Ketchum";
    this->mana = 100;
    this->exp = 0;
    this->level = 1;
    this->currentPokemon = nullptr;
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
Pokemon * Trainer::getCurrentPokemon(){return this->currentPokemon;}

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

    std::cout << "Which pokemon would you like to fight with?" << std::endl;
    // std::cout << this->currentPokemon->getHp() << "\n";

    // for(int i = 0; i< backpack->getPokemonCollection().size(); i++){
    //     if(backpack->getPokemonCollection()[i].getName() == this->currentPokemon->getName())
    //         backpack->getPokemonCollection()[i].setHp(this->currentPokemon->getHp());
    // }

    // show availible pokemon to the user
    this->backpack->showContent(0);

    // user input
    int choice;
    std::cin >> choice;

    // // validate user input
    // while(choice > this->getBackpack()->getPokemonCollection().size()){
    //     std::cout << "Pokemon choice is invalid, please try again." << std::endl;
    //     std::cin >> choice;
    // }

    // update the users active pokemon to the one they chose
    this->currentPokemon = new Pokemon(this->backpack->getPokemonCollection()[0]);
}

Backpack * Trainer::getBackpack(){return this->backpack;}

// showing trainers stats
void Trainer::showStats(int choice){

    std::cout << "Name: " << this->name << std::endl;
    std:: cout << "Level: " << this->level << std::endl;    
    std::cout << std::endl;

    // output everything the backpack has
    this->backpack->showContent(choice);
}

void Trainer::useManaPot(){
    //  clear();

    // check if the player has max mana
    if(this->mana == 100)
        std::cout << "You already have max mana!" << std::endl;

    // check if the player has no mana pots
    else if(this->getBackpack()->getManaPot() == 0)
        std::cout << "You don't have enough Mana pots !" << std::endl;

    // update the mana and decrement the mana pot
    else{
        int oldMana = this->mana;
        // increment mana
        this->mana += 20;
        // decrement manaPot count
        this->backpack->setManaPot(this->backpack->getManaPot() - 1);

        // bound mana if above threshold
        if(this->mana > 100)
            this->mana = 100;

        std::cout << "Using Mana Pot, you've gained " << (this->mana - oldMana) << " mana!" << std::endl;
        std::cout << "You now have " << this->mana << " Mana and " << this->backpack->getManaPot() << " pots left" << std::endl;
    }
    return;
}

// to use health pot, healing a pokemon
void Trainer::useHealthPot(std::vector<Pokemon> DB){

    int pokemonHealth = this->currentPokemon->getHp();
    std::string pokemonName = this->currentPokemon->getName();

    // check if the user has enough healthpots
    if(this->backpack->getHealthPot() == 0){
        std::cout << "You don't have enough health pots to heal" << this->currentPokemon->getName() << "!" << std::endl;
        return;
    }

    // heal the currentPokemon
    // check if the pokemon has more than its normal health
    for(int i = 0; i < DB.size(); i++){
        if(pokemonName == DB[i].getName()){
            // check if the poke is already at max health
            if(pokemonHealth == DB[i].getHp()){
                std::cout << pokemonName << " already has max health!" << std::endl << std::endl;
                return;
            }
            // actually add the health and decrement a mana pot
            else {
                this->currentPokemon->setHp(pokemonHealth + 20);
                this->backpack->setHealthPot(this->backpack->getHealthPot() - 1);
                // special case: pokemon health went over its bounded maximum
                if(currentPokemon->getHp() > DB[i].getHp())
                    this->currentPokemon->setHp(DB[i].getHp());
                    
                std::cout << this->currentPokemon->getName() << " now has " << this->currentPokemon->getHp() << " health!" << std::endl << std::endl;
            }
        }
    }
    return;
}

// to run away from a pokemon fighting encounter, will lose random item in a random amout
void Trainer::flee(){

    GameStart g;

    // will be used to randomly lose a type of item
    int arr[] = {this->backpack->getPokeBalls(),this->backpack->getGreatBalls(), this->backpack->getUltraBalls(), this->backpack->getHealthPot(), this->backpack->getManaPot()};

    int randomItem = g.randomNumber(0, 4);

    // check if the trainer has the item to lose
    if (arr[randomItem] != 0) {
        int amount = arr[randomItem];
        // the amount of a certian item a trainer will lose when running away
        int amountLost = g.randomNumber(1, 5);
        std::string itemLost;
        
        // update the item
        amount -= amountLost;

        // error check: item count cannot be negative
        if(amount < 0)
            amount = 0;

        // update the backpack of the user based off of the item lost
        switch (randomItem) {
            case 0: this->backpack->setPokeBalls(amount); itemLost = "Pokeball"; break;
            case 1: this->backpack->setGreatBalls(amount); itemLost = "Great Ball"; break;
            case 2: this->backpack->setUltraBalls(amount); itemLost = "Ultra Ball"; break;
            case 3: this->backpack->setHealthPot(amount); itemLost = "Health Pot"; break;
            case 4: this->backpack->setManaPot(amount); itemLost = "Mana Pot"; break;
        }

        // clear UI
        g.clear();

        std::cout << "You ran away, but while escaping you lost " << amountLost << " " << itemLost;
        
        // add plural
        if(amountLost > 1)
            std::cout << "s";
        
        std::cout << "\n\n";
    }

    // when the user already dosent have any of the item chose to be lost
    else {
        // clear UI
        g.clear();
        std::cout << "You begin to question your skills as a trainer, nonetheless, you successfully ran away" << std::endl;
        std::cout << "Lost 10 XP" << std::endl << std::endl;
        this->exp -= 10;
    }
}




