CC = g++
CFLAGS= -Wall -Wextra
SRC = *.cpp
# LIBS =

all:
	$(CC) $(SRC) $(CFLAGS) -o pokemon
clean:
	$(RM) pokemon
run: all
	./pokemon
