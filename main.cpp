#include <iostream>
#include <fstream>
#include <vector>

#include "pokemon.h"
#include "pokedex.h"

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

int getNumberOfLines(std::string filename) {//gets the number of records each region's pokemon has in each file

    std::ifstream f(filename);
    std::string line;
    int count = 0;

    while(getline(f, line)) {
        count++;
    }
    return count;
}

int main() {

    // std::string filename = "./honen_pokemon.txt"; // Linux file name
    std::string filename = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";

    int size = getNumberOfLines(filename);
    std::vector<Pokemon> vec(size);

    readPokemonData(filename, size, vec);

    return 0;
}
