#ifndef POKEMONDB_H
#define POKEMONDB_H

#include "Pokemon.h"
#include <vector>

class PokemonDB{
    
    private:
        // the databases of all the reigons
        std::vector<Pokemon> kantoDB;
        std::vector<Pokemon> honenDB;
        std::vector<Pokemon> johtoDB;

        // the current reigon (with its name) a user is in
        std::vector<Pokemon> currentReigon;
        std::string reigonName;

    public:
        // constructor, filenames are passed by 
        PokemonDB(std::string, std::string, std::string);
        // destructor
        ~PokemonDB();

        // currentReigon
        void setCurrentReigon(std::string);
        std::vector<Pokemon> getCurrentReigon();

        // reigonName
        std::string getReigonName();

        // getting database info
        void getDBInfo(std::string, std::vector<Pokemon>&);

};

#endif