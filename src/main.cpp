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
    Words words(filename, 30);

    TT tt; // Initialize curses using wrapper
    if (tt.getRows() < 4) throw "Console too small to run Typing Trainer. Console must have at least 4 rows.";

    OrderedTrainer trainer(words.getWords());
    tt.typeMode(trainer.getWords());

  } catch (Words::EOpenFile err) {
    cout << "Open File Error: " << err.what() << endl;
  } catch (char const * errText) {
    cout << errText << endl;
  }

  return 0;
}