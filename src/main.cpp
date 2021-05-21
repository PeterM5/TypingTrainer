#include "words.cpp"
#include "ncWrapper.cpp"

int main(int argc, char ** argv)
{

  // Load words into memory
  try {
    string filename = "words.csv";
    Words words(filename, 10);

    NCWrapper ncw; // Initialize curses using wrapper
    if (ncw.getRows() < 4) throw "Console too small to run Typing Trainer. Console must have at least 4 rows.";
    string word = ncw.getWord(ncw.getRows()/2 + 1, ncw.getCols()/2);
    mvprintw(ncw.getRows()/2, ncw.getCols()/2, word.c_str());
    getch();



  } catch (Words::EOpenFile err) {
    cout << "Open File Error: " << err.what() << endl;
  } catch (char const * errText) {
    cout << errText << endl;
  }

  return 0;
}


