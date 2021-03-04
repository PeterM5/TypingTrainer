LIBS = "-lncurses"

main: main.cpp
	$(CC) $(LIBS) main.cpp -o TypingTrainer
