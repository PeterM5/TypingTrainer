#include "tt.h"
#include <string>
using namespace std;
TT::TT() {
    // initializes the screen
    // sets up memory and clears the screen
    initscr(); // Start curses mode 
    if(has_colors() == FALSE) // Make sure terminal supports colors
	{
        endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
    start_color();
    use_default_colors();
    
    // Define color pairs
    init_pair(WHITE, COLOR_WHITE, -1);
    init_pair(RED, COLOR_RED, -1);
    init_pair(RED_B, COLOR_RED, COLOR_RED);

    raw(); // Ctrl-Z and Ctrl-C are passed directly to program without generating signal.
    noecho(); // We want control over what to display to screen when user is typing.
    keypad(stdscr, TRUE); // Take in arrow keys and Funciton keys as raw input.

    // Get size of terminal screen
    getmaxyx(stdscr,m_rows,m_cols);
}

TT::~TT() {
    endwin(); 
    // deallocates memory and ends ncurses
}

// Obtain a readable character from the user.
int TT::getChr() const {
    int ch = getch();
    if (ch >= 33 && ch <= 126) return ch; // Return alphabetical chars
    // Check for special characters
    if (
        ch == ' ' ||
        ch == '\n'||
        ch == 27 /* escape */
        ) return ch;
    return 0; // Ignore all other characters
}

// Obtain a word from the user
string TT::getWord(int row, int col) {
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

void TT::typeMode(string words) {
    m_words = words;
    displayWords();
    move(m_rows/2, 0);
    int ch = getChr();
    int shift = 0;
    while (ch != 27) { // 27: Escape character
        if (ch == m_words[m_index]) {
            m_index++;
            move(m_rows/2, m_index);
        }
        else {
            if (m_words[m_index] == ' ') {
                attron(COLOR_PAIR(RED_B));
                mvaddch(m_rows/2,m_index,m_words[m_index]);
                move(m_rows/2, m_index);
                attroff(COLOR_PAIR(RED_B));
            } else {
                attron(COLOR_PAIR(RED));
                mvaddch(m_rows/2,m_index,m_words[m_index]);
                move(m_rows/2, m_index);
                attroff(COLOR_PAIR(RED));
            }
        }
        ch = getChr();
    }
}

void TT::displayWords() {
    mvaddstr(m_rows/2, 0, m_words.c_str());
    //mvprintw(m_rows/2, 0, words.c_str());
}

int TT::getRows() const {
    return m_rows;
}

int TT::getCols() const {
    return m_cols;
}