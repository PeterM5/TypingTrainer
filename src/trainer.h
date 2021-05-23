#ifndef TRAINER_H 
#define TRAINER_H 

#include <vector>
#include <string>
#include <cstdint>
#include <algorithm>

using namespace std;

class Trainer {
public: // Public constants
    static const int MAX_SET_SIZE{30};
    const char IGNORED_CHARS[2] {'\n', '\r'};
    
protected:
    string m_words;
    u_int8_t m_set_size{MAX_SET_SIZE};
    
public:
    Trainer();
    virtual ~Trainer();
    virtual string selectWords(vector<string> words)=0;
    virtual string getWords()=0;
};

class OrderedTrainer: public Trainer {
private:
    int m_total_index{0};

public:
    OrderedTrainer(vector<string> words);
    string selectWords(vector<string> words);
    string getWords();
    const string cleanString(string str);

};
#endif