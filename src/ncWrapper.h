#ifndef NCWRAPPER_H
#define NCWRAPPER_H

#include <ncurses.h>
#include <string>

using namespace std;

// nCurses Wrapper
class NCWrapper {
private:
    int m_rows{0};
    int m_cols{0};

public:
    NCWrapper();
    ~NCWrapper();
    int getChr() const;
    string getWord(int row, int col);
    void displayWords(vector<string> words);

    int getRows() const;
    int getCols() const;
};

#endif