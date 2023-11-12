#include "GameStart.h"
#include "PokemonDB.h"

// for use of strings
#include <string>
// for cout and cin
#include <iostream>

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

// travel to another reigon
void GameStart::fastTravel(Trainer&){}

// awarding exp for the Trainer
void GameStart::giveExp(Trainer&){}

// where player looks for items (pokeballs, health potions, etc)
void GameStart::forage(Trainer&){}






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
        case 0: std::cout << "Exiting menu!" << std::endl; break;
        case 1: this->forage(player); break;
        // case 2: explore(player); break;
        // case 3: fastTravel(player, kantoDB, johtoDB, honenDB); break;
        // case 4: showStats(player); break;
        }
    }
}

// to validate user choice
void GameStart::choiceCheck(int min, int& userChoice, int max, std::string choice){
     while(userChoice < min || userChoice > max){
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




