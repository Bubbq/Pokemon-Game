#include "GameStart.h"
#include "Pokemon.h"
#include "PokemonDB.h"

// for use of strings
#include <string>

// for cout and cin
#include <iostream>

// for std::numeric_limits, helps choiceCheck function
// for out of bound ints and invalid types
#include <limits> 


// constructor
GameStart::GameStart(){
    this->pokemonDB = new PokemonDB(this->honenFilename, this->kantoFilename, this->johtoFilename);
}

// destructor
GameStart::~GameStart(){}   

// the currentDB
void GameStart::setCurrentDB(std::string pokemonReigon){this->pokemonDB->setCurrentReigon(pokemonReigon);}
PokemonDB * GameStart::getCurrentDB(){return this->pokemonDB;}

// Other Functionality

// awarding exp for the Trainer and pokemon for fight victories
void GameStart::giveExp(Trainer& player, int exp){
    // giving the player and pokemon exp
    player.setExp(player.getExp() + exp);
    player.getCurrentPokemon()->setPokemonExp(player.getCurrentPokemon()->getPokemonExp() + exp);

    // checking if the player has leveled up
    // will level up after every 500 exp
    if(player.getExp() >= 500){
        //reset it back to 0
        player.setExp(0);
        // update players level
        player.setLevel(player.getLevel() + 1);
        // give dialouge
        std::cout << std::endl <<  "Congrats, you leveled up!" << std::endl;
        std::cout << "You're now level " << player.getLevel() << "\n\n";
    }

    // representing the players 'old' pokemon if they are able to evolve
    Pokemon oldPokemon = *player.getCurrentPokemon();

    // for checking if the currentPokemon has leveled up
    for(int i = 0; i < this->pokemonDB->getCurrentReigon().size(); i++){
        if(oldPokemon.getName() == this->pokemonDB->getCurrentReigon()[i].getName()){
            if(oldPokemon.getPokemonExp() >= 1000 && oldPokemon.getEvoStage() < 3){
                // update the old pokemon with the next pokemon in the database
                oldPokemon = this->pokemonDB->getCurrentReigon()[i+1];
                // update the players currentPokemon with the new one
                player.setCurrentPokemon(&oldPokemon);
                // dialouge of pokemon evolution
                player.getCurrentPokemon()->evolve();
            } 
        }
    }
}

// simulating the catch of the pokemon
bool GameStart::catchSim(Trainer& player, int successRate, int& catchAttempts, int ballChoice, Pokemon& encounteredPokemon){
    
    // clear UI
    clear();
 
    switch (ballChoice) {
        case 1: 
            player.getBackpack()->setPokeBalls(player.getBackpack()->getPokeBalls() - 1); 
            if(player.getBackpack()->getPokeBalls() <= 0){
                std::cout << "You don't have enough balls to catch " << encounteredPokemon.getName() << "!" << std::endl;
                return false;
            }
            break;
        case 2: 
            player.getBackpack()->setGreatBalls(player.getBackpack()->getGreatBalls() - 1); 
            successRate += 10; 
            if(player.getBackpack()->getGreatBalls() <= 0){
                std::cout << "You don't have enough balls to catch " << encounteredPokemon.getName() << "!" << std::endl;
                return false;
            }
            break;
        case 3: 
            player.getBackpack()->setUltraBalls(player.getBackpack()->getUltraBalls() - 1); 
            successRate += 15; 
            if(player.getBackpack()->getUltraBalls() <= 0){
                std::cout << "You don't have enough balls to catch " << encounteredPokemon.getName() << "!" << std::endl;
                return false;
            }
            break;
    }

    // range of random numbers to determine if the pokemon has been caught or not
    const int min = 1;
    const int max = 100;
    
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int randomNumber = min + (std::rand() % (max - min + 1));

    if (randomNumber <= successRate) {
        std::cout << "Wow! You've caught " << encounteredPokemon.getName() << std::endl;
        // add the pokemon to the users backpack
        player.getBackpack()->addPokemon(encounteredPokemon);
        // award exp to the user
        // giveXP(player, player.currDB[randomPokemonIndex], 1);
        return true;
    }

    // user only has 5 tries before the pokemon runs away
    if (catchAttempts == 5) {
        std::cout << encounteredPokemon.getName() << " ran away! :(" << std::endl << std::endl;
        return true;
    }

    // didnt catch the pokemon
    std::cout << encounteredPokemon.getName() << " broke free!" << std::endl << std::endl;
    catchAttempts++;  
    return false;
}

// where player looks for items (pokeballs, health potions, etc)
// 40% 4 poke ball, 20% 4 great 10% 4 ultra 15% 4 mana and health pots, DONE
void GameStart::forageSim(Trainer &player){

    // get random number from 1 - 100 inclusive
    std::srand(static_cast<unsigned int>(time(nullptr)));
    int randomNumber = 1 + (std::rand() % (100 - 1 + 1));

    if(randomNumber <= 40){
        // upd8 user's backpack
        player.getBackpack()->setPokeBalls(player.getBackpack()->getPokeBalls() + 3);
        // dialouge for action
        this->forageDialouge(3, "pokeballs");
    }

    else if(randomNumber > 40 && randomNumber <= 60){
       player.getBackpack()->setGreatBalls(player.getBackpack()->getGreatBalls() + 2);
       this->forageDialouge(2, "greatballs");
    }

    else if(randomNumber > 60 && randomNumber <= 70){
        player.getBackpack()->setUltraBalls(player.getBackpack()->getUltraBalls() + 2);
        this->forageDialouge(2, "ultraballs");
    }

    else if(randomNumber > 70 && randomNumber <= 85){
        player.getBackpack()->setHealthPot(player.getBackpack()->getHealthPot() + 1);
        this->forageDialouge(1, "health pot");
    }

    else{
       player.getBackpack()->setManaPot(player.getBackpack()->getManaPot() + 1);
       this->forageDialouge(1, "mana pot");
    }

}

// dialouge for finding stuff while foraging
void GameStart::forageDialouge(int itemCount, std::string itemName){
    std::cout << "Exploring got you " << itemCount << " " << itemName << ", lucky!" << std::endl;
    std::cout << std::endl;
}

// to validate user choice
void GameStart::choiceCheck(int min, int& userChoice, int max, std::string choice){
     while (std::cin.fail() || userChoice < min || userChoice > max) {
        // clear the fail state
        std::cin.clear(); 
        // discard invalid input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << choice << " choice is invalid, please try again" << std::endl;
        std::cin >> userChoice;
    }
}

// to clear terminal based on OS
void GameStart::clear() {
    #if defined _WIN32
        system("cls");
    #elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
    #elif defined(__APPLE__)
        system("clear");
    #endif
}

// generates a random number between a min and max
int GameStart::randomNumber(int min, int max){
     // randomly generate a number for pokemon encounter
    std::srand(static_cast<unsigned int>(time(nullptr)));

    return min + (std::rand() % (max - min + 1));
}

// simulating the attacking interation 
bool GameStart::attackSim(Pokemon& attacker, Pokemon& victim, Trainer& player, int attackType, int& turns){
      
    int manaCost = (attackType == 1) ? 10 : 20;
    player.setMana(player.getMana() - manaCost);

    // the multiplier of the attacking pokemons damage based its and the victims types
    double effectiveness = 1.0;

    switch (attacker.getType()) {
        // strong to grass, weak to water
        case FIRE:
            if (victim.getType() == GRASS) 
                effectiveness = 2.0;
            if (victim.getType() == WATER)
                effectiveness = 0.5;
            //update the dialoge
            break;

        // strong to water, weak to fire 
        case GRASS:
            if (victim.getType() == FIRE) 
                effectiveness = 0.5;
            if (victim.getType() == WATER) 
                effectiveness = 2.0;           
            break;

        // strong to fire, weak to grass and electric
        case WATER:
            if (victim.getType() == GRASS || victim.getType() == ELECTRIC) 
                effectiveness = 0.5; 
            if (victim.getType() == FIRE) 
                effectiveness = 2.0;           
            break;

        // strong to water, weak to nothing... kinda broken tbh
        case ELECTRIC:
            if (victim.getType() == WATER) 
                effectiveness = 2.0;
            break;
    }
    
    // basing the damage off the integer passed and type effectiveness
    double damage = (attackType == 1) ? (attacker.getBaseAttackDmg() * effectiveness): (attacker.getHeavyAttackDmg() * effectiveness);
    // decrement the victims health
    victim.setHp(victim.getHp() - damage);

    // the dialouge of the effectivness of the attack
    std::string effective;

        if (effectiveness == 0.5 || effectiveness == 1) 
            effective = "Its not very effective";
        else if (effectiveness == 2.0) 
            effective = "Its super effective!";
        else
        effective = "";

    // the dialouge of the attacking dialouge
    return this->attackDialouge(player, attacker, victim, attackType, turns, effective, damage);
    
}

// dialouge of the fight interaction
bool GameStart::attackDialouge(Trainer& player, Pokemon& attacker, Pokemon& victim, int heavyOrBase, int& turns, std::string effectiveness, double damage){

    std::string attackName = (heavyOrBase == 1) ? attacker.getBaseAttackName() : attacker.getHeavyAttackName();
    // the credit given to the attacker, based on the turns
    std::string credit = (turns % 2 == 0) ? "The enemy " : "Your ";

    std::cout << credit << attacker.getName() << " used " << attackName << std::endl;
    // saying how effective the attack was
    std::cout << effectiveness << std::endl;
    std::cout << victim.getName() << " took " << damage << " damage and has ";

    // finish the rest of dialouge by looking at the victims health

    // if the pokemon's dead
     if(victim.getHp() <= 0){
        // set to 0 for simplicity
        victim.setHp(0);
        std::cout << "no health left!" << std::endl << std::endl;
        // now the pokemon's dead, check if the player defeated it and give them XP
        if(turns % 2 != 0){
            std::cout << "The enemy " << victim.getName() << " has been defeated!" << std::endl;
            // generate random xp number from 1-100
            int exp = this->randomNumber(1, 100);
            std::cout << "Defeating " << victim.getName() << " gave you and " << attacker.getName() << " " << exp << "XP!" << std::endl; 
            // award exp to the user
            this->giveExp(player, exp);
            return true;
        }
        
        // when your pokemon has been defeated
        else{
            std::cout << "Your " << victim.getName() << " has been defeated!" << std::endl;
            return false;
        }
    }

    // the victim has not died
    else{
        std::cout << victim.getHp() << " health left!" << std::endl << std::endl;
        return false;
    }
}


// error handling if user is trying to fight w no HP
bool GameStart::attackWithNoHP(Pokemon pokemon){  
    if(pokemon.getHp() <= 0){
        std::cout << pokemon.getName() << " has no health!" << std::endl << std::endl;
        return true;
    }
    
    return false;
}
    
// error handiling if user is fighting with no mana
bool GameStart::attackWithNoMana(Trainer& player, bool base){
    int manaThreshold = (base == true) ? 10 : 20; 
    if(player.getMana() < manaThreshold){
        std::cout << "your dont have a enough mana for " << player.getCurrentPokemon()->getName() << " to fight!\n\n";
        return true;
    }
    return false;
}



