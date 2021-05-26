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
    init_pair(RED_BG, -1, COLOR_RED);
    init_pair(GREEN, COLOR_GREEN, -1);
    init_pair(GREEN_BG, -1, COLOR_GREEN);


    raw(); // Ctrl-Z and Ctrl-C are passed directly to program without generating signal.
    noecho(); // We want control over what to display to screen when user is typing.
    keypad(stdscr, TRUE); // Take in arrow keys and Funciton keys as raw input.

    // Get size of terminal screen
    getmaxyx(stdscr,m_rows,m_cols);

    // Initalize windows
    m_main_win = newwin(m_rows-2, m_cols,1,0);
    m_top_win = newwin(1, m_cols, 0,0);
    m_bot_win = newwin(1, m_cols, m_rows-1,0);

}


TT::~TT() {
    delwin(m_bot_win);
    delwin(m_top_win);
    delwin(m_main_win);
    endwin(); 
    // deallocates memory and ends ncurses
}


// Obtain a readable character from the user.
int TT::getChr() const {
    int ch = wgetch(m_main_win);
    if (ch >= 33 && ch <= 126) return ch; // Return alphabetical chars
    // Check for special characters
    if (
        ch == ' ' ||
        ch == '\n'||
        ch == 27 /* escape */
        ) return ch;
    return 0; // Ignore all other characters
}

int TT::getInput(Trainer &trainer) {
    int ch = getChr();
    if (!trainer.getTimerState()) {
        trainer.setTimerOn();
        displayBotBar(trainer);
    }
    return ch;
}

// Increment position
void TT::incPosition(int ch, Trainer & trainer, int start_row) {
    if (ch == ' ') {
        trainer.incWordsScore();
        displayBotBar(trainer);
    }
    // Continue
    m_index++;
    wmove(m_main_win, start_row + m_index/m_cols, m_index%m_cols);
}

void TT::markChrRed(Trainer &trainer, int color, int start_row) {
    trainer.incMistakesScore();
    displayBotBar(trainer);
    // We dont continue until user types correct character
    if (m_words[m_index] == ' ') { // Color space red (set background red)
        color = RED_B;
    } else { // Color character red
        color = RED;
    }
    wattron(m_main_win, COLOR_PAIR(color));
    mvwaddch(m_main_win, start_row + m_index/m_cols,m_index%m_cols,m_words[m_index]);
    wmove(m_main_win, start_row + m_index/m_cols, m_index%m_cols);
    wrefresh(m_main_win);
    wattroff(m_main_win, COLOR_PAIR(color));

}

// Generate and display a new set of words. Also stop timer. 
void TT::regenWords(Trainer &trainer, chrono::steady_clock::time_point &time, int &start_row, bool &restart_timer) {
    trainer.setTimerOff();
    trainer.calcWPM(time, chrono::steady_clock::now());
    displayBotBar(trainer);
    if (!trainer.ended()) {
        m_words = trainer.selectWords();
        clear(); // clear screen
        m_index = 0;
        start_row = (m_rows-2)/2 - m_words.size()/(m_cols*2); // m_rows - 2 becuase we loose two rows to top and bottom bars
        displayWords(start_row);
        wmove(m_main_win, start_row, 0);
        restart_timer = true;
    }
}

void TT::typeMode(Trainer &trainer) {
    int color; // Initalize color
    m_words = trainer.getWords();
    int start_row = (m_rows-2)/2 - m_words.size()/(m_cols*2); // m_rows - 2 becuase we loose two rows to top and bottom bars
    displayTopBar();
    displayBotBar(trainer);
    displayWords(start_row);
    wmove(m_main_win, start_row, 0);

    int ch = getInput(trainer); // Also displays timer as ON
    chrono::steady_clock::time_point time = chrono::steady_clock::now();
    bool restart_timer = false; // when we reach the end of a set of words, restart_timer is set to true

    while (ch != 27 && !trainer.ended()) { // 27: Escape character
        if (ch == m_words[m_index]) { // User types correct character
            incPosition(ch, trainer, start_row);
        }
        else { // If user does not type correct character
            markChrRed(trainer, color, start_row);
        }

        if (m_index == m_words.size()) { // Reached the end, generate new set of words 
            regenWords(trainer, time, start_row, restart_timer);
        }
        ch = getInput(trainer);
        if (restart_timer) {
            time = chrono::steady_clock::now();
            restart_timer = false; // We have started a new set of words, set back to false.
        }
    }
}


void TT::displayWords(int start_row) {
    wclear(m_main_win);
    mvwaddstr(m_main_win, start_row, 0, m_words.c_str());
    wrefresh(m_main_win);
    //mvprintw(m_rows/2, 0, words.c_str());
}


void TT::displayTopBar() {
    string title = "Typing Trainer";
    mvwaddstr(m_top_win, 0, (m_cols - title.size())/2, title.c_str());
    wrefresh(m_top_win);
}


void TT::displayBotBar(Trainer &trainer) {
    wclear(m_bot_win);

    // Dispaly if timer is active
    string timer_text = "Timer: ";
    mvwaddstr(m_bot_win, 0, 1, timer_text.c_str());
    if (trainer.getTimerState()) {
        wattron(m_bot_win, COLOR_PAIR(GREEN_BG));
            mvwaddstr(m_bot_win, 0, 1+timer_text.size(), "ON");
        wattroff(m_bot_win, COLOR_PAIR(GREEN_BG));
    } else {
        wattron(m_bot_win, COLOR_PAIR(RED_BG));
            mvwaddstr(m_bot_win, 0, 1+timer_text.size(), "OFF");
        wattroff(m_bot_win, COLOR_PAIR(RED_BG));
    }

    // Draw Words Per Minute
    string wpm = "WPM: ";
    wpm.append(trainer.getScore().wpm);
    mvwaddstr(m_bot_win, 0, 2*(m_cols - wpm.size())/6, wpm.c_str());

    // Draw total words count
    wattron(m_bot_win, COLOR_PAIR(GREEN));
        string total = "Words typed: ";
        total.append(to_string(trainer.getScore().total_words));
        mvwaddstr(m_bot_win, 0, 4*(m_cols - total.size())/6, total.c_str());
    wattroff(m_bot_win, COLOR_PAIR(GREEN));

    // Draw mistake count
    wattron(m_bot_win, COLOR_PAIR(RED));
        string mistakes = "mistakes: ";
        mistakes.append(to_string(trainer.getScore().mistakes));
        mvwaddstr(m_bot_win, 0, 6 * (m_cols - total.size())/6, mistakes.c_str());
    wattroff(m_bot_win, COLOR_PAIR(RED));

    wrefresh(m_bot_win);
}


int TT::getRows() const {
    return m_rows;
}


int TT::getCols() const {
    return m_cols;
}