#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

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

struct Trainer{//this is the content of the current player, the linked list of pokemon (his/her pokemonCollection), their lvl, and some forageable items (pokeBalls, health and mana pots).

    Pokedex pokemonCollection;
    int trainerLvl = 5; //for testing features
    int xp = 0;
    int mana = 100;
    // int trainerLvl = 1;

    int pokeBalls = 10;
    int greatBalls = 5;
    int ultraBalls = 2;

    int manaPot = 5;
    int healthPot = 5;

    std::string currRegion;
    std::vector<Pokemon> currDB;
    Pokemon * activePokemon;

};

void showStats(Trainer &player) {//show stats for debugging

    std::cout << "Level: " << player.trainerLvl << std::endl;
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

    player.pokemonCollection.printPokemon();
    // player.pokemonCollection.printCurrPokemon();
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
    std::string w;
    while (counter < size) {
        f >> w; vec[counter].Setname(w);
        f >> n; vec[counter].SetevoStage(n);
        f >> n; vec[counter].Sethp(n);
        f >> w; vec[counter].Setbase_attack_name(w);
        f >> n; vec[counter].Setbase_attack_dmg(n);
        f >> w; vec[counter].Setheavy_attack_name(w);
        f >> n; vec[counter].Setheavy_attack_dmg(n);
        f >> n; vec[counter].SetType(n);
        f >> n; vec[counter].setRarity(n);

        vec[counter].printPokemon();
        counter++;
    }
}

Pokemon * findPokemon(std::string name, int N, std::vector<Pokemon> &pokemonDB){//finds and returns of a pokemon given its name, helpful annexing pokemon into the trainers collection

    for(int i = 0; i < N; i++){
        if(pokemonDB[i].Getname() == name){
            return &pokemonDB[i];
        }
    }
    return nullptr;
}

void kantoStarter(Trainer &player, int N, std::vector<Pokemon>&pokemonDB){

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
        case 1: player.pokemonCollection.appendPokemon(findPokemon("Charmander", N, pokemonDB)); break;
        case 2: player.pokemonCollection.appendPokemon(findPokemon("Squirtle", N, pokemonDB)); break;
        case 3: player.pokemonCollection.appendPokemon(findPokemon("Bulbasuar", N, pokemonDB)); break;
        default: break;
    }
}

void johtoStarter(Trainer &player, int N, std::vector<Pokemon>&pokemonDB){

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
        case 1: player.pokemonCollection.appendPokemon(findPokemon("Chikorita", N, pokemonDB)); break;
        case 2: player.pokemonCollection.appendPokemon(findPokemon("Cyndaquil", N, pokemonDB)); break;
        case 3: player.pokemonCollection.appendPokemon(findPokemon("Totodile", N, pokemonDB)); break;
        default: break;
    }
}

void honenStarter(Trainer &player, int N, std::vector<Pokemon>&pokemonDB){

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
        case 1: player.pokemonCollection.appendPokemon(findPokemon("Treeko", N, pokemonDB)); break;
        case 2: player.pokemonCollection.appendPokemon(findPokemon("Torchic", N, pokemonDB)); break;
        case 3: player.pokemonCollection.appendPokemon(findPokemon("Mudkip", N, pokemonDB)); break;
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
        std::cout << "You begin to question your skills as a trainer, nonetheless, you successfully ran away" << std::endl << std::endl;
        player.xp -= 50;
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
            player.pokemonCollection.appendPokemon(&player.currDB[randomPokemonIndex]);
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
            player.pokemonCollection.appendPokemon(&player.currDB[randomPokemonIndex]);
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
            player.pokemonCollection.appendPokemon(&player.currDB[randomPokemonIndex]);
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

void catchPokemon(Trainer &player, int randomPokemonIndex){//function that simulates the catching of a pokemon, %  chance of catch is as follows: 50% common, 25% uncommon, 15% rare, and 10% legendary
    
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

Pokemon * choosePokemon(Trainer &player, int choice){//input validation for the user's pokemon choice

        while(choice > player.pokemonCollection.findNodeSize()){//if the number entered is larger than the trainers pokemon size, then the user's choice is invalid
            std::cout << "Pokemon choice is invalid, please try again." << std::endl;
            std::cin >> choice;
        }

    return player.pokemonCollection.findPokemonAtIndex(choice);//returns the info of the pokemon that the player has chosen
}

void fight(Trainer &player, int randomPokemonIndex){
    
    bool attack = false;//either you defeat the pokemon, or you flee
    Pokemon enemyPokemon = player.currDB[randomPokemonIndex];//makes the randomly encountered pokemon a single varibale
    
    while(attack == false){
        std::cout << "Before fighting " << player.currDB[randomPokemonIndex].Getname() << ", which pokemon would you like to bring to battle?" << std::endl << std::endl;
        
        player.pokemonCollection.printCurrPokemon();// user will choose based on number output from this member function
        
        int choice;
        std::cin >> choice;
        player.activePokemon = choosePokemon(player, choice);// sets the active pokemon of the trainer to the pokemon he/she picked
        
        std::cout << "What will you attack " << enemyPokemon.Getname() << " with?" << std::endl << std::endl;
        
        int userChoice;
        
        std::cout << "1)Base attack: " << player.activePokemon->Getbase_attack_name() << player.activePokemon->Getbase_attack_dmg() << " dmg (Mana cost: 5)" << std::endl;
        std::cout << "2)Heavy attack: " << player.activePokemon->Getheavy_attack_name() << player.activePokemon->Getheavy_attack_dmg() << " dmg (Mana cost: 20)" << std::endl;
        std::cout << "Other:" << std::endl;
        
        std::cout << "3)Consume Mana Pot (+20 Mana)" << std::endl;
        std::cout << "4)Use Health Pot (+20 Health)" << std::endl;//heals a specific pokemon
        std::cout << "5)Switch Pokemon" << std::endl;//switches the active pokemon of the trainer
        
        std::cin >> userChoice;
        
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
    std::cout << "After roaming for some time in the " << player.currRegion << " Region, you've run into " << player.currDB[randomNumber].Getname() << "!" << std::endl;
    // std::cout << "Here are some of "<< player.currDB[randomNumber].Getname() << "'s Stats:" << std::endl << std::endl;
    
    std::cout << "Name: " << player.currDB[randomNumber].Getname() << std::endl
              << "Type: " << player.currDB[randomNumber].GetTypeAsString(player.currDB[randomNumber].GetType()) << std::endl
              << "HP: " << player.currDB[randomNumber].Gethp() << std::endl << std::endl
              << "Base_Attack: " << player.currDB[randomNumber].Getbase_attack_name() << ", " << player.currDB[randomNumber].Getbase_attack_dmg() << " dmg" << std::endl 
              << "Heavy_Attack: " << player.currDB[randomNumber].Getheavy_attack_name() << ", " << player.currDB[randomNumber].Getheavy_attack_dmg() << std::endl << std::endl;
    
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
    std::cout << player.pokemonCollection.findNodeSize() << std::endl;

    // Pokemon *P = findPokemon("Charmander", 3, kantoDB);
    // P.printPokemon();
        std::cout << "What would you like to do? (Enter number)" << std::endl << std::endl;
        std::cout << "1) Forage" << std::endl;//DONE
        std::cout << "2) Explore" << std::endl;

        std::cout << "3) Fast Travel to another region" << std::endl;//DONE
        std::cout << "4) View Stats" << std::endl;//DONE
        std::cout << std::endl << "0) QUIT" << std::endl;//DONE

        // std::cout << "Kanto: \n";
        // for (auto x : kantoDB) x.printPokemon();
        // std::cout << "Johto: \n";
        // for (auto x : johtoDB) x.printPokemon();
        // std::cout << "Honen: \n";
        // for (auto x : honenDB) x.printPokemon();

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

    // std::cout << "Kanto: \n";
    // for (auto x : kantoDataBase) x.printPokemon();
    // std::cout << "Johto: \n";
    // for (auto x : johtoDataBase) x.printPokemon();
    // std::cout << "Honen: \n";
    // for (auto x : honenDataBase) x.printPokemon();

    player.pokemonCollection.appendPokemon(nullptr);

    switch(userChoice){//used to identify which starter the user will have acess to depending on their region of choice
        case 1:
            player.currRegion = "Kanto";
            kantoStarter(player, numOfPokemon, kantoDataBase);
            player.currDB = kantoDataBase;
            break;
        case 2:
            player.currRegion = "Johto";
            johtoStarter(player, numOfPokemon, johtoDataBase);
            player.currDB = johtoDataBase;
            break;
        case 3:
            player.currRegion = "Hoenn";
            honenStarter(player, numOfPokemon, honenDataBase);
            player.currDB = honenDataBase;
            break;

        default: break;
    }
    menu(player, kantoDataBase, johtoDataBase, honenDataBase);//player chooses what to do

    return 0;
}
