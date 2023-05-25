#include <iostream>
#include <fstream>
#include <vector>

#include "pokemon.h"
#include "pokedex.h"

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

struct Trainer{//this is the content of the current player, the linked list of pokemon (his/her pokemonCollection), their lvl, and some forageable items (pokeBalls, health and mana pots).
    
    Pokedex pokemonCollection;
    int xp;
    int trainerLvl = 1;
    int pokeBalls = 20;
    int greatBalls = 10;
    int ultraBalls = 5;
    int manaPot = 5;
    int healthPot = 5;
};

Pokemon * findPokemon(std::string name, int N, std::vector<Pokemon> &pokemonDB){//finds and returns of a pokemon given its name, helpful annexing pokemon into the trainers collection
    
    for(int i = 0; i < N; i++){
        if(pokemonDB[i].Getname() == name){
            return &pokemonDB[i];
        }
    }
    return nullptr;
}

void kantoStarter(Trainer &player, int N, std::vector<Pokemon>&pokemonDB){
    
    std::cout << "\033[2J\033[1;1H";
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
    
    std::cout << "\033[2J\033[1;1H";
    std::cout << "Based on the Johto region, you have access to the following starter pokemon:" << std::endl << std::endl;
    std::cout << "1) Chikorita" << std::endl;
    std::cout << "2) Cyndaquil" << std::endl;
    std::cout << "3) Totodile" << std::endl;
    
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
    
    std::cout << "\033[2J\033[1;1H";
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


int main() {
    
    Trainer player;//this represents the user/player.
    
    // std::string kantoPokemonFile = "./kanto_pokemon.txt";
    // std::string johtoPokemonFile = "./johto_pokemon.txt";
    // std::string honenPokemonFile = "./honen_pokemon.txt";
    std::string kantoPokemonFile =  "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\kanto_pokemon.txt";//file names and path for each of the corresponding regions
    std::string johtoPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\johto_pokemon.txt";
    std::string honenPokemonFile = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";
    
    std::cout << "\033[2J\033[1;1H"; //hack to clear terminal before printing text
    std::cout << "Hello trainer! Welcome to world of Pokemon, to begin, which region would you like to start in?" << std::endl << std::endl;
    std::cout << "1) Kanto" << std::endl;
    std::cout << "2) Johto" << std::endl;
    std::cout << "3) Honen" << std::endl;
    
    int userChoice;
    std::cin >> userChoice;//will either be 1 for Kanto, 2 for Johto, or 3 representing Honen
    
    while(userChoice < 1 || userChoice > 3){//error checking until the user has entered an approporate input
        std::cout << "choice is invalid, please try again" << std::endl;
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
    case 1: kantoStarter(player, kantoNum, kantoDataBase); break;
    case 2: johtoStarter(player, johtoNum, johtoDataBase); break;
    case 3: honenStarter(player, honenNum, honenDataBase); break;
    default: break;
    }
    
    return 0;
}
