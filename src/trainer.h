#ifndef TRAINER_H 
#define TRAINER_H 

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <sstream>
#include <map>

using namespace std;

struct Score {
    int total_words;
    int mistakes;
    string wpm; // Words Per Minute
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
    bool m_timer_on{false};
    
    
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
    void setTimerOn();
    void setTimerOff();
    bool getTimerState();
    void calcWPM(chrono::steady_clock::time_point start, 
                   chrono::steady_clock::time_point end);
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
protected:
    int m_total_index{0};
    vector<int> shuffled_index;
    map<int, int> char_stats; // Key: Character, Value: Number of mistakes

public:
    RandomTrainer(vector<string> &words);
    string selectWords();
    string selectWords(vector<string> &words);
    string getWords();
    bool ended();

};

class SmartTrainer: public RandomTrainer {
private:
    map<int, int> m_char_stats; // Key: Character, Value: Number of mistakes

public:
    SmartTrainer(vector<string> &words);
    string selectWords();
    string selectWords(vector<string> &words);
    string getWords();
    bool ended();
    int getMistakeCount(int ch);
    void setMistakeCount(int ch, int count);
};


#endif