CC = g++
CFLAGS= -Wall -Wextra
SRC = *.cpp
# LIBS = -lSDL2

all:
	$(CC) $(SRC) $(CFLAGS) -o pokemon.o
clean:
	$(RM) *.o
