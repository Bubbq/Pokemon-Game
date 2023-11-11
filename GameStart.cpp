#include "GameStart.h"
#include "PokemonDB.h"
#include <string>

// constructor
GameStart::GameStart(){
   
    this->pokemonDB = new PokemonDB(this->honenFilename, this->kantoFilename, this->johtoFilename);
   
}

GameStart::~GameStart(){}



