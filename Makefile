LIBS = -lncurses
CC = clang++
FLAGS = -std=c++11
SRC = src/

main: $(SRC)TypingTrainer.cpp
	$(CC) $(SRC)TypingTrainer.cpp -o TypingTrainer $(LIBS) $(FLAGS)
