#pragma once

#include <iostream>

using namespace std;

class Canvas {
    static const int HEIGHT = 11, WIDTH = 41;
    char buffer[HEIGHT][WIDTH]{};
    int pos[3]{};

public:
    Canvas() {
        reset();
        for (auto & i : buffer[HEIGHT - 1])
            i = '-';
        for (auto & i : buffer)
            i[5] = i[20] = i[35] = '|';
    }

    void insert(int rod, int size) {
        int start = 15 * rod + 5 - size / 2;
        int end = start + size - 1;
        for (int i = start; i <= end; i++)
            buffer[pos[rod]][i] = '*';
        pos[rod] -= 2;
    }

    void draw() const {
        for (const auto & i : buffer) {
            for (char j : i)
                cout << j;
            cout << endl;
        }
    }
    
    void reset() {
        for (auto & i : buffer)
            for (char & j : i)
                j = ' ';
        pos[0] = pos[1] = pos[2] = 9;
    }
};