#include "trainer.h"

Trainer::Trainer() {}

Trainer::~Trainer() {}

OrderedTrainer::OrderedTrainer(vector<string> words) {
    selectWords(words);
}

string OrderedTrainer::selectWords(vector<string> words) 
{
    // Check if slice indexes outside vector
    vector<string>::iterator end;
    if (m_total_index + MAX_SET_SIZE > words.size()) {
        end = words.end();
        m_set_size = m_total_index + MAX_SET_SIZE - words.size();
    } else {
        end = words.begin() + m_total_index + MAX_SET_SIZE;
    }
    for (auto it = words.begin() + m_total_index; it != end; it++) {
        m_words.append(cleanString(*it));
        m_words.append(" ");
    }
    return m_words;
}

const string OrderedTrainer::cleanString(string str) {
    for (int i = 0; i < sizeof(IGNORED_CHARS)/sizeof(char); i++) {
        str.erase(remove(str.begin(), str.end(), IGNORED_CHARS[i]), str.end());
    }
    return str;
}

string OrderedTrainer::getWords() {
    return m_words;
}