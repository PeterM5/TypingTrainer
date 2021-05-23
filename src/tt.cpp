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


void TT::typeMode(Trainer &trainer) {
    m_words = trainer.getWords();
    int start_row = m_rows/2 + m_words.size()/(m_cols*2);
    displayWords(start_row);
    move(start_row, 0);
    int ch = getChr();
    int color = RED;
    bool end = false;

    while (ch != 27 && !end) { // 27: Escape character
        if (ch == m_words[m_index]) { // User types correct character
            // Continue
            m_index++;
            move(start_row + m_index/m_cols, m_index%m_cols);
        }
        else { // If user does not type correct character
            // We dont continue until user types correct character
            if (m_words[m_index] == ' ') { // Color space red (set background red)
                color = RED_B;
            } else { // Color character red
                color = RED;
            }
            attron(COLOR_PAIR(color));
            mvaddch(start_row + m_index/m_cols,m_index%m_cols,m_words[m_index]);
            move(start_row + m_index/m_cols, m_index%m_cols);
            attroff(COLOR_PAIR(color));
        }
        if (m_index == m_words.size()) { // Reached the end, generate new words 
            if (!trainer.ended()) {
                m_words = trainer.selectWords();
                clear(); // clear screen
                m_index = 0;
                int start_row = m_rows/2 + m_words.size()/(m_cols*2);
                displayWords(start_row);
                move(start_row, 0);
            } else end = true;
        }
        ch = getChr();
    }
}

void TT::displayWords(int start_row) {
    mvaddstr(start_row, 0, m_words.c_str());
    //mvprintw(m_rows/2, 0, words.c_str());
}

int TT::getRows() const {
    return m_rows;
}

int TT::getCols() const {
    return m_cols;
}