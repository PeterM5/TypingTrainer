#include "words.cpp"
#include "tt.cpp"
#include "trainer.cpp"
#include <iostream>
using namespace std;
int main(int argc, char ** argv)
{

  // Load words into memory
  try {
    string filename = "words.csv";
    Words words(filename, 15);

    TT tt; // Initialize curses using wrapper
    if (tt.getRows() < 4) throw "Console too small to run Typing Trainer. Console must have at least 4 rows.";

    RandomTrainer trainer(words.m_words);
    tt.typeMode(trainer);

  } catch (Words::EOpenFile err) {
    cout << "Open File Error: " << err.what() << endl;
  } catch (char const * errText) {
    cout << errText << endl;
  }

  return 0;
}