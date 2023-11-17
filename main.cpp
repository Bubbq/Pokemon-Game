#include <iostream>
#include "GameStart.h"

// contains the backend functionality of the game
GameStart g;
// represents a player in the game
Trainer player;

void fight(Pokemon& encounteredPokemon){
    // flag that will continue/end the interaction
    bool defeatOrFlee = false;
    //if odd, player interaction, even, CPU interaction
    int turns = 0;
    // let the player choose their pokemon for battle
    player.switchPokemon();
    // clear UI
    g.clear();


    while(defeatOrFlee == false){
        // user action choice
        int userChoice;
        // choice of the CPU
        int CPUchoice = g.randomNumber(1, 2);

        if(player.getCurrentPokemon()->getHp() > 0){
            std::cout << "What will you attack " << encounteredPokemon.getName() << " with?" << std::endl << std::endl;
            std::cout << "1) Base attack: " << player.getCurrentPokemon()->getBaseAttackName() << " " << player.getCurrentPokemon()->getBaseAttackDmg() << " DMG (Mana cost: 10)" << std::endl;
            std::cout << "2) Heavy attack: " << player.getCurrentPokemon()->getHeavyAttackName() << " " << player.getCurrentPokemon()->getHeavyAttackDmg() << " DMG (Mana cost: 20)" << std::endl << std::endl;
            std::cout << "Other:" << std::endl << std::endl;
        }

        // dont show attack stuff if the current pokemons dead
        else
            std::cout << "What will you do?" << std::endl << std::endl;
            
        std::cout << "3)Consume Mana Pot (+20 Mana)" << std::endl;
        // heals a specific pokemon
        std::cout << "4)Heal Pokemon (+20 Health)" << std::endl;
        // switches the active pokemon of the trainer
        std::cout << "5)Switch Pokemon" << std::endl;
        std::cout << "6) Flee!" << std::endl << std::endl;;

        std::cin >> userChoice;

        // validate user input
        g.choiceCheck(1, userChoice, 6, "Fight");

        // clear UI
        g.clear();

        if(userChoice == 1 || userChoice == 2){
            bool base = (userChoice == 1) ? true : false;
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
}

// interaction to catch a pokemon
void catchPokemonMenu(Pokemon& encounteredPokemon){
    
    // flag indicating wether to stop the catch interaction or not
    bool caught = false;
    
    // user only has 5 tries before the pokemon runs away
    int catchAttempts = 0;
    
    // clear UI
    g.clear();

    while (caught == false){

        std::cout << "Which ball would you like to use?" << std::endl << std::endl;
        std::cout << "1.)Pokeball" << std::endl;
        std::cout << "2.)Great Ball" << std::endl;
        std::cout << "3.)Ultra Ball" << std::endl;

        int userChoice;
        std::cin >> userChoice;

        g.choiceCheck(1, userChoice, 3, "Pokeball");

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
    // make pokemon pointer of encountered 'mon
    Pokemon  encounteredPokemon = g.getCurrentDB()->getCurrentReigon()[g.randomNumber(0, g.getCurrentDB()->getCurrentReigon().size() - 1)];
    // clear UI
    g.clear();

    std::cout << "After roaming for some time in the " << g.getCurrentDB()->getReigonName() << " Region, you've run into " << encounteredPokemon.getName() << "!" << std::endl << std::endl;
    std::cout << "Here are some of " << encounteredPokemon.getName() << "'s Stats:" << std::endl << std::endl;

    // show stats of encountered pokemon
    encounteredPokemon.showStats();

    // user input
    int userChoice;

    std::cout << "What would you like to do?" << std::endl << std::endl;
    std::cout << "1) Catch it" << std::endl;
    std::cout << "2) Fight it" << std::endl;
    std::cout << "3) Flee!" << std::endl;

    std::cin >> userChoice;

    // input validation
    g.choiceCheck(1, userChoice, 3, "Choice");

    g.clear();

    switch(userChoice) {
    case 1: catchPokemonMenu(encounteredPokemon); break;
    case 2: fight(encounteredPokemon); break;
    case 3: player.flee(); break;
    }
}

// to travel to another reigon
void fastTravel(){
    
    // clear screen
    g.clear();
    // user input
    int userChoice;
    // list of pokemon reigon, so user cant join the reigon there already in
    std::string reigons[] = {"Kanto", "Johto", "Honen"};

    // check player level before starting fast travel menu
    if (player.getLevel() < 5) {
        std::cout << "(Fast Travel unlocked at Level 5)" << std::endl << std::endl;
        return;
    }

    std::cout << "CURRENT REGION: *" << g.getCurrentDB()->getReigonName() << "*" << std::endl;
    std::cout << "Which region would you like to Travel to?" << std::endl << std::endl;

    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    std::cin >> userChoice;

    // validate user's choice, cannot be outside range and be the same reigon
    g.choiceCheck(1, userChoice, 3, "Reigon");

    switch (userChoice) {
        case 1: 
            g.clear();
            // update current database
            g.getCurrentDB()->setCurrentReigon("Kanto");
            // dialouge for action
            std::cout << "You have successfully traveled to the Kanto Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
        case 2: 
            g.clear();
            // update current database
            g.getCurrentDB()->setCurrentReigon("Johto");
            // dialouge for action
            std::cout << "You have successfully traveled to the Johto Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
        case 3:
            g.clear(); 
            // update current database
            g.getCurrentDB()->setCurrentReigon("Honen");
            // dialouge for action
            std::cout << "You have successfully traveled to the Honen Region, New adventures and Pokemon await!" << std::endl << std::endl;
            break;
    }

}

// main hub of the game
void menu(){

    // clear terminal screen
    g.clear();
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
        g.choiceCheck(0, userChoice, 4, "Choice");

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
            case 4: std::cout << "Reigon: " << g.getCurrentDB()->getReigonName() << std::endl; player.showStats(1);
        }
    }
}

// players choosing their starting pokemon
void chooseStarter(){

    // clear terminal 
    g.clear();

    std::cout << "Based on the " << g.getCurrentDB()->getReigonName() << " region, you have access to the following starter pokemon:" << std::endl << std::endl;
    
    std::cout << "1) " << g.getCurrentDB()->getCurrentReigon()[0].getName() << std::endl;
    std::cout << "2) " << g.getCurrentDB()->getCurrentReigon()[3].getName() << std::endl;
    std::cout << "3) " << g.getCurrentDB()->getCurrentReigon()[6].getName() << std::endl;

    int userChoice;
    std::cin >> userChoice;

    // validate user's pokemon choice
    g.choiceCheck(1, userChoice, 3, "Pokemon");

    // add pokemon to user's backpack
    switch(userChoice) {
    case 1: player.getBackpack()->addPokemon(g.getCurrentDB()->getCurrentReigon()[0]); break;
    case 2: player.getBackpack()->addPokemon(g.getCurrentDB()->getCurrentReigon()[3]); break;
    case 3: player.getBackpack()->addPokemon(g.getCurrentDB()->getCurrentReigon()[6]); break;

    default: break;
    }

    // send user to menu
    menu();
}

// beginning dialouge for starting the game, where a user chooses his/her reigon
void startGame(){
   
    std::cout << "Hello trainer! Welcome to world of Pokemon, to begin, which region would you like to start in?" << std::endl << std::endl;
    
    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    int userChoice;
    std::cin >> userChoice;
    
    // validate user input
    g.choiceCheck(1, userChoice, 3, "Reigon");


    // set DB based on user choice, this is where user will fight and catch pokemon
    switch (userChoice) {
        case 1: g.getCurrentDB()->setCurrentReigon("Kanto"); break;
        case 2: g.getCurrentDB()->setCurrentReigon("Johto"); break;
        case 3: g.getCurrentDB()->setCurrentReigon("Honen"); break;
        
        default: break;
    }

    // send Trainer to choose starting pokemon
    chooseStarter();
}

int main() {
    // clear UI
    g.clear();
    startGame();
    return 0; 
}
