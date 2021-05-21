#include <ncurses.h>
#include "words.cpp"

int main(int argc, char ** argv)
{
  // initializes the screen
  // sets up memory and clears the screen
  /*
  initscr(); // Start curses mode 
	raw(); // Ctrl-Z and Ctrl-C are passed directly to program without generating signal.
	noecho(); // We want control over what to display to screen when user is typing.
	keypad(stdscr, TRUE); // Take in arrow keys and Funciton keys as raw input.



	printw("Hello World !!!");
	refresh();
  getch();

  endwin(); 
  // deallocates memory and ends ncurses
  */

  string filename = "words.csv";
  Words w;
  cout << w.size() << endl;
  w.size();
  w.print();

  return 0;
}


