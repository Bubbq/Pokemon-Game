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

// Setters and getters

// the currentDB
void GameStart::setCurrentDB(std::string pokemonReigon){this->pokemonDB->setCurrentReigon(pokemonReigon);}
std::vector<Pokemon> GameStart::getCurrentDB(){return this->pokemonDB->getCurrentReigon();}

// Other Functionality

// awarding exp for the Trainer for catches and fight victories
void GameStart::giveExp(Trainer&){}

// main hub of the game
void GameStart::menu(Trainer& player){

    // clear terminal screen
    clear();
    // holding user input
    int userChoice;

    while(userChoice != 0) {

        std::cout << "What would you like to do?" << std::endl << std::endl;

        std::cout << "1) Forage" << std::endl;
        std::cout << "2) Explore" << std::endl;
        std::cout << "3) Fast Travel to another region" << std::endl;
        std::cout << "4) View Stats" << std::endl;
        std::cout << std::endl << "0) QUIT" << std::endl;

        std::cin >> userChoice;

        // valide user choice
        this->choiceCheck(0, userChoice, 4, "Choice");

        // clear after choice
        clear();

        switch(userChoice) {
        // ending the game, DONE
        case 0: std::cout << "Exiting menu!" << std::endl; break;
        // where player get pokeballs and other items, DONE
        case 1: this->forage(player); break;
        case 2: this->explore(player); break;
        // user can move to a different pokemon reigon, DONE
        case 3: this->fastTravel(player); break;
        
        // shows the stats of the player, DONE
        case 4: std::cout << "Reigon: " << this->pokemonDB->getReigonName() << std::endl; player.showStats();
        }
    }
}

void GameStart::catchPokemonMenu(Trainer& player, Pokemon& encounteredPokemon){
    
    // flag indicating wether to stop the catch interaction or not
    bool caught = false;
    
    // user only has 5 tries before the pokemon runs away
    int catchAttempts = 0;
    
    // clear UI
    clear();

    while (caught == false){

        std::cout << "Which ball would you like to use?" << std::endl << std::endl;
        std::cout << "1.)Pokeball" << std::endl;
        std::cout << "2.)Great Ball" << std::endl;
        std::cout << "3.)Ultra Ball" << std::endl;

        int userChoice;
        std::cin >> userChoice;

        this->choiceCheck(1, userChoice, 3, "Pokeball");

        // cases based on the rarity of the pokemon
        // normal - 50
        // uncommon - 25
        // rare - 15
        // legedary - 10
        switch (encounteredPokemon.getRarity()) {
        case 1: caught = catchSim(player, 50, catchAttempts, userChoice, encounteredPokemon); break;
        case 2: caught = catchSim(player, 25, catchAttempts, userChoice, encounteredPokemon); break;
        case 3: caught = catchSim(player, 15, catchAttempts, userChoice, encounteredPokemon); break;
        case 4: caught = catchSim(player, 10, catchAttempts, userChoice, encounteredPokemon); break;
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


void GameStart::explore(Trainer&player){

    // randomly generate a number for pokemon encounter
    std::srand(static_cast<unsigned int>(time(nullptr)));

    int randomNumber = (std::rand() % (this->pokemonDB->getCurrentReigon().size()));
    // make pokemon pointer of encountered 'mon
    Pokemon  encounteredPokemon = this->pokemonDB->getCurrentReigon()[randomNumber];

    // clear UI
    clear();

    std::cout << "After roaming for some time in the " << this->pokemonDB->getReigonName() << " Region, you've run into " << encounteredPokemon.getName() << "!" << std::endl << std::endl;

    std::cout << "Here are some of " << encounteredPokemon.getName() << "'s Stats:" << std::endl << std::endl;

    encounteredPokemon.showStats();

    // user input
    int userChoice;

    std::cout << "What would you like to do?" << std::endl << std::endl;
    std::cout << "1) Catch it" << std::endl;
    std::cout << "2) Fight it" << std::endl;
    std::cout << "3) Flee!" << std::endl;

    std::cin >> userChoice;

    // input validation
    choiceCheck(1, userChoice, 3, "Choice");

    clear();

    switch(userChoice) {
    case 1: this->catchPokemonMenu(player, encounteredPokemon); break;
    // case 2: fight(player, randomNumber); break;
    // case 3: flee(player); break;
    }
}

// travel to another reigon
void GameStart::fastTravel(Trainer& player){
    
    // clear screen
    clear();
    // user input
    int userChoice;
    // list of pokemon reigon, so user cant join the reigon there already in
    std::string reigons[] = {"Kanto", "Johto", "Honen"};

    // check player level before starting fast travel menu
    if (player.getLevel() < 5) {
        std::cout << "(Fast Travel unlocked at Level 5)" << std::endl << std::endl;
        return;
    }

    std::cout << "CURRENT REGION: *" << this->pokemonDB->getReigonName() << "*" << std::endl;
    std::cout << "Which region would you like to Travel to?" << std::endl << std::endl;

    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    std::cin >> userChoice;

    // validate user's choice, cannot be outside range and be the same reigon
    while((userChoice < 1 || userChoice > 3) || (reigons[userChoice - 1] == this->pokemonDB->getReigonName())){
        std::cout << "Region choice is invalid or you are already at the location, please try again" << std::endl;
        std::cin >> userChoice;
    }

    switch (userChoice) {
        case 1: 
            clear();
            // update current database
            this->pokemonDB->setCurrentReigon("Kanto");
            // dialouge for action
            std::cout << "You have successfully traveled to the Kanto Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
        case 2: 
            clear();
            // update current database
            this->pokemonDB->setCurrentReigon("Johto");
            // dialouge for action
            std::cout << "You have successfully traveled to the Johto Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
        case 3:
            clear(); 
            // update current database
            this->pokemonDB->setCurrentReigon("Honen");
            // dialouge for action
            std::cout << "You have successfully traveled to the Honen Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
    }

}

// where player looks for items (pokeballs, health potions, etc)
// uses a random number for the chance a user gets an item
// 40% 4 poke ball, 20% 4 great 10% 4 ultra 15% 4 mana and health pots, DONE
void GameStart::forage(Trainer& player){

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

// beginning dialouge of the game, users chooses thier reigon
// are able to fast travel at level 5, DONE
void GameStart::startGame(Trainer& player){
   
    std::cout << "Hello trainer! Welcome to world of Pokemon, to begin, which region would you like to start in?" << std::endl << std::endl;
    
    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    int userChoice;
    std::cin >> userChoice;
    
    // validate user input
    this->choiceCheck(1, userChoice, 3, "Reigon");


    // set DB based on user choice, this is where user will fight and catch pokemon
    switch (userChoice) {
        case 1: this->pokemonDB->setCurrentReigon("Kanto"); break;
        case 2: this->pokemonDB->setCurrentReigon("Johto"); break;
        case 3 :this->pokemonDB->setCurrentReigon("Honen"); break;
        
        default: break;
    }

    // send Trainer to choose starting pokemon
    this->chooseStarter(player);
}

// players choosing their starting pokemon, DONE
void GameStart::chooseStarter(Trainer& player){

    // clear terminal 
    this->clear();

    std::cout << "Based on the " << this->pokemonDB->getReigonName() << " region, you have access to the following starter pokemon:" << std::endl << std::endl;
    
    std::cout << "1) " << this->pokemonDB->getCurrentReigon()[0].getName() << std::endl;
    std::cout << "2) " << this->pokemonDB->getCurrentReigon()[3].getName() << std::endl;
    std::cout << "3) " << this->pokemonDB->getCurrentReigon()[6].getName() << std::endl;

    int userChoice;
    std::cin >> userChoice;

    // validate user's pokemon choice
    this->choiceCheck(1, userChoice, 3, "Pokemon");

    // add pokemon to user's backpack
    switch(userChoice) {
    case 1: player.getBackpack()->addPokemon(this->pokemonDB->getCurrentReigon()[0]); break;
    case 2: player.getBackpack()->addPokemon(this->pokemonDB->getCurrentReigon()[3]); break;
    case 3: player.getBackpack()->addPokemon(this->pokemonDB->getCurrentReigon()[6]); break;

    default: break;
    }

    // send user to menu
    this->menu(player);
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





