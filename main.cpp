#include <cstdio>
#include <iostream>

// for the pokemon class
#include "Backpack.h"
#include "GameStart.h"
#include "Pokemon.h"
#include "PokemonDB.h"
#include "Trainer.h"

int main() {
    
    GameStart g;
    Trainer  t;
    g.startGame(t);

    return 0;
    
}
