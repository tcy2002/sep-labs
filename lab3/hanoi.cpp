#include <iostream>
#include <string>

#include "board.h"

using namespace std;

int main() {
    while (true) {
        cout << "How many disks do you want? (1 ~ 5)" << endl;
        string input;
        getline(cin, input);
        if (input == "Q") {
            break;
        }
        
        // TODO
        bool notDigit = false;
        for (char i : input) if (!isdigit(i)) notDigit = true;
        int n = strtol(input.c_str(), nullptr, 10);
        if (n < 1 || n > 5 || notDigit) continue;

        Board hanoi(n);
        hanoi.draw();
        while (true) {
            cout << "Move a disk. Format: x y" << endl;
            int x, y;
            cin >> x >> y;
            if (!cin.good()) {
                cin.clear();
                cin.sync();
                hanoi.draw();
                continue;
            }

            if (x == 0 && y == 0)
                hanoi.autoplay();
            else {
                if (x <= 3 && x >= 1 && y <= 3 && y >= 1 && x != y)
                    hanoi.move(x - 1, y - 1);
                hanoi.draw();
            }

            if (hanoi.win()) { cin.get(); break; }
        }
    }
    return 0;
}
