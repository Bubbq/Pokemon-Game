CC = g++
CFLAGS= -Wall -Wextra
SRC = *.cpp
# LIBS =

all:
	$(CC) $(SRC) $(CFLAGS) -o pokemon.o
clean:
	$(RM) *.o
