#pragma once

#include "stack.h"
#include "queue.h"

class Board {
    // TODO
    struct step {
        int from;
        int to;
        step(int f, int t): from(f), to(t) {}
        ~step()=default;
    };
    int num;
    Stack<int> rod[3];
    Stack<step> stepsLog;
    Queue<step> stepsForward;

    void hanoi(int size, int a, int b, int c);

public:
    explicit Board(int num_disk);
    ~Board();
    void draw();
    void move(int from, int to, bool log = true);
    bool win();
    void autoplay();
};
