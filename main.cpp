#include <iostream>
#include "GameFunction.h"

// contains the backend functionality of the game
GameFunction g;
// represents a player in the game
Trainer player;

void fight(Pokemon& encounteredPokemon){

    // flag that will continue/end the interaction
    bool defeatOrFlee = false;
    //if odd, player interaction, even, CPU interaction
    int turns = 0;
    // let the player choose their pokemon for battle
    player.switchPokemon();
    g.clear();

    while(defeatOrFlee == false){
        
        // choice of the CPU
        int CPUchoice = g.randomNumber(1, 2);

        if(player.getCurrentPokemon()->getHp() > 0){
            std::cout << "What will you attack " << encounteredPokemon.getName() << " with? \n\n";
            std::cout << "1) Base attack: " << player.getCurrentPokemon()->getBaseAttackName() << " " << player.getCurrentPokemon()->getBaseAttackDmg() << " DMG (Mana cost: 5) \n";
            std::cout << "2) Heavy attack: " << player.getCurrentPokemon()->getHeavyAttackName() << " " << player.getCurrentPokemon()->getHeavyAttackDmg() << " DMG (Mana cost: 10) \n\n";
            std::cout << "Other: \n\n";
        }

        // dont show attack stuff if the current pokemons dead
        else
            std::cout << "What will you do? \n\n";
            
        std::cout << "3) Consume Mana Pot (+20 Mana) \n";
        // to heal your current pokemon
        std::cout << "4) Heal Pokemon (+20 Health) \n";
        // switches the active pokemon of the trainer
        std::cout << "5) Switch Pokemon \n";
        std::cout << "6) Flee! \n\n";

        // user action choice
        int userChoice;
        std::cin >> userChoice;
        // validate user input
        player.choiceCheck(1, userChoice, 6, "Fight");

        g.clear();

        if(userChoice == 1 || userChoice == 2){
            bool base = (userChoice == 1) ? true : false;
            // error checking if user is fighting with no mana and/or health
            if(!g.attackWithNoHP(*player.getCurrentPokemon()) && !g.attackWithNoMana(player, base)){
                // user does a base attack
                defeatOrFlee = g.attackSim(*player.getCurrentPokemon(), encounteredPokemon, player, userChoice, ++turns);
                //to make sure the enemy dosen't attack while its dead
                if(defeatOrFlee == false)
                // the CPU attacking you
                defeatOrFlee = g.attackSim(encounteredPokemon, *player.getCurrentPokemon(), player, CPUchoice, ++turns);
            }
        }

        switch(userChoice){
            // to use a mana pot
            case 3: g.clear(); player.useManaPot(); break;
            // to use a health pot
            case 4: g.clear(); player.useHealthPot(g.getCurrentDB()->getCurrentReigon()); break;
            // to fight with a different pokemon
            case 5: g.clear(); player.switchPokemon(); g.clear(); break;
            // to leave a pokemon fighting encounter with punishment
            case 6: player.flee(); defeatOrFlee = true; break;
        }

    }
    // update the health of the pokemon in the player's backpack after the trainer wins or flees the fight
    player.backpack->pokemonCollection[player.pokemonIndex].setHp(player.getCurrentPokemon()->getHp());
}

// interaction to catch a pokemon
void catchPokemonMenu(Pokemon& encounteredPokemon){
    
    // flag indicating wether to stop the catch interaction or not
    bool caught = false;
    
    // user only has 5 tries before the pokemon runs away
    int catchAttempts = 0;
    
    g.clear();

    while (caught == false){

        std::cout << "Which ball would you like to use? \n\n";
        std::cout << "1.) Pokeball \n";
        std::cout << "2.) Great Ball \n";
        std::cout << "3.) Ultra Ball \n";

        // validate user input
        int userChoice;
        std::cin >> userChoice;
        player.choiceCheck(1, userChoice, 3, "Pokeball");

        // cases based on the rarity of the pokemon
        // normal - 50%
        // uncommon - 25%
        // rare - 15%
        // legedary - 10%

        switch (encounteredPokemon.getRarity()) {
            case 1: caught = g.catchSim(player, 50, catchAttempts, userChoice, encounteredPokemon); break;
            case 2: caught = g.catchSim(player, 25, catchAttempts, userChoice, encounteredPokemon); break;
            case 3: caught = g.catchSim(player, 15, catchAttempts, userChoice, encounteredPokemon); break;
            case 4: caught = g.catchSim(player, 10, catchAttempts, userChoice, encounteredPokemon); break;
        }
    }
}

// to explore the world, can fight or catch a randomly encountered pokemon
void explore(){

    // make pokemon variable of encountered 'mon
    Pokemon  encounteredPokemon = g.getCurrentDB()->getCurrentReigon()[g.randomNumber(0, g.getCurrentDB()->getCurrentReigon().size() - 1)];
    g.clear();

    std::cout << "After roaming for some time in the " << g.getCurrentDB()->getReigonName() << " Region, you've run into " << encounteredPokemon.getName() << "! \n\n";
    std::cout << "Here are its stats: \n\n";

    // show stats of encountered pokemon
    encounteredPokemon.showStats();

    std::cout << "What would you like to do? \n\n";
    std::cout << "1) Catch it \n";
    std::cout << "2) Fight it \n";
    std::cout << "3) Go Back \n";
    
    // user input
    int userChoice;
    std::cin >> userChoice;
    // input validation
    player.choiceCheck(1, userChoice, 3, "Choice");
    
    g.clear();

    switch(userChoice) {
        case 1: catchPokemonMenu(encounteredPokemon); break;
        case 2: fight(encounteredPokemon); break;
        case 3: break;
    }
}

// to travel to another reigon
void fastTravel(){
    
    g.clear();
   
    // list of pokemon reigon, so user cant join the reigon there already in
    std::string reigons[] = {"Kanto", "Johto", "Honen"};

    // check player level before starting fast travel menu
    if (player.getLevel() < 5) {
        std::cout << "(Fast Travel unlocked at Level 5) \n\n";
        return;
    }

    std::cout << "CURRENT REGION: *" << g.getCurrentDB()->getReigonName() << "* \n";
    std::cout << "Which region would you like to Travel to? \n\n";
    std::cout << "1) Kanto \n";
    std::cout << "2) Johto \n";
    std::cout << "3) Honen \n";
    
    // user input
    int userChoice;
    std::cin >> userChoice;
    // validate user's choice
    player.choiceCheck(1, userChoice, 3, "Reigon");

    switch (userChoice) {
        case 1: g.getCurrentDB()->setCurrentReigon("Kanto"); break;
        case 2: g.getCurrentDB()->setCurrentReigon("Johto"); break;
        case 3: g.getCurrentDB()->setCurrentReigon("Honen"); break;
    }

    g.clear();
    std::cout << "You have successfully traveled to the " << g.getCurrentDB()->getReigonName() << " Region, New adventures and Pokemon await! \n\n";
}

// main hub of the game
void menu(){

    // clear terminal screen
    g.clear();
    // holding user input
    int userChoice;

    while(userChoice != 0) {

        std::cout << "What would you like to do? \n\n";
        std::cout << "1) Forage \n";
        std::cout << "2) Explore \n";
        std::cout << "3) Fast Travel to another region \n";
        std::cout << "4) View Stats \n\n";
        std::cout << "0) QUIT \n";

        std::cin >> userChoice;
        // valide user choice
        player.choiceCheck(0, userChoice, 4, "Your");

        // clear after choice
        g.clear();

        switch(userChoice) {
            // ending the game
            case 0: std::cout << "Exiting menu!" << std::endl; break;
            // where player get pokeballs and other items
            case 1: g.forageSim(player); break;
            case 2: explore(); break;
            // user can move to a different pokemon reigon
            case 3: fastTravel(); break;
            // shows the stats of the player
            case 4: player.showStats(g.getCurrentDB()->getReigonName());
        }
    }
}

// players choosing their starting pokemon
void chooseStarter(){
    
    // clear terminal 
    g.clear();

    std::cout << "Based on the " << g.getCurrentDB()->getReigonName() << " region, you have access to the following starter pokemon: \n\n";
    // show the 1st 3 starters in the users database
    std::cout << "1) " << g.getCurrentDB()->getCurrentReigon()[0].getName() << std::endl;
    std::cout << "2) " << g.getCurrentDB()->getCurrentReigon()[3].getName() << std::endl;
    std::cout << "3) " << g.getCurrentDB()->getCurrentReigon()[6].getName() << std::endl;

    //user input
    int userChoice;
    std::cin >> userChoice;
    // validate user's pokemon choice
    player.choiceCheck(1, userChoice, 3, "Pokemon");

    // add pokemon to user's backpack
    switch(userChoice) {
        case 1: player.backpack->addPokemon(g.getCurrentDB()->getCurrentReigon()[0]); break;
        case 2: player.backpack->addPokemon(g.getCurrentDB()->getCurrentReigon()[3]); break;
        case 3: player.backpack->addPokemon(g.getCurrentDB()->getCurrentReigon()[6]); break;
    }

    // send user to menu
    menu();
}

// beginning dialouge for starting the game, where a user chooses his/her reigon
void startGame(){
   
    std::cout << "Hello trainer! Welcome to world of Pokemon, to begin, which region would you like to start in? \n\n";
    std::cout << "1) Kanto \n";
    std::cout << "2) Johto \n";
    std::cout << "3) Honen \n";

    int userChoice;
    std::cin >> userChoice;
    
    // validate user input
    player.choiceCheck(1, userChoice, 3, "Reigon");


    // set DB based on user choice, this is where user will fight and catsch pokemon
    switch (userChoice) {
        case 1: g.getCurrentDB()->setCurrentReigon("Kanto"); break;
        case 2: g.getCurrentDB()->setCurrentReigon("Johto"); break;
        case 3: g.getCurrentDB()->setCurrentReigon("Honen"); break; 
    }

    // send Trainer to choose starting pokemon
    chooseStarter();
}

int main() {
    g.clear();
    startGame();
    return 0; 
}
