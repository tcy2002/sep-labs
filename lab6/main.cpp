#include <iostream>
#include "lexicon.h"

using namespace std;

int main() {
    Lexicon l("../EnglishWords.txt");

    cout << l.contains("obey") << endl;

    return 0;
}