#ifndef TYPINGTRAINER_H
#define TYPINGTRAINER_H

#include "trainer.h"
#include <ncurses.h>
#include <string>
#include <chrono>

// Define color pair macros
#define WHITE 1
#define RED 2
#define RED_B 3 // Both foreground and background red
#define RED_BG 4 // Just background red
#define GREEN 5
#define GREEN_BG 6 // Just background green


using namespace std;

// Typing Trainer object used to display UI to user and to control logic 
class TT{
private:
    int m_rows{0};
    int m_cols{0};
    WINDOW *m_main_win; // Main window where text is displayed
    WINDOW *m_top_win; // Top bar 
    WINDOW *m_bot_win; // Bottom bar 

    string m_words;
    unsigned int m_index{0};

private:
    void displayWords(int start_row);
    void displayTopBar();
    void displayBotBar(Trainer &trainer);
    int startTimer(Trainer &trainer);
    void incPosition(int ch, Trainer & trainer, int start_row);
    void markChrRed(Trainer &trainer, int color, int start_row);
    void regenWords(Trainer &trainer, chrono::steady_clock::time_point &time, int &start_row, bool &restart_timer);
public:
    TT();
    ~TT();
    int getChr() const;
    void typeMode(Trainer &trainer);
    string getWord(int row, int col);

    int getRows() const;
    int getCols() const;
};

#endif