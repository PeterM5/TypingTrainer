#ifndef TRAINER_H 
#define TRAINER_H 

#include <vector>
#include <string>
#include <cstdint>

using namespace std;

class Trainer {
public:
    static int const MAX_SET_SIZE{10};
    
protected:
    vector<string> m_words;
    u_int8_t m_index{0};
    u_int8_t m_set_size{MAX_SET_SIZE};
    
public:
    Trainer();
    virtual ~Trainer();
    virtual void selectWords(vector<string> words)=0;
    virtual vector<string> getWords()=0;
};

class OrderedTrainer: public Trainer {
private:
    int m_total_index{0};

public:
    OrderedTrainer(vector<string> words);
    void selectWords(vector<string> words);
    vector<string> getWords();
};
#endif