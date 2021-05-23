#ifndef TYPINGTRAINER_H
#define TYPINGTRAINER_H

#include <ncurses.h>
#include <string>

// Define color pair macros
#define WHITE 1
#define RED 2
#define RED_B 3


using namespace std;

// Typing Trainer object used to display UI to user and to control logic 
class TT{
private:
    int m_rows{0};
    int m_cols{0};
    string m_words;
    unsigned int m_index{0};

public:
    TT();
    ~TT();
    int getChr() const;
    void typeMode(string words);
    string getWord(int row, int col);
    void displayWords();

    int getRows() const;
    int getCols() const;
};

#endif