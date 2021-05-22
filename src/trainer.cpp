#include "trainer.h"

Trainer::Trainer() {}

Trainer::~Trainer() {}

OrderedTrainer::OrderedTrainer(vector<string> words) {
    selectWords(words);
}

void OrderedTrainer::selectWords(vector<string> words) 
{
    // Check if slice indexes outside vector
    int start = m_total_index;

    if (m_total_index + MAX_SET_SIZE > words.size()) {
        for (auto it = words.begin() + m_total_index; it != words.end(); it++) {
            m_words.push_back(*it);
        }
/*        std::copy(
            words.begin()+start, 
            words.end(), 
            m_words.begin()
        );*/
        m_set_size = start + MAX_SET_SIZE - words.size();
    } else {
        for (auto it = words.begin() + m_total_index; it != words.begin() + m_total_index + MAX_SET_SIZE; it++) {
            m_words.push_back(*it);
        }
/*        std::copy(
            words.begin()+start, 
            words.begin()+start+MAX_SET_SIZE, 
            m_words.begin()
        );*/
    }
}

vector<string> OrderedTrainer::getWords() {
    return m_words;
}