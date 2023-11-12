#include <cstdio>
#include <iostream>

// for the pokemon class
#include "Backpack.h"
#include "GameStart.h"
#include "Pokemon.h"
#include "PokemonDB.h"
#include "Trainer.h"

// to clear terminal based on OS
void clear() {
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}


int main() {
    GameStart g;
    Trainer  t;
    g.startGame(t);

    return 0;
    
    }
