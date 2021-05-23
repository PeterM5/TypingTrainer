#include "trainer.h"

Trainer::Trainer() {}

Trainer::~Trainer() {}

const string Trainer::cleanString(string str) {
    for (int i = 0; i < sizeof(IGNORED_CHARS)/sizeof(char); i++) {
        str.erase(remove(str.begin(), str.end(), IGNORED_CHARS[i]), str.end());
    }
    return str;
}

OrderedTrainer::OrderedTrainer(vector<string> &words) {
    m_lexicon = words;
    selectWords();
}

string OrderedTrainer::selectWords() {
    return selectWords(m_lexicon);
}


string OrderedTrainer::selectWords(vector<string> &words) 
{
    // If m_words is not empty, make empty
    if (m_words.size() > 0){
        m_words.erase();
    }

    // Check if we have reached the end
    if (!m_end) {
        // Check if slice indexes outside vector
        vector<string>::iterator end;
        if (m_total_index + MAX_SET_SIZE > words.size()) {
            end = words.end();
            m_set_size = m_total_index + MAX_SET_SIZE - words.size();
            m_end = true; // We have reached the end, there are no more words.
        } else {
            end = words.begin() + m_total_index + MAX_SET_SIZE;
        }
        for (auto it = words.begin() + m_total_index; it != end; it++) {
            m_words.append(cleanString(*it));
            m_words.append(" ");
        }
        m_total_index += MAX_SET_SIZE;
    }
    return m_words;
}

string OrderedTrainer::getWords() {
    return m_words;
}

bool OrderedTrainer::ended() {
    return m_end;
}

RandomTrainer::RandomTrainer(vector<string> &words) {
    shuffled_index.resize(words.size());
    iota(shuffled_index.begin(), shuffled_index.end(), 0);
    random_shuffle(shuffled_index.begin(), shuffled_index.end());
    m_lexicon = words;
    selectWords();
}

string RandomTrainer::selectWords() {
    return selectWords(m_lexicon);
}


string RandomTrainer::selectWords(vector<string> &words) 
{
    // If m_words is not empty, make empty
    if (m_words.size() > 0){
        m_words.erase();
    }

    // Check if we have reached the end
    if (!m_end) {
        // Check if slice indexes outside vector
        vector<int>::iterator end;
        if (m_total_index + MAX_SET_SIZE > shuffled_index.size()) {
            end = shuffled_index.end();
            m_set_size = m_total_index + MAX_SET_SIZE - shuffled_index.size();
            m_end = true; // We have reached the end, there are no more words.
        } else {
            end = shuffled_index.begin() + m_total_index + MAX_SET_SIZE;
        }
        for (auto it = shuffled_index.begin() + m_total_index; it != end; it++) {
            m_words.append(cleanString(words[*it]));
            m_words.append(" ");
        }
        m_total_index += MAX_SET_SIZE;
    }
    return m_words;
}

string RandomTrainer::getWords() {
    return m_words;
}

bool RandomTrainer::ended() {
    return m_end;
}