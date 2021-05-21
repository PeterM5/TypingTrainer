#include "ncWrapper.h"
#include <string>
using namespace std;
NCWrapper::NCWrapper() {
    // initializes the screen
    // sets up memory and clears the screen
    initscr(); // Start curses mode 
    raw(); // Ctrl-Z and Ctrl-C are passed directly to program without generating signal.
    noecho(); // We want control over what to display to screen when user is typing.
    keypad(stdscr, TRUE); // Take in arrow keys and Funciton keys as raw input.

    // Get size of terminal screen
    getmaxyx(stdscr,m_rows,m_cols);
}

NCWrapper::~NCWrapper() {
    endwin(); 
    // deallocates memory and ends ncurses
}

// Obtain a readable character from the user.
int NCWrapper::getChr() const {
    int ch = getch();
    if (ch >= 33 && ch <= 126) return ch;
    else {
        // Check for special characters
        if (
            ch == ' ' ||
            ch == '\n'||
            ch == 127 || /* backspace*/
            ch == 27 /* escape */
            ) return ch;
        else return 0;
    }
}

// Obtain a word from the user
string NCWrapper::getWord(int row, int col) {
    move(row, col);
    string word;
    int ch = getChr();
    int count = 0;
    while (ch && ch != ' ' && ch != '\n') {
        if (ch == 127) { // backspace
            if (count > 0) {
                word.pop_back();
                count--;
                mvaddch(row, col + count, ' '); // Remove character from screen
                move(row, col + count);
            }
            ch = getChr();
        } else {
            word.push_back(ch);
            addch(ch); // addch() advances cursor for us
            count++;
            ch = getChr();
        }
    }
    return word;
}

int NCWrapper::getRows() const {
    return m_rows;
}

int NCWrapper::getCols() const {
    return m_cols;
}