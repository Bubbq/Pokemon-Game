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
    int xp = 0;
    int trainerLvl = 1;
    int pokeBalls = 10;
    int greatBalls = 5;
    int ultraBalls = 2;
    int manaPot = 5;
    int healthPot = 5;
    std::string currRegion;
    std::vector<Pokemon> currDB;

};

void showStats(Trainer &player) {//show stats for debugging

    std::cout << "Level: " << player.trainerLvl << std::endl;

    std::cout << "Pokeballs: " << std::endl;
    std::cout << "\t Normal: " << player.pokeBalls << std::endl;
    std::cout << "\t Great: " << player.greatBalls << std::endl;
    std::cout << "\t Ultra: " << player.ultraBalls << std::endl;

    std::cout << "Recovery: " << std::endl;
    std::cout << "\t Health Pots: " << player.healthPot << std::endl;
    std::cout << "\t Mana Pots: " << player.manaPot << std::endl;
    std::cout << std::endl;

    std::cout << "TEAM:" << std::endl;

    player.pokemonCollection.printCurrPokemon();
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

        // vec[counter].print();
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

 std::cout << "Which region would you like to Travel to?" << std::endl << std::endl;

    int forbiddenNumber; //choice representing the region that the trainer is already in.


    std::cout << "1) Kanto";
        if(player.currRegion == "Kanto"){
            std::cout << "(Already Here!)" << std::endl;
            forbiddenNumber = 1;
        }

        else{
           std::cout << std::endl;
        }

    std::cout << "2) Johto";
         if(player.currRegion == "Johto"){
            std::cout << "(Already Here!)" << std::endl;
            forbiddenNumber = 2;
        }

        else{
           std::cout << std::endl;
        }


    std::cout << "3) Honen";
        if(player.currRegion == "Honen"){
            std::cout << "(Already Here!)" << std::endl;
            forbiddenNumber = 3;
        }

        else{
           std::cout << std::endl;
        }

    int userChoice;
    std::cin >> userChoice;//will either be 1 for Kanto, 2 for Johto, or 3 representing Honen

    while((userChoice < 1 || userChoice > 3) || userChoice == forbiddenNumber){//error checking until the user has entered an approporate input
        std::cout << " Region choice is invalid, please try again" << std::endl;
        std::cin >> userChoice;
    }

    switch (userChoice){

        case 1: player.currRegion == "Kanto";
            player.currDB = kantoDB;
            std::cout << "You have successfully traveled to the Kanto Region, New adventures and Pokemon await!" << std::endl;
            break;

        case 2: player.currRegion == "Johto";
            player.currDB = johtoDB;
            std::cout << "You have successfully traveled to the Johto Region, New adventures and Pokemon await!" << std::endl;
            break;

        default: player.currRegion == "Honen";
            player.currDB = honenDB;
            std::cout << "You have successfully traveled to the Honen Region, New adventures and Pokemon await!" << std::endl;
            break;
    }

}

void menu(Trainer &player, std::vector<Pokemon> kantoDB, std::vector<Pokemon> johtoDB, std::vector<Pokemon> honenDB){//main hub of the game, where trainer either encounters pokemon, forages for new items, or fast travels to a new location.

    clear();
    int userChoice;

    while(userChoice != 0) {
        std::cout << "What would you like to do? (Enter number)" << std::endl << std::endl;
        std::cout << "1) Forage" << std::endl;//DONE
        std::cout << "2) Explore" << std::endl;
        std::cout << "3) Fast Travel to another region" << std::endl;//DONE
        std::cout << "4) View Stats" << std::endl;//DONE
        std::cout << std::endl << "0) QUIT" << std::endl;//DONE

        std::cin >> userChoice;
        clear();

        switch(userChoice){
        case 0: std::cout << "Exiting menu!" << std::endl; break;

        case 1: forage(player); break;

        case 2: std::cout << "Explore function\n"; break; // EXPLORE FUNCTION GOES HERE

        case 3: if(player.trainerLvl < 5){
                    std::cout << "(Unlocked at Lvl 5)" << std::endl;
                }
                else {
                       fastTravel(player, kantoDB, johtoDB, honenDB);
                }
                break;

        case 4: showStats(player); break;
        default: break;
        }
    }
}

int main() {

    Trainer player;//this represents the user/player.

    // std::string kantoPokemonFile = "./kanto_pokemon.txt";
    // std::string johtoPokemonFile = "./johto_pokemon.txt";
    // std::string honenPokemonFile = "./honen_pokemon.txt";
    std::string kantoPokemonFile =  "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\kanto_pokemon.txt";//file names and path for each of the corresponding regions
    std::string johtoPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\johto_pokemon.txt";
    std::string honenPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";

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

    int kantoNum = getNumberOfLines(kantoPokemonFile);//find how many records are in each available region
    int johtoNum = getNumberOfLines(johtoPokemonFile);
    int honenNum = getNumberOfLines(honenPokemonFile);

    std::vector<Pokemon> kantoDataBase(kantoNum);//intializes vectors of type pokemon with the predetermined size of how many records are in their respective files
    std::vector<Pokemon> johtoDataBase(johtoNum);
    std::vector<Pokemon> honenDataBase(honenNum);

    readPokemonData(kantoPokemonFile, kantoNum, kantoDataBase);//reads the info to the corresponding vectors of region
    readPokemonData(johtoPokemonFile, johtoNum, johtoDataBase);
    readPokemonData(honenPokemonFile, honenNum, honenDataBase);

    switch(userChoice){//used to identify which starter the user will have acess to depending on their region of choice
    case 1:
        player.currRegion = "Kanto";
        kantoStarter(player, kantoNum, kantoDataBase);
        player.currDB = kantoDataBase;
        break;
    case 2:
        player.currRegion = "Johto";
        johtoStarter(player, johtoNum, johtoDataBase);
        player.currDB = johtoDataBase;
        break;
    case 3:
        player.currRegion = "Hoenn";
        honenStarter(player, honenNum, honenDataBase);
        player.currDB = honenDataBase;
        break;
    default: break;
    }

    menu(player, kantoDataBase, johtoDataBase, honenDataBase);//player chooses what to do

    return 0;
}
