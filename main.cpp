#include <cstdio>
#include <iostream>

// for the pokemon class
#include "Pokemon.h"
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
    Trainer t;

    t.showStats();

    return 0;
}
