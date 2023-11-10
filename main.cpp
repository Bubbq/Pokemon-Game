#include <cstdio>
#include <iostream>

// for the pokemon class
#include "pokemon.h"

void clear() {//clear terminal based on OS
#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}


int main() {
    return 0;
}
