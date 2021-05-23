#include "words.h"

Words::Words(string &filename): 
    m_filename(filename) 
{
    loadWords(filename);
}

Words::Words(string &filename, int max_size): 
    m_filename(filename) 
{
    loadWords(filename, max_size);
}

/*  Reads words from file and inserts them into m_words.
*
*   Parameters:
*       string &filename: Name of a file to read words from.
*       int max_size: (optional) Max number of words to read 
*                     from file. If max_size is greater than
*                     number of words in file, loadWords reads
*                     all words. If max_size is not set, static
*                     const MAX_SIZE is used.
*       bool append:  (optional, true by default) If true,
*                     append words read from file into m_words.
*                     If false, clear m_words and then read
*                     from file.
*/
void Words::loadWords(string &filename, int max_size, bool append) 
{
    if (!append) {
        m_words.clear();
    }
    ifstream file (filename);
    if (file.is_open()) {
        string line;
        string word;
        int count = 0;
        while (getline(file, line, '\n') && count < max_size) {
            stringstream ss(line);
            while (getline(ss, word, ' ')) {
                m_words.push_back(word);
                count++;
            }
        }
        file.close();
    }
    else {
        throw EOpenFile();
    }
}

/* Print all words stored in m_words.
*  If there are no words, nothing will be sent to
*  output stream.
*/
void Words::print() const 
{
    for (auto &word : m_words) {
        cout << word << endl;
    }
}

int Words::size() const 
{
    return m_words.size();
}