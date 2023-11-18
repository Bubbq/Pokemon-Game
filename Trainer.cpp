#include <iostream>
#include <limits>
#include "GameFunction.h"

// constructor
Trainer::Trainer(){
    this->name = "Ash Ketchum";
    this->level = 1;
    this->mana = 100;
    this->exp = 0;
    this->pokemonIndex = 0;
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

// exp
void Trainer::setExp(int exp){this->exp = exp;}
int Trainer::getExp(){return this->exp;}

// level
void Trainer::setLevel(int level){this->level = level;}
int Trainer::getLevel(){return this->level;}

// Other Functionality

// dialouge to switch a players pokemon
void Trainer::switchPokemon(){

    std::cout << "Which pokemon would you like to fight with?\n\n";
   
    // update the pokemon in the trainer's backpack to the health of the current pokemon
    if(this->currentPokemon != nullptr)
        this->backpack->pokemonCollection[this->pokemonIndex].setHp(this->currentPokemon->getHp());

    // show availible pokemon to the user
    this->backpack->showContent(false);

    // user input
    int choice;
    std::cin >> choice;

    // validate user input
    this->choiceCheck(1, choice, this->backpack->pokemonCollection.size(), "Pokemon");

    // update the users active pokemon to the one they chose
    this->pokemonIndex = --choice;
    this->currentPokemon = new Pokemon(this->backpack->getPokemonCollection()[pokemonIndex]);

}

// showing trainers stats
void Trainer::showStats(std::string reigonName){
    std::cout << "PLAYER \n";
    std::cout << "\t Reigon: " << reigonName << std::endl;
    std::cout << "\t Name: " << this->name << std::endl;
    std:: cout << "\t Level: " << this->level << std::endl << std::endl;;    
    // output everything the backpack has
    this->backpack->showContent(true);
}

// to use a mana pot
void Trainer::useManaPot(){

    // check if the player has max mana
    if(this->mana == 100)
        std::cout << "You already have max mana!" << std::endl;

    // check if the player has no mana pots
    else if(this->backpack->getManaPot() == 0)
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

        std::cout << "Using a mana pot, you've gained " << (this->mana - oldMana) << " mana!\n";
        std::cout << "You now have " << this->mana << " mana and " << this->backpack->getManaPot() << " pots left\n";
    }
}

// to use health pot, healing a pokemon
void Trainer::useHealthPot(std::vector<Pokemon> DB){

    int pokemonHealth = this->currentPokemon->getHp();
    std::string pokemonName = this->currentPokemon->getName();

    // check if the user has enough healthpots
    if(this->backpack->getHealthPot() == 0){
        std::cout << "You don't have enough health pots to heal" << pokemonName << "!" << std::endl;
        return;
    }

    // heal the currentPokemon
    for(int i = 0; i < DB.size(); i++){
    // check if the pokemon has more than its normal health
        if(pokemonName == DB[i].getName()){
            // check if the poke is already at max health
            if(pokemonHealth == DB[i].getHp()){
                std::cout << pokemonName << " already has max health! \n\n";
                return;
            }
            // actually add the health and decrement a mana pot
            else {
                this->currentPokemon->setHp(pokemonHealth + 20);
                this->backpack->setHealthPot(this->backpack->getHealthPot() - 1);
                // special case: pokemon health went over its bounded maximum
                if(currentPokemon->getHp() > DB[i].getHp())
                    this->currentPokemon->setHp(DB[i].getHp());
                    
                std::cout << this->currentPokemon->getName() << " now has " << this->currentPokemon->getHp() << " health! \n";
                std::cout << "You now have " << this->backpack->getHealthPot() << " health pots left! \n\n";
            }
        }
    }
    return;
}

// to run away from a pokemon fighting encounter, will lose random item in a random amout
void Trainer::flee(){

    GameFunction g;

    // will be used to randomly lose a type of item
    int arr[] = {this->backpack->getPokeBalls(),this->backpack->getGreatBalls(), this->backpack->getUltraBalls(), this->backpack->getHealthPot(), this->backpack->getManaPot()};

    // one of the 5 quantifiable items will be lost
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
        // user will lose a random amount of exp
        int exp = g.randomNumber(1, 100);
        std::cout << "Lost " << exp << " XP" << std::endl << std::endl;
        this->exp -= exp;
    }
}

// to validate user choice
void Trainer::choiceCheck(int min, int& userChoice, int max, std::string choice){
     while (std::cin.fail() || userChoice < min || userChoice > max) {
        // clear the fail state
        std::cin.clear(); 
        // discard invalid input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << choice << " choice is invalid, please try again" << std::endl;
        std::cin >> userChoice;
    }
}



