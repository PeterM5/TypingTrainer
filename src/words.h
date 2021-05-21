#ifndef WORDS_H
#define WORDS_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class Words {
private: // Private Constants
    const static int MAX_SIZE{16777215}; //2^24 - 1

private: // Private Member vartiables
    vector<string> m_words;
    string m_filename;

public:
    Words() = default;
    Words(string &filename);
    Words(string &filename, int max_size);
    void print() const;
    int size() const;
    void makeUnique(bool saveNew);
    void loadWords(string &filename, int max_size=MAX_SIZE, bool append=true);
    // Add function to remove all duplicates from words

};

#endif