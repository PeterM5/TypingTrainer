#ifndef TRAINER_H 
#define TRAINER_H 

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

using namespace std;

class Trainer {
public: // Public constants
    static const int MAX_SET_SIZE{10};
    const char IGNORED_CHARS[2] {'\n', '\r'};
    
protected:
    vector<string> m_lexicon; // All the inputted words
    string m_words; // The words selected from the lexicon
    u_int8_t m_set_size {MAX_SET_SIZE}; // Actual number of selected words
    bool m_end {false}; // true if there are no more words
    
public:
    Trainer();
    virtual ~Trainer();
    virtual string selectWords(vector<string> &words)=0;
    virtual string getWords()=0;
    virtual bool ended()=0;
};

class OrderedTrainer: public Trainer {
private:
    int m_total_index{0};

public:
    OrderedTrainer(vector<string> &words);
    string selectWords();
    string selectWords(vector<string> &words);
    string getWords();
    const string cleanString(string str);
    bool ended();

};
#endif