#ifndef POKEMONDB_H
#define POKEMONDB_H

#include "Pokemon.h"
#include <string>
#include <vector>

class PokemonDB{
    
    private:
    
    // the databases of all the reigons
    std::vector<Pokemon> kantoDB;
    std::vector<Pokemon> honenDB;
    std::vector<Pokemon> johtoDB;

    std::vector<Pokemon> currentReigon;

    public:

    // constructor, filenames are passed by 
    PokemonDB(std::string, std::string, std::string);
    // destructor
    ~PokemonDB();

    // setters and getters

    // currentReigon
    void setReigon(std::string);
    std::vector<Pokemon> getReigon();

    // getting database info
    void getDBInfo(std::string, std::vector<Pokemon>&);

};

#endif