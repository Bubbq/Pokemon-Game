#include <iostream>
#include <fstream>
#include <vector>

#include "pokemon.h"
#include "pokedex.h"

void readPokemonData(std::string filename, int size, std::vector<Pokemon> &vec) {

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

int getNumberOfLines(std::string filename) {

    std::ifstream f(filename);
    std::string line;
    int count = 0;

    while(getline(f, line)) {
        count++;
    }
    return count;
}

int main() {

    std::string filename = "./honen_pokemon.txt";
    // std::string filename = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";

    int size = getNumberOfLines(filename);
    std::vector<Pokemon> vec(size);

    readPokemonData(filename, size, vec);

    return 0;
}
