#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include<random>

#include "pokemon.h"
#include "pokedex.h"

void clear() {//clear terminal based on OS
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

void printPokemon(std::vector<Pokemon> vec) {

    int pokemonNumber = 0;

    for (auto x:vec){

        std::cout << ++pokemonNumber <<".)";
        x.printPokemon();
        std::cout << std::endl;

    }
}

struct Trainer{//this is the content of the current player, the linked list of pokemon (his/her pokemonCollection), their lvl, and some forageable items (pokeBalls, health and mana pots).

    std::vector<Pokemon> pokemonCollection;
    int trainerLvl = 5; //for testing features
    int xp = 0;//every 100 xp, the trainer gets a new level, max level is 10
    int mana = 100;//energy used every time a trainers pokemon attacks
    // int trainerLvl = 1;

    int pokeBalls = 10;
    int greatBalls = 5;
    int ultraBalls = 2;

    int manaPot = 5;
    int healthPot = 5;

    std::string currRegion;
    std::vector<Pokemon> currDB;
    std::vector<Pokemon> kantoDB;
    std::vector<Pokemon> johtoDB;
    std::vector<Pokemon> honenDB;
    Pokemon * activePokemon;

};

void showStats(Trainer &player) {//show stats for debugging

    std::cout << "Level: " << player.trainerLvl << std::endl;
    std::cout << "XP: " << player.xp << std::endl;
    std::cout << "Region: " << player.currRegion << std::endl;

    std::cout << "Pokeballs: " << std::endl;
    std::cout << "\t Normal: " << player.pokeBalls << std::endl;
    std::cout << "\t Great: " << player.greatBalls << std::endl;
    std::cout << "\t Ultra: " << player.ultraBalls << std::endl;

    std::cout << "Recovery: " << std::endl;
    std::cout << "\t Health Pots: " << player.healthPot << std::endl;
    std::cout << "\t Mana Pots: " << player.manaPot << std::endl;
    std::cout << std::endl;

    // std::cout << "TEAM:" << std::endl;
    std::cout << "Pokemon: " << std::endl;
    printPokemon(player.pokemonCollection);
    // player.pokemonCollection.printCurrPokemon();
}

bool findPokemonDB(Trainer &player, std::vector<Pokemon>DB){//finds the database the evolved pokemon is in

    for(int i = 0; i < DB.size(); i++){
        if(player.activePokemon->Getname() == player.currDB[i].Getname()){//if the name of the pokemon mathces, return true
            return true;
        }
    }
    return false;
}

int findPokemonIndex(Trainer &player, std::vector<Pokemon>DB){ //finds pokemon in its region locked database

    for(int i = 0; i < DB.size(); i++){
        if(player.activePokemon->Getname() == DB[i].Getname()){//if your active pokemon matches with the same pokemon thats in your collection, return that index
            return i;
        }
    }
    return -1;
}

void giveXP(Trainer &player, Pokemon &caughtOrKilled, int choice){//rewards xp to the trainer based on the rarity of pokemon that they've defeated in battle or caught

    if(choice == 1){//you caught a pokemon, so only the player gets xp

        switch (caughtOrKilled.getRarity()){

        case 1: std::cout << "You Earned 10XP" << std::endl << std::endl; player.xp += 10; break;
        case 2: std::cout << "You Earned 20XP" << std::endl << std::endl; player.xp += 20; break;
        case 3: std::cout << "You Earned 30XP" << std::endl << std::endl; player.xp += 30; break;
        case 4: std::cout << "You Earned 40XP" << std::endl << std::endl; player.xp += 40; break;

        }

    }
    if(choice == 2){

        switch (caughtOrKilled.getRarity()){//you defeated a pokemon, so you and the pokemon you fought with get xp

        case 1: std::cout << "Earned 10XP" << std::endl; player.xp += 10; std::cout << player.activePokemon->Getname() << " earned 5XP" << std::endl << std::endl; player.activePokemon->SetPokemonXp(player.activePokemon->GetPokemonXp() + 5); break;
        case 2: std::cout << "Earned 20XP" << std::endl; player.xp += 20; std::cout << player.activePokemon->Getname() << " earned 10XP" << std::endl << std::endl; player.activePokemon->SetPokemonXp(player.activePokemon->GetPokemonXp() + 10); break;
        case 3: std::cout << "Earned 30XP" << std::endl; player.xp += 30; std::cout << player.activePokemon->Getname() << " earned 15XP" << std::endl << std::endl; player.activePokemon->SetPokemonXp(player.activePokemon->GetPokemonXp() + 15); break;
        case 4: std::cout << "Earned 40XP" << std::endl; player.xp += 40; std::cout << player.activePokemon->Getname() << " earned 20XP" << std::endl << std::endl; player.activePokemon->SetPokemonXp(player.activePokemon->GetPokemonXp() + 20); break;

        }

    }


    if(player.xp > 100){//checks if the player has lvled up!

        player.xp = 0;//sets xp back for trainer to earn again
        std::cout << "Congrats! You've leveled up!" << std::endl;
        player.trainerLvl += 1;
        std::cout << "You are now level " << player.trainerLvl << std::endl;

    }

    if(player.activePokemon->GetPokemonXp() > 10 && player.activePokemon->GetevoStage() < 3){//checks if the pokemon evolved, cant evolve if its already a tier 3 pokemon (ex charizard)

        std::cout << player.activePokemon->Getname() << " has evolved ";
        player.activePokemon->SetPokemonXp(0);//sets active pokemon and matching pokemon in trainers collection back to 0, until they earn it to evolve further
        player.pokemonCollection[findPokemonIndex(player, player.pokemonCollection)].SetPokemonXp(0);

        if(findPokemonDB(player, player.kantoDB) == true){

            std::cout << "into " << player.kantoDB[findPokemonIndex(player, player.kantoDB) + 1].Getname() << "!" << std::endl;

            player.pokemonCollection[findPokemonIndex(player, player.pokemonCollection)] = player.kantoDB[findPokemonIndex(player, player.kantoDB) + 1];//sets the pokemon in the users collection to the pokemon under it (in terms of file positioning)
            player.activePokemon = &player.kantoDB[findPokemonIndex(player, player.kantoDB)];//sets active pokemon to the new evolved pokemon aswell
            std::cout << "Here are some of " << player.activePokemon->Getname() << "'s stats:" << std::endl << std::endl;
            player.activePokemon->printPokemon();

            return;
        }

        if(findPokemonDB(player, player.johtoDB) == true){

            std::cout << "into " << player.johtoDB[findPokemonIndex(player, player.johtoDB) + 1].Getname() << "!" << std::endl;

            player.pokemonCollection[findPokemonIndex(player, player.pokemonCollection)] = player.johtoDB[findPokemonIndex(player, player.johtoDB) + 1];//sets the pokemon in the users collection to the pokemon under it (in terms of file positioning)
            player.activePokemon = &player.johtoDB[findPokemonIndex(player, player.johtoDB)];//sets active pokemon to the new evolved pokemon aswell
            std::cout << "Here are some of " << player.activePokemon->Getname() << "'s stats:" << std::endl << std::endl;
            player.activePokemon->printPokemon();

            return;
        }

        if(findPokemonDB(player, player.honenDB) == true){

            std::cout << "into " << player.honenDB[findPokemonIndex(player, player.honenDB) + 1].Getname() << "!" << std::endl;

            player.pokemonCollection[findPokemonIndex(player, player.pokemonCollection)] = player.honenDB[findPokemonIndex(player, player.honenDB) + 1];//sets the pokemon in the users collection to the pokemon under it (in terms of file positioning)
            player.activePokemon = &player.honenDB[findPokemonIndex(player, player.honenDB)];//sets active pokemon to the new evolved pokemon aswell
            std::cout << "Here are some of " << player.activePokemon->Getname() << "'s stats:" << std::endl << std::endl;
            player.activePokemon->printPokemon();

            return;
        }

    }


}

int getNumberOfLines(std::string filename) {//gets the number of records each region's pokemon has in each file

    std::ifstream f(filename);
    std::string line;
    int count = 0;

    while(getline(f, line)) {
        count++;
    }
    return count;
}

void readPokemonData(std::string filename, int size, std::vector<Pokemon> &vec) {//reads all the info of pokemon in a region

    std::ifstream f(filename);
    int counter = 0;

    int n;
    int check;
    std::string w;
    while (counter < size) {
        f >> w; vec[counter].Setname(w);
        f >> n; vec[counter].SetevoStage(n);
        f >> n; vec[counter].SetPokemonXp(n);
        f >> n; vec[counter].Sethp(n);

        // check for underscore in base attack
        f >> w;
        check = w.find('_');
        if (check != std::string::npos) {
            w[check] = ' ';
            vec[counter].Setbase_attack_name(w);
        }
        else {
            vec[counter].Setbase_attack_name(w);
        }

        f >> n; vec[counter].Setbase_attack_dmg(n);

        // check for underscore in heavy attack
        f >> w;
        check = w.find('_');
        if (check != std::string::npos) {
            w[check] = ' ';
            vec[counter].Setheavy_attack_name(w);
        }
        else {
            vec[counter].Setheavy_attack_name(w);
        }

        f >> n; vec[counter].Setheavy_attack_dmg(n);
        f >> n; vec[counter].SetType(n);
        f >> n; vec[counter].setRarity(n);

        vec[counter].printPokemon();
        counter++;
    }
}

void kantoStarter(Trainer &player, std::vector<Pokemon>&pokemonDB){

    clear();
    std::cout << "Based on the Kanto region you have access to the following starter pokemon:" << std::endl << std::endl;
    std::cout << "1) Charmander" << std::endl;
    std::cout << "2) Squirtle" << std::endl;
    std::cout << "3) Bulbasuar" << std::endl;

    int userPokemonChoice;//user chooses out of these three pokemon
    std::cin >> userPokemonChoice;

    while(userPokemonChoice < 1 || userPokemonChoice > 3){//error checking until the user has entered an approporate input
        std::cout << "choice is invalid, please try again" << std::endl;
        std::cin >> userPokemonChoice;
    }

    // adds the starters to the pokemon collection
    switch(userPokemonChoice) {
    case 1: player.pokemonCollection.push_back(pokemonDB[0]); break;
    case 2: player.pokemonCollection.push_back(pokemonDB[1]); break;
    case 3: player.pokemonCollection.push_back(pokemonDB[2]); break;
    default: break;
    }
}

void johtoStarter(Trainer &player, std::vector<Pokemon>&pokemonDB){

    clear();
    std::cout << "Based on the Johto region, you have access to the following starter pokemon:" << std::endl << std::endl;
    std::cout << "1) Chikorita" << std::endl;
    std::cout << "2) Cyndaquil" << std::endl;
    std::cout << "3) Totodile" << std::endl;

    std::cout << std::endl;
    int userPokemonChoice;//user chooses out of these three pokemon
    std::cin >> userPokemonChoice;

    while(userPokemonChoice < 1 || userPokemonChoice > 3){//error checking until the user has entered an approporate input
        std::cout << "choice is invalid, please try again" << std::endl;
        std::cin >> userPokemonChoice;
    }

    // adds the starters to the pokemon collection
    switch(userPokemonChoice) {
    case 1: player.pokemonCollection.push_back(pokemonDB[0]); break;
    case 2: player.pokemonCollection.push_back(pokemonDB[1]); break;
    case 3: player.pokemonCollection.push_back(pokemonDB[2]); break;
    default: break;
    }
}

void honenStarter(Trainer &player, std::vector<Pokemon>&pokemonDB){

    clear();
    std::cout << "Based on the Honen region, you have access to the following starter pokemon:" << std::endl << std::endl;
    std::cout << "1) Treeko" << std::endl;
    std::cout << "2) Torchic" << std::endl;
    std::cout << "3) Mudkip" << std::endl;

    int userPokemonChoice;//user chooses out of these three pokemon
    std::cin >> userPokemonChoice;

    while(userPokemonChoice < 1 || userPokemonChoice > 3){//error checking until the user has entered an approporate input
        std::cout << "choice is invalid, please try again" << std::endl;
        std::cin >> userPokemonChoice;
    }

    switch(userPokemonChoice) {
    case 1: player.pokemonCollection.push_back(pokemonDB[0]); break;
    case 2: player.pokemonCollection.push_back(pokemonDB[1]); break;
    case 3: player.pokemonCollection.push_back(pokemonDB[2]); break;
    default: break;
    }
}

void forage(Trainer &player){//adds 3 to on of the quantitative items of trainer (either the balls (normal, great, or ultra), and health/mana pots)

    int min = 1;
    int max = 100;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int randomNumber = min + (std::rand() % (max - min + 1));// 40 4 poke ball, 20 4 great 10 4 ultra 15 4 mana and health each

    if(randomNumber <= 40){//40% chance for 3 normal balls
        player.pokeBalls += 3;
        std::cout << "While exploring the " << player.currRegion << ", you've encountered 3 pokeballs!" << std::endl;
        std::cout << std::endl;
    }

    else if(randomNumber > 40 && randomNumber <= 60){//20% chance for 2 great balls
        player.greatBalls += 2;
        std::cout << "While exploring the " << player.currRegion << ", you've encountered 2 great balls, nice job!" << std::endl;
        std::cout << std::endl;
    }

    else if(randomNumber > 60 && randomNumber <= 70){//10% chance for 2 ultra balls
        player.ultraBalls += 2;
        std::cout << "While exploring the " << player.currRegion << ", you've encountered 2 ultra balls, amazing!" << std::endl;
        std::cout << std::endl;
    }

    else if(randomNumber > 70 && randomNumber <= 85){//both 15% chance for one health or mana pot
        player.healthPot += 1;
        std::cout << "While exploring the " << player.currRegion << ", you've found a health pot, lucky!" << std::endl;
        std::cout << std::endl;
    }

    else{
        player.manaPot += 1;
        std::cout << "While exploring the " << player.currRegion << ", you've found a mana pot, lucky!" << std::endl;
        std::cout << std::endl;
    }
}

void fastTravel(Trainer &player, std::vector<Pokemon> kantoDB, std::vector<Pokemon> johtoDB, std::vector<Pokemon> honenDB){//allows the trainer to change his/her location as well as change the database of pokemon that are region locked in thier new location

    clear();
    int userChoice;
    std::string regions[] = {"Kanto", "Johto", "Honen"};

    if (player.trainerLvl < 5) {//check player level before starting fast travel menu
        std::cout << "(Fast Travel unlocked at Level 5)" << std::endl << std::endl;
        return;
    }

    std::cout << "CURRENT REGION: *" << player.currRegion << "*" << std::endl;
    std::cout << "Which region would you like to Travel to?" << std::endl << std::endl;
    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    std::cin >> userChoice;//will either be 1 for Kanto, 2 for Johto, or 3 representing Honen

    while((userChoice < 1 || userChoice > 3 || player.currRegion == regions[userChoice - 1])){//error checking until the user has entered an approporate input
        clear();
        std::cout << "Region choice is invalid or you are already at the location, please try again" << std::endl;
        std::cin >> userChoice;
    }

    if (userChoice == 1) {

        clear();
        player.currRegion = "Kanto";
        player.currDB = kantoDB;
        std::cout << "You have successfully traveled to the Kanto Region, New adventures and Pokemon await!" << std::endl << std::endl;
    }
    else if (userChoice == 2) {

        clear();
        player.currRegion = "Johto";
        player.currDB = johtoDB;
        std::cout << "You have successfully traveled to the Johto Region, New adventures and Pokemon await!" << std::endl << std::endl;
    }
    else {

        clear();
        player.currRegion= "Honen";
        player.currDB = honenDB;
        std::cout << "You have successfully traveled to the Honen Region, New adventures and Pokemon await!" << std::endl << std::endl;
    }
}

void flee(Trainer &player){// lets the trainer run away, but not without punishment, some items will be lost

    int arr[] = {player.pokeBalls, player.greatBalls, player.ultraBalls, player.healthPot, player.manaPot};

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = 0 + (std::rand() % (4 - 0 + 1));

    if (arr[randomNumber] != 0) {

        int randomAmmount = 1 + (std::rand() % (5 - 1 + 1));

        std::string item;

        switch (randomNumber) {
        case 0: player.pokeBalls -= randomAmmount; if (player.pokeBalls < 0) player.pokeBalls = 0; item = "Pokeball"; break;
        case 1: player.greatBalls -= randomAmmount; if (player.greatBalls < 0) player.greatBalls = 0;item = "Great Ball"; break;
        case 2: player.ultraBalls -= randomAmmount; if (player.ultraBalls < 0) player.ultraBalls = 0;item = "Ultra Ball"; break;
        case 3: player.healthPot -= randomAmmount; if (player.healthPot < 0) player.healthPot = 0;item = "Health Pot"; break;
        case 4: player.manaPot -= randomAmmount; if (player.manaPot < 0) player.manaPot = 0;item = "Mana Pot"; break;
        }

        clear();
        std::cout << "You ran away, but while escaping you lost " << randomAmmount << " " << item;
        if(randomAmmount > 1){
            std::cout << "s";
        }
        std::cout << " !" << std::endl << std::endl;
    }
    else {
        clear();
        std::cout << "You begin to question your skills as a trainer, nonetheless, you successfully ran away" << std::endl;
        std::cout << "Lost 10 XP" << std::endl << std::endl;
        player.xp -= 10;
    }
}

bool catchSim(int userChoice, int successRate, Trainer &player, int randomPokemonIndex, int &catchAttempts){//simualtes the act of catching, bool values will tell the catchPokemon function if the pokemon has been caught or fled.

    int randomNumber;
    int min = 1;
    int max = 100;

    std::cout << "random pokemomn index: " << randomPokemonIndex << std::endl;

    switch(userChoice){

    case 1:
        if(player.pokeBalls > 0){//if the player has the appropraite amount of a certain ball...
            player.pokeBalls--;//lose a pokeball trying to catch the pokemon
        }
        else{
            std::cout << "You dont have enough Pokeballs to catch " << player.currDB[randomPokemonIndex].Getname() << "!" << std::endl;
            return false;
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomNumber = min + (std::rand() % (max - min + 1));

        if(randomNumber <= successRate){//using a pokeball does not change the base success rate
            std::cout << "Wow! You've caught " << player.currDB[randomPokemonIndex].Getname() << std::endl;
            player.pokemonCollection.push_back(player.currDB[randomPokemonIndex]);
            giveXP(player, player.currDB[randomPokemonIndex], 1);

            return true;
        }
        else{
            std::cout << player.currDB[randomPokemonIndex].Getname() << " broke free!" << std::endl;
            catchAttempts++;//after 5, the pokemon runs away
        }

        if(catchAttempts == 5){//runs away after 5 tries
            std::cout << player.currDB[randomPokemonIndex].Getname() << " ran away! :(" << std::endl;
            return true;
        }
        break;

    case 2:
        if(player.greatBalls > 0){//if the player has the appropraite amount of a certain ball...
            player.greatBalls--;//lose a great ball trying to catch the pokemon
        }
        else{
            std::cout << "You dont have enough Great balls to catch " << player.currDB[randomPokemonIndex].Getname() << "!" << std::endl;
            return false;
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomNumber = min + (std::rand() % (max - min + 1));

        if(randomNumber <= successRate + 10){//using a great ball adds 10% to the base sucess rate
            std::cout << "Wow! You've caught " << player.currDB[randomPokemonIndex].Getname() << std::endl;
            player.pokemonCollection.push_back(player.currDB[randomPokemonIndex]);
            giveXP(player, player.currDB[randomPokemonIndex], 1);

            return true;
        }
        else{
            std::cout << player.currDB[randomPokemonIndex].Getname() << " broke free!" << std::endl;
            catchAttempts++;//after 5, the pokemon runs away
        }

        if(catchAttempts == 5){//runs away after 5 tries
            std::cout << player.currDB[randomPokemonIndex].Getname() << " ran away! :(" << std::endl;
            return true;
        }
        break;

    case 3:
        if(player.ultraBalls > 0){//if the player has the appropraite amount of a certain ball...
            player.ultraBalls--;//lose an ultra ball trying to catch the pokemon
        }
        else{
            std::cout << "You dont have enough Ultra balls to catch " << player.currDB[randomPokemonIndex].Getname() << "!" << std::endl;
            return false;
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        randomNumber = min + (std::rand() % (max - min + 1));

        if(randomNumber <= successRate + 15){//using an ultra ball adds 15% chance
            std::cout << "Wow! You've caught " << player.currDB[randomPokemonIndex].Getname()  << "!" << std::endl;
            player.pokemonCollection.push_back(player.currDB[randomPokemonIndex]);
            giveXP(player, player.currDB[randomPokemonIndex], 1);

            return true;
        }
        else{
            std::cout << player.currDB[randomPokemonIndex].Getname() << " broke free!" << std::endl;
            catchAttempts++;//after 5, the pokemon runs away
        }

        if(catchAttempts == 5){//runs away after 5 tries
            std::cout << player.currDB[randomPokemonIndex].Getname() << " ran away! :(" << std::endl;
            return true;
        }
        break;

    }
    return false;
}

void catchPokemon(Trainer &player, int randomPokemonIndex){//function that simulates the catching of a pokemon

    bool caught = false;//variable to loop the menu screen
    int catchAttempts = 0;//the amount of times the player tries to catch a certain pokemon

    std::cout << "Random Pokemon Index: " << randomPokemonIndex << std::endl;
    while (caught == false){
        std::cout << "Which ball would you like to use?" << std::endl << std::endl;
        std::cout << "1.)Pokeball" << std::endl;
        std::cout << "2.)Great Ball" << std::endl;
        std::cout << "3.)Ultra Ball" << std::endl;

        int userChoice;
        std::cin >> userChoice;

        if(player.currDB[randomPokemonIndex].getRarity() == COMMON){//theres a 50% base catch rate
            caught = catchSim(userChoice, 50, player, randomPokemonIndex, catchAttempts);
        }
        else if(player.currDB[randomPokemonIndex].getRarity() == UNCOMMON){//theres a 25% base catch rate
            caught = catchSim(userChoice, 25, player, randomPokemonIndex, catchAttempts);
        }
        else if(player.currDB[randomPokemonIndex].getRarity() == RARE){//theres a 15% base catch rate
            caught = catchSim(userChoice, 15, player, randomPokemonIndex, catchAttempts);
        }
        else{//theres a 10% base catch rate for legendary pokemon
            caught = catchSim(userChoice, 10, player, randomPokemonIndex, catchAttempts);
        }
    }
}

void choosePokemon(Trainer &player, int switches, Pokemon enemyPokemon){//user's pokemon choice when orginially choosing or switching their pokemon

    if (switches > 0){
        std::cout << "Which pokemon would you like to switch with?" << std::endl;
    }
    else {
        std::cout << "Before fighting " << enemyPokemon.Getname() << ", which pokemon would you like to bring to battle?" << std::endl << std::endl;
    }

    printPokemon(player.pokemonCollection);

    int choice;
    std::cin >> choice;

    while(choice > (int)player.pokemonCollection.size()){//if the number entered is larger than the trainers pokemon size, then the user's choice is invalid
        std::cout << "Pokemon choice is invalid, please try again." << std::endl;
        std::cin >> choice;
    }

    player.activePokemon = &player.pokemonCollection[--choice];//returns the info of the pokemon that the player has chosen
}

void choosePokemonToHeal(Trainer &player){

    std::cout << "Which pokemon would you like to heal?" << std ::endl;
    printPokemon(player.pokemonCollection);//lists options for the user to choose

    int choice;
    std::cin >> choice;

    while(choice > (int)player.pokemonCollection.size()){//if the number entered is larger than the trainers pokemon size, then the user's choice is invalid
        std::cout << "Pokemon choice is invalid, please try again." << std::endl;
        std::cin >> choice;
    }

    player.activePokemon = &player.pokemonCollection[choice - 1];//returns the info of the pokemon that the player has chosen
    std::cout << "DEBUG: PLAYER CHOICE SUCCESS\n";
    player.activePokemon->printPokemon();
    std::cout << "DEBUG: POKEMON PRINTED\n";

}

void useManaPot(Trainer &player){ //act of using a mana pot

    if(player.mana == 100){

        std::cout << "You already have max mana!" << std::endl;
        return;
    }

    if(player.manaPot > 0 && player.mana < 100){

        int oldMana = player.mana;
        player.mana += 20;//adds 20 to the player
        int gainedMana = player.mana-oldMana;
        player.manaPot--;

        if(player.mana > 100){
            player.mana = 100;
        }

        std::cout << "Using Mana Pot, you've gained " << gainedMana << " mana!" << std::endl;

        std::cout << "You now have " << player.mana << " Mana and " << player.manaPot << " pots left" << std::endl;

    }

    else{
        std::cout << "You don't have enough Mana pots !" << std::endl;
    }

}

bool findMaxHealth(Trainer &player){


    return false;

}

void useHealthPot(Trainer &player){//act of healing the trainers active pokemon

    if(player.healthPot > 0){

        choosePokemonToHeal(player); //choose pokemon to heal

        for(int i =0; i < 20; i++){
            if(player.activePokemon->Getname() == player.currDB[i].Getname()){//if the pokemon mathced has the same health as the pokemon you chose, then your pokemon is at max health, and cannot be healed any futher
                if(player.activePokemon->Gethp() == player.currDB[i].Gethp()){
                    std::cout << "Your pokemon's hp is allready full\n";
                    return;
                }
                else {
                    std::cout << "DEBUG: Healing pokemon\n";

                    int currentHp = player.activePokemon->Gethp() + 20;
                    if (currentHp > 100) {

                        std::cout << "DEBUG: HP " << player.activePokemon->Gethp() << " will be " << 100 << std::endl;
                        player.activePokemon->Sethp(100);

                        // standard message
                        std::cout << "You've healed " << player.activePokemon->Getname() << " , " << player.activePokemon->Getname() << " now has " << player.activePokemon->Gethp() << " hp!" << std::endl;
                    }
                    else {

                        std::cout << "DEBUG: HP " << player.activePokemon->Gethp() << " will be " << currentHp << std::endl;
                        player.activePokemon->Sethp(currentHp);

                        //standard message
                        std::cout << "You've healed " << player.activePokemon->Getname() << " , " << player.activePokemon->Getname() << " now has " << player.activePokemon->Gethp() << " hp!" << std::endl;
                    }
                    return;
                }
            }
        }
    }

    else{
        std::cout << "You don't have enough health pots to heal" << player.activePokemon->Getname() << "!" << std::endl;
    }

}

bool victoryOrDefeat(Pokemon victimPokemon, Trainer &player, int &turns){//victory dialouge for the player after beating said pokemon, exp earned is based off of the rarity of the pokemon

    if(turns % 2 != 0){//when you defeat a pokemon
        std::cout << victimPokemon.Getname() << " has been defeated!" << std::endl;

        giveXP(player, victimPokemon, 2);//rewarding the trainer exp
        return true;
    }

    else{//when your pokemon has been defeated
        std::cout << "Your " << victimPokemon.Getname() << " has been defeated!" << std::endl;
        return false;//gives the player a chance to switch their pokemon out, dont want to close them out after just losing one of their pokemon
    }

}

void attackNotEffective(Pokemon &attacker, Pokemon &victim, int baseOrHeavy, int &turns){//the dialouge for a base/heavy attack that is not very effective

    switch(baseOrHeavy){

    case 1:

            if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getbase_attack_name() << std::endl << std::endl;
        std::cout << "Its not very effective..." << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getbase_attack_dmg() * 0.5) << " dmg and has ";
        break;

    case 2:

         if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getbase_attack_name() << std::endl << std::endl;
        std::cout << "Its not very effective..." << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getbase_attack_dmg() * 0.5) << " dmg and has ";
        break;

    }

}

void attackNormalEffective(Pokemon &attacker, Pokemon &victim, int baseOrHeavy, int &turns){//the dialouge for a base/heavy attack that is normal effective


    switch(baseOrHeavy){

    case 1:

         if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getbase_attack_name() << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getbase_attack_dmg()) << " dmg and has ";
        break;

    case 2:

         if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getheavy_attack_name() << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getheavy_attack_dmg()) << " dmg and has ";
        break;

    }


}

void attackSuperEffective(Pokemon &attacker, Pokemon &victim, int baseOrHeavy, int &turns){//the dialouge for a base/heavy attack that is super effective

    switch(baseOrHeavy){

    case 1:

         if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getbase_attack_name() << std::endl << std::endl;
        std::cout << "Its super effective!" << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getbase_attack_dmg() * 2) << " dmg and has ";
        break;

    case 2:

         if(turns % 2 != 0){//the players action
                std::cout << "Your ";
            }
            else{//the enemy's action
                std::cout << "The enemy ";//helps to identify pokemon if the trainer is fighting with the same pokemon to avoid confusion
            }

        std::cout << attacker.Getname() << " used " << attacker.Getheavy_attack_name() << std::endl << std::endl;
        std::cout << "Its super effective!" << std::endl;
        std::cout << victim.Getname() << " took " << (attacker.Getheavy_attack_dmg() * 2) << " dmg and has ";
        break;

    }

}

bool checkIfDead(Pokemon &victim, Trainer &player, int &turns){//bool that returns true if dead to get out of the while loop in the fight menu

    if(victim.Gethp() <=0){

        victim.Sethp(0);
        std::cout << "no health left!" << std::endl;
       return victoryOrDefeat(victim, player, turns); //returns true so the while loop of the attack menu ends


    }

    else{
        std::cout << victim.Gethp() << " health left!" << std::endl;
        return false;
    }

}

void attackWhenNoHp(Pokemon & attacker, Trainer &player, int &turns, Pokemon &victim){//checks if the user is trying to fight with a fainted pokemon


    if(attacker.Gethp() == 0){

        int choice;

        std::cout << attacker.Getname() << " does not have any health!" << std::endl;

        std::cout << "would you like to heal or switch " << attacker.Getname() << "?" << std::endl << std::endl;

        std::cout << "1.)Heal" << std::endl;
        std::cout << "2.)Switch" << std::endl;

        std::cin >> choice;

        switch(choice){

        case 1: useHealthPot(player);break;
        case 2: choosePokemon(player, turns, victim); break;
        default: std::cout << "invalid choice, please try again" << std::endl;

        }
    }

}

bool baseAttackSim(Pokemon &attacker, Pokemon &victim, Trainer &player, int &turns){//the base attack sim for a pokemon

    if(attacker.GetType() == NORMAL){//strong against nothing, weak to fighting (not included)

            victim.Sethp(victim.Gethp() - attacker.Getbase_attack_dmg());//setting the enemy pokemon's health to its current health minus the dmg of the active pokemons base attack

            attackNormalEffective(attacker, victim, 1, turns);

            return checkIfDead(victim, player, turns);
        }

    if(attacker.GetType() == FIRE){//strong against grass, weak to water

            if(victim.GetType() == GRASS){ //trainers fire type pokemon will do 2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);

            }

            else if(victim.GetType() == WATER){ //trainers fire type pokemon will do 1/2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is neither water or grass

                victim.Sethp(victim.Gethp() - attacker.Getbase_attack_dmg());

                attackNormalEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

        }

    if(attacker.GetType() == GRASS){//strong against water, weak to fire

            if(victim.GetType() == FIRE){ //trainers grass type pokemon will do 1/2x dmg to a fire type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else if(victim.GetType() == WATER){ //trainers grass type pokemon will do 2x dmg to a water type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is neither water or fire

                victim.Sethp(victim.Gethp() - attacker.Getbase_attack_dmg());

                attackNormalEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

        }

    if(attacker.GetType() == WATER){//strong against fire, weak to grass and eletric

            if(victim.GetType() == GRASS){ //trainers water type pokemon will do 1/2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else if(victim.GetType() == ELECTRIC){ //trainers water type pokemon will do 1/2x dmg to a electric type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else if(victim.GetType() == FIRE){ //trainers water type pokemon will do 2x dmg to a fire type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is neither fire, grass, or electric

                victim.Sethp(victim.Gethp() - attacker.Getbase_attack_dmg());

                attackNormalEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

        }

    if(attacker.GetType() == ELECTRIC){//strong against water

            if(victim.GetType() == WATER){ //trainers electric type pokemon will do 2x dmg to a water type

                victim.Sethp(victim.Gethp() - (attacker.Getbase_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is not water

                victim.Sethp(victim.Gethp() - attacker.Getbase_attack_dmg());

                attackNormalEffective(attacker, victim, 1, turns);

                return checkIfDead(victim, player, turns);
            }

        }
    return false;
}

bool heavyAttackSim(Pokemon &attacker, Pokemon &victim, Trainer &player, int &turns){//the heavy attack sim for a pokemon

    if(attacker.GetType() == NORMAL){//strong against nothing, weak to fighting (not included)

            victim.Sethp(victim.Gethp() - attacker.Getheavy_attack_dmg());//setting the enemy pokemon's health to its current health minus the dmg of the active pokemons base attack

            attackNormalEffective(attacker, victim, 2, turns);

            return checkIfDead(victim, player, turns);

        }

    if(attacker.GetType() == FIRE){//strong against grass, weak to water

            if(victim.GetType() == GRASS){ //trainers fire type pokemon will do 2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

            else if(victim.GetType() == WATER){ //trainers fire type pokemon will do 1/2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

            else{//do normal dmg if enemy pokemon is neither water or grass

                victim.Sethp(victim.Gethp() - attacker.Getheavy_attack_dmg());

                attackNormalEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

        }

    if(attacker.GetType() == GRASS){//strong against water, weak to fire

            if(victim.GetType() == FIRE){ //trainers grass type pokemon will do 1/2x dmg to a fire type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

            else if(victim.GetType() == WATER){ //trainers grass type pokemon will do 2x dmg to a water type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is neither water or fire

                victim.Sethp(victim.Gethp() - attacker.Getheavy_attack_dmg());

                attackNormalEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

        }

    if(attacker.GetType() == WATER){//strong against fire, weak to grass and eletric

            if(victim.GetType() == GRASS){ //trainers water type pokemon will do 1/2x dmg to a grass type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);
            }

            else if(victim.GetType() == ELECTRIC){ //trainers water type pokemon will do 1/2x dmg to a electric type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * .5));

                attackNotEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);
            }

            else if(victim.GetType() == FIRE){ //trainers water type pokemon will do 2x dmg to a fire type

                victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * 2));

                attackSuperEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);
            }

            else{//do normal dmg if enemy pokemon is neither fire, grass, or electric

                victim.Sethp(victim.Gethp() - attacker.Getheavy_attack_dmg());

                attackNormalEffective(attacker, victim, 2, turns);

                 return checkIfDead(victim, player, turns);

            }

        }

    if(attacker.GetType() == ELECTRIC){//strong against water

        if(victim.GetType() == WATER){ //trainers electric type pokemon will do 2x dmg to a water type

            victim.Sethp(victim.Gethp() - (attacker.Getheavy_attack_dmg() * 2));

            attackSuperEffective(attacker, victim, 1, turns);

             return checkIfDead(victim, player, turns);
        }

        else{//do normal dmg if enemy pokemon is not water

            victim.Sethp(victim.Gethp() - attacker.Getheavy_attack_dmg());

            attackNormalEffective(attacker, victim, 1, turns);

            return checkIfDead(victim, player, turns);
        }
    }
    return false;
}

bool heavyAttack(Pokemon &attacker, Pokemon &victim, Trainer &player, int &turns){//function used to error check the players mana, and pokemon health before commiting an attack

    if(attacker.Gethp() <= 0){

        attackWhenNoHp(attacker ,player, turns, victim);//checks if the trainer is trying to attack the pokemon when theirs is fainted!

    }

    if(turns % 2 != 0){//if player is attacking (bc they attack first)

        if(player.mana >=10){//and the player has enough mana to do the attack

            player.mana -= 10;
            return heavyAttackSim(attacker, victim, player, turns);//returns false if neither pokemon is dead, to continue the while loop
        }

        else{//if the trainer does not have enough mana...

            std::cout << "You dont have enough mana for " << attacker.Getname() << " to use " <<attacker.Getheavy_attack_name() << "!" << std::endl;

        }

        return false;//returns false to continue the while loop, this means niether pokemon is not dead yet
    }

    if(turns % 2 == 0){//if the CPU is attacking

            return heavyAttackSim(attacker, victim, player, turns);//commit the action, CPU pokemon does not worry about mana

    }

    return false;
}

bool baseAttack(Pokemon &attacker, Pokemon &victim, Trainer &player, int &turns){//function used to error check the players mana, and pokemon health before commiting an attack

   if(attacker.Gethp() <= 0){

        attackWhenNoHp(attacker ,player, turns, victim);//checks if the trainer is trying to attack the pokemon when theirs is fainted!

    }

   if(turns % 2 != 0){//if player is attacking (bc they attack first)

        if(player.mana >=10){//and the player has enough mana to do the attack

            player.mana -= 10;
            return baseAttackSim(attacker, victim, player, turns);//returns false if neither pokemon is dead, to continue the while loop
        }

        else{//if the trainer does not have enough mana...

            std::cout << "You dont have enough mana for " << attacker.Getname() << " to use " <<attacker.Getbase_attack_name() << "!" << std::endl;

        }

        return false;//returns false to continue the while loop, this means niether pokemon is not dead yet
    }

     if(turns % 2 == 0){//if the CPU is attacking

            return baseAttackSim(attacker, victim, player, turns);//commit the action, CPU pokemon does not worry about mana

    }
    return false;
}

bool attack(Pokemon &attacker, Pokemon &victim, Trainer &player, int &turns, int choice){

    switch(choice){
    case 1: return baseAttack(attacker, victim, player, turns); break;
    case 2: return heavyAttack(attacker, victim, player, turns); break;
    }
    return false;
}

int enemyChoice(){//random decision the enemy pokemon makes (either it heavy attacks or, base attacks you)

    std::random_device rd;

    std::mt19937 generator(rd());

    // Define the range of numbers (1 and 2)
    std::uniform_int_distribution<int> distribution(1, 2);

    // Generate a random number
    return distribution(generator);

}

void fight(Trainer &player, int randomPokemonIndex){

    bool defeatOrFlee = false;//either you defeat the pokemon, or you flee

    int switches = 0;//# of times a user will switch his pokemon, changes dialouge for first choosing a pokemon, to switching it
    int turns = 0;//if turns are odd, thats the player, if turns even , thats the enemy pokemon fighting

    Pokemon enemyPokemon = player.currDB[randomPokemonIndex];//makes the randomly encountered pokemon a single varibale
    choosePokemon(player, switches, enemyPokemon); // user will choose based on number output from this member function

    while(defeatOrFlee == false){



        int userChoice;
        int CPUchoice;

            if(player.activePokemon->Gethp() > 0){//inclines the player to heal the pokemon, rather than try to attack with no health, albeit there's error checking for this
                std::cout << "What will you attack " << enemyPokemon.Getname() << " with?" << std::endl << std::endl;
                std::cout << "1)Base attack: " << player.activePokemon->Getbase_attack_name() << " " << player.activePokemon->Getbase_attack_dmg() << " dmg (Mana cost: 5)" << std::endl;
                std::cout << "2)Heavy attack: " << player.activePokemon->Getheavy_attack_name() << " " << player.activePokemon->Getheavy_attack_dmg() << " dmg (Mana cost: 20)" << std::endl << std::endl;

                std::cout << "Other:" << std::endl;
            }

            else{
                std::cout << "What will you do?" << std::endl << std::endl;
            }

        std::cout << "3)Consume Mana Pot (+20 Mana)" << std::endl;
        std::cout << "4)Heal Pokemon (+20 Health)" << std::endl;//heals a specific pokemon
        std::cout << "5)Switch Pokemon" << std::endl;//switches the active pokemon of the trainer
        std::cout << "6) Flee!" << std::endl;

        std::cin >> userChoice;
        CPUchoice = enemyChoice();

        std::cout << std::endl;

        switch(userChoice){

        case 1: defeatOrFlee = attack(*player.activePokemon, enemyPokemon, player, ++turns, 1);
                std::cout << enemyPokemon.Getname() << "'s turn!" << std::endl << std::endl;
                defeatOrFlee = attack(enemyPokemon, *player.activePokemon, player, ++turns, CPUchoice); //the CPU attacking you
                break;

        case 2: defeatOrFlee = attack(*player.activePokemon, enemyPokemon, player, ++turns, 2);
           if(defeatOrFlee == false){
               std::cout << enemyPokemon.Getname() << "'s turn!" << std::endl << std::endl;
                defeatOrFlee = attack(enemyPokemon, *player.activePokemon, player, ++turns, CPUchoice); //the CPU attacking you
            }
            break;

        case 3: useManaPot(player); break;
        case 4: useHealthPot(player); break;
        case 5: choosePokemon(player, ++switches, enemyPokemon); break;
        case 6: flee(player); defeatOrFlee = true; break;
        default: std::cout << "Invalid input" << std::endl; break;

        }

    }
}

void explore(Trainer &player){

    std::cout << "Starting explore function\n";
    int min = 0;
    int max = player.currDB.size() - 1;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int randomNumber = min + (std::rand() % (max - min + 1));

    clear();
    std::cout << "Random number calcuated : " << randomNumber << std::endl;
    std::cout << "After roaming for some time in the " << player.currRegion << " Region, you've run into " << player.currDB[randomNumber].Getname() << "!" << std::endl << std::endl;
    std::cout << "Here are some of "<< player.currDB[randomNumber].Getname() << "'s Stats:" << std::endl << std::endl;

    player.currDB[randomNumber].printPokemon();
    // std::cout << "Name: " << player.currDB[randomNumber].Getname() << std::endl
    //           << "Type: " << player.currDB[randomNumber].GetTypeAsString(player.currDB[randomNumber].GetType()) << std::endl
    //           << "HP: " << player.currDB[randomNumber].Gethp() << std::endl << std::endl
    //           << "Base_Attack: " << player.currDB[randomNumber].Getbase_attack_name() << ", " << player.currDB[randomNumber].Getbase_attack_dmg() << " dmg" << std::endl
    //           << "Heavy_Attack: " << player.currDB[randomNumber].Getheavy_attack_name() << ", " << player.currDB[randomNumber].Getheavy_attack_dmg() << std::endl << std::endl;

    int userChoice;

    std::cout << "What would you like to do? (Enter number)" << std::endl;
    std::cout << "1) Catch it" << std::endl;
    std::cout << "2) Fight it" << std::endl;
    std::cout << "3) Flee!" << std::endl;

    std::cin >> userChoice;

    switch(userChoice) {
    case 1: catchPokemon(player, randomNumber); break;
    case 2: fight(player, randomNumber); break;
    case 3: flee(player); break;
    default: std::cout << "Invalid input" << std::endl; break; //error checking
    }
}

void menu(Trainer &player, std::vector<Pokemon> kantoDB, std::vector<Pokemon> johtoDB, std::vector<Pokemon> honenDB){//main hub of the game, where trainer either encounters pokemon, forages for new items, or fast travels to a new location.

    clear();
    int userChoice;

    while(userChoice != 0) {

        //the node size is still zero, appending to list does not work
        std::cout << "Number of pokemon in collection: " << std::endl;
        std::cout << player.pokemonCollection.size() << std::endl;

        std::cout << "What would you like to do? (Enter number)" << std::endl << std::endl;
        std::cout << "1) Forage" << std::endl;//DONE
        std::cout << "2) Explore" << std::endl;
        std::cout << "3) Fast Travel to another region" << std::endl;//DONE
        std::cout << "4) View Stats" << std::endl;//DONE
        std::cout << std::endl << "0) QUIT" << std::endl;//DONE

        std::cin >> userChoice;
        clear();

        switch(userChoice) {
        case 0: std::cout << "Exiting menu!" << std::endl; break;
        case 1: forage(player); break;
        case 2: explore(player); break;
        case 3: fastTravel(player, kantoDB, johtoDB, honenDB); break;
        case 4: showStats(player); break;
        default: std::cout << "Invalid input" << std::endl; break;
        }
    }
}

int main() {

    Trainer player;//this represents the user/player.

    std::string kantoPokemonFile = "kanto_pokemon.txt";
    std::string johtoPokemonFile = "johto_pokemon.txt";
    std::string honenPokemonFile = "honen_pokemon.txt";
    // std::string kantoPokemonFile =  "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\kanto_pokemon.txt";//file names and path for each of the corresponding regions
    // std::string johtoPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\johto_pokemon.txt";
    // std::string honenPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";

    clear();
    std::cout << "Hello trainer! Welcome to world of Pokemon, to begin, which region would you like to start in?" << std::endl << std::endl;
    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;

    int userChoice;
    std::cin >> userChoice;//will either be 1 for Kanto, 2 for Johto, or 3 representing Honen

    while(userChoice < 1 || userChoice > 3){//error checking until the user has entered an approporate input
        std::cout << "Region choice is invalid, please try again" << std::endl;
        std::cin >> userChoice;
    }

    //change this back to proper ammount of pokemon
    int numOfPokemon = 3;

    std::vector<Pokemon> kantoDataBase(numOfPokemon);//intializes vectors of type pokemon with the predetermined size of how many records are in their respective files
    std::vector<Pokemon> johtoDataBase(numOfPokemon);
    std::vector<Pokemon> honenDataBase(numOfPokemon);

    readPokemonData(kantoPokemonFile, numOfPokemon, kantoDataBase);//reads the info to the corresponding vectors of region
    readPokemonData(johtoPokemonFile, numOfPokemon, johtoDataBase);
    readPokemonData(honenPokemonFile, numOfPokemon, honenDataBase);

    player.kantoDB = kantoDataBase;
    player.johtoDB = johtoDataBase;
    player.honenDB = honenDataBase;

    switch(userChoice){//used to identify which starter the user will have acess to depending on their region of choice
    case 1:
        player.currRegion = "Kanto";
        kantoStarter(player, kantoDataBase);
        player.currDB = kantoDataBase;
        break;
    case 2:
        player.currRegion = "Johto";
        johtoStarter(player, johtoDataBase);
        player.currDB = johtoDataBase;
        break;
    case 3:
        player.currRegion = "Hoenn";
        honenStarter(player, honenDataBase);
        player.currDB = honenDataBase;
        break;

    default: break;
    }
    menu(player, kantoDataBase, johtoDataBase, honenDataBase);//player chooses what to do

    return 0;
}
