LIBS = -lncurses
CC = g++
FLAGS = -std=c++11 -g
SRC = src/

main: $(SRC)main.cpp
	$(CC) $(SRC)main.cpp -o TypingTrainer $(LIBS) $(FLAGS)
