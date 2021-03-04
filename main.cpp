#include <ncurses.h>
using namespace std;



int main(int argc, char ** argv)
{
  // initializes the screen
  // sets up memory and clears the screen
  initscr();  

	mvprintw(10,10,"yo");	

  // refreshes the screen to match whats in memory
  //refresh();

	while (true) {
		getch();
	}

  endwin(); 
  // deallocates memory and ends ncurses

  return 0;
}


