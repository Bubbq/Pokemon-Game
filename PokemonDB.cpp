#include "Pokemon.h"
#include "PokemonDB.h"

// for file reading/manipulation
#include <fstream>
// for use of vector
#include <vector>

// constructor, filenames are passed by GameStart to fill up DB of pokemon
PokemonDB::PokemonDB(std::string honenFilename, std::string kantoFileName, std::string johtoFilename){
    // getDB info of all pokemon
    this->getDBInfo(honenFilename, this->honenDB);
    this->getDBInfo(kantoFileName, this->kantoDB);
    this->getDBInfo(johtoFilename, this->johtoDB);
    this->reigonName = "None";
}

//destructor
PokemonDB::~PokemonDB(){}

// currentReigon
void PokemonDB::setCurrentReigon(std::string reigonName){

    if(reigonName == "Kanto")
        this->currentReigon = this->kantoDB;

    else if(reigonName == "Honen")
        this->currentReigon = this->honenDB;
    
    else if(reigonName == "Johto")
        this->currentReigon = this->johtoDB;
    
    this->reigonName = reigonName;
}

std::vector<Pokemon> PokemonDB::getCurrentReigon(){return this->currentReigon;}

// reigonName
std::string PokemonDB::getReigonName(){return this->reigonName;}

// fill the DB of pokemonInfo
void PokemonDB::getDBInfo(std::string filename, std::vector<Pokemon>& pokemonDB){
     // resize the DB to make it fit
    pokemonDB.resize(9);

    // for handling '_' characters, storing #s, and the iterator
    int check, num;
    // for storing string values
    std::string words;
    
    // for file reading, read the file that was passed
    std::ifstream inFile(filename);

    for(int i  = 0; i < 9; i++){

        // read the pokemon name
        inFile >> words; 
        pokemonDB[i].setName(words);
        // read the evolution stage
        inFile >> num;
        pokemonDB[i].setEvoStage(num);
        // read and store pokemonExp
        inFile >> num;
        pokemonDB[i].setPokemonExp(num);
        // read and store HP
        inFile >> num;
        pokemonDB[i].setHp(num);
        // read baseAttackName
        inFile >> words; 
       
        // check for underscore in attack and replace with ' '
        check = words.find('_');
        if (check != std::string::npos) {
            words[check] = ' ';
            pokemonDB[i].setBaseAttackName(words);
        }

        else 
            pokemonDB[i].setBaseAttackName(words);

        // read and store base attack dmg
        inFile >> num;
        pokemonDB[i].setBaseAttackDmg(num);

        // read heavy attack name
        inFile >> words;
        check = words.find('_');
        if (check != std::string::npos) {
            words[check] = ' ';
            pokemonDB[i].setHeavyAttackName(words);
        }
        else 
            pokemonDB[i].setHeavyAttackName(words);
    
        // read and store heavy attack dmg
        inFile >> num;
        pokemonDB[i].setHeavyAttackDmg(num);
        // read and set type
        inFile >> num;
        pokemonDB[i].setType(num);
        // read and store rarity
        inFile >> num;
        pokemonDB[i].setRarity(num);
    }
    // close file after use
    inFile.close();
}