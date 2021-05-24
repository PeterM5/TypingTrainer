#ifndef TRAINER_H 
#define TRAINER_H 

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <numeric>

using namespace std;

struct Score {
    int total_words;
    int mistakes;
};

class Trainer {
public: // Public constants
    static const int MAX_SET_SIZE{20};
    const char IGNORED_CHARS[2] {'\n', '\r'};
    
protected:
    vector<string> m_lexicon; // All the inputted words
    string m_words; // The words selected from the lexicon
    u_int8_t m_set_size {MAX_SET_SIZE}; // Actual number of selected words
    bool m_end {false}; // true if there are no more words
    Score m_score;
    
    
public:
    Trainer();
    virtual ~Trainer();
    virtual string selectWords()=0;
    virtual string selectWords(vector<string> &words)=0;
    virtual string getWords()=0;
    virtual bool ended()=0;

    const string cleanString(string str);
    const Score getScore() const;
    void setScore(Score score);
    void incWordsScore();
    void incMistakesScore();

};

class OrderedTrainer: public Trainer {
private:
    int m_total_index{0};

public:
    OrderedTrainer(vector<string> &words);
    string selectWords();
    string selectWords(vector<string> &words);
    string getWords();
    bool ended();

};

class RandomTrainer: public Trainer {
private:
    int m_total_index{0};
    vector<int> shuffled_index;

public:
    RandomTrainer(vector<string> &words);
    string selectWords();
    string selectWords(vector<string> &words);
    string getWords();
    bool ended();

};

#endif