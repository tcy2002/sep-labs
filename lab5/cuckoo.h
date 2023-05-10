#pragma once

#include "iostream"

class cuckooHash {
private:
    struct pair {
        int key;
        int val;
        pair(): key(-1), val(0) {}
        pair(int key, int val): key(key), val(val) {}
        ~pair() = default;
        bool isAvailable() const { return key == -1; }
        void makeEmpty() { key = -1; }
    };

    pair *tab[2]{};
    int size;

    int H1(int key) const { return key % size; }
    int H2(int key) const { return (key / size) % size; }

    void insert(int key, int val);
    void insert(int key, int val, int idx, int depth);
    void resize();

public:
    cuckooHash(): size(8) {
        tab[0] = new pair[8]{};
        tab[1] = new pair[8]{};
    }
    ~cuckooHash() {
        delete []tab[0];
        delete []tab[1];
    }

    void Insert(int key, int val) { insert(key, val); }
    void Lookup(int key);
    void Delete(int key);
};
