#include <iostream>
#include<fstream>
#include <string>
#include<cstdlib>
#include "Pokemon.h"
#include "Pokedex.h"

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

int getNumberOfRecords(char filename[]){//gets the number of records each region's pokemon has in each file

    std::ifstream inFile;
    inFile.open(filename);
    char helper[1000];
    int counter = 0;

        while(!inFile.eof()){
            inFile.getline(helper, 1000);
            counter++;
        }

    return counter;

    }

void readPokemonDataBase(char filename[], Pokemon*&arr){//reads all the info of pokemon in a region

        int N = getNumberOfRecords(filename);
        int index = 0;

        int helper;

        char nameHelper[100];
        char base_attack_nameHelper[100];
        char heavy_attack_helper[100];

        std::ifstream inFile;
        inFile.open(filename);

        while(index < N - 1){

            inFile.getline(nameHelper, 100);
            arr[index].Setname(nameHelper);

            inFile >> helper;
            arr[index].SetevoStage(helper);

            inFile >> helper;
            arr[index].Sethp(helper);

            inFile.getline(base_attack_nameHelper, 100);
            arr[index].Setname(base_attack_nameHelper);

            inFile >> helper;
            arr[index].Setbase_attack_dmg(helper);

            inFile.getline(heavy_attack_helper, 100);
            arr[index].Setname(heavy_attack_helper);

            inFile >> helper;
            arr[index].Setheavy_attack_dmg(helper);

            inFile >> helper;
            arr[index].SetType(helper);


            arr[index].print();

            index++;

        }
    inFile.close();
    }




int main()
{

    char filename[] = "C:\\Users\\nemoq\\codeblocks\\Pokemon Personal Project\\honen_pokemon.txt";

    int num = getNumberOfRecords(filename);

    Pokemon * arr = new Pokemon [num];

    readPokemonDataBase(filename, arr);







    return 0;
}
