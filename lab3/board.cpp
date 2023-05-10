#include "board.h"
#include "canvas.h"

Board::Board(int num_disk): num(num_disk) {
    // TODO
    int size = 2 * num_disk + 1;
    while (num_disk--) {
        rod[0].push(size);
        size -= 2;
    }
}

Board::~Board()=default;

void Board::draw() {
    Canvas canvas;
    
    // TODO
    Stack<int> tmp;
    for (int i = 0; i < 3; i++) {
        while (!rod[i].empty()) {
            tmp.push(rod[i].top());
            rod[i].pop();
        }

        while (!tmp.empty()) {
            int n = tmp.top();
            rod[i].push(n);
            canvas.insert(i, n);
            tmp.pop();
        }
    }

    canvas.draw();
}

void Board::move(int from, int to, bool log) {
    // TODO
    if (rod[from].empty()) return;
    if (!rod[to].empty() && rod[from].top() > rod[to].top()) return;
    rod[to].push(rod[from].top());
    rod[from].pop();
    if (log) stepsLog.push({from, to});
}

bool Board::win() {
    // TODO
    if (rod[0].empty() && rod[2].empty()) {
        cout << "Congratulations! You win!" << endl;
        rod[1].reset();
        return true;
    }
    return false;
}

void Board::autoplay() {
    // TODO
    while (!stepsLog.empty()) {
        step &st = stepsLog.top();
        cout << "Auto moving:" << st.to + 1 << "->" << st.from + 1 << endl;
        move(st.to, st.from, false);
        draw();
        stepsLog.pop();
    }

    stepsForward.reset();
    hanoi(num, 0, 1, 2);
    while (!stepsForward.empty()) {
        step &st = stepsForward.front();
        cout << "Auto moving:" << st.from + 1 << "->" << st.to + 1 << endl;
        move(st.from, st.to, false);
        draw();
        stepsForward.pop();
    }
}

void Board::hanoi(int size, int a, int b, int c) {
    if (size == 0) return;
    hanoi(size - 1, a, c, b);
    stepsForward.push({a, b});
    hanoi(size - 1, c, b, a);
}
