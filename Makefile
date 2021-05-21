LIBS = -lncurses
CC = clang++
FLAGS = -std=c++11
SRC = src/

main: $(SRC)main.cpp
	$(CC) $(SRC)main.cpp -o TypingTrainer $(LIBS) $(FLAGS)
