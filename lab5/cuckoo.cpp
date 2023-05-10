#include "cuckoo.h"


void cuckooHash::insert(int key, int val) {
    int k1{H1(key)}, k2{H2(key)};
    if (tab[0][k1].isAvailable() || tab[0][k1].key == key) {
        tab[0][k1] = {key, val};
        return;
    }
    if (tab[1][k2].isAvailable() || tab[1][k2].key == key) {
        tab[1][k2] = {key, val};
        return;
    }
    insert(key, val, 0, 0);
}

void cuckooHash::insert(int key, int val, int idx, int depth) {
    if (depth >= 2 * size) {
        std::cout << "Loop Detect" << std::endl;
        resize();
        insert(key, val);
        return;
    }

    int k{idx ? H2(key) : H1(key)};
    int key_tmp;
    int val_tmp;

    if (tab[idx][k].isAvailable()) {
        tab[idx][k] = {key, val};
        return;
    }

    key_tmp = tab[idx][k].key;
    val_tmp = tab[idx][k].val;
    std::cout << "Kick " << key_tmp << " with " << key <<
              " in table " << idx << " " << k << std::endl;

    tab[idx][k] = {key, val};
    insert(key_tmp, val_tmp, !idx, ++depth);
}

void cuckooHash::Lookup(int key) {
    int k1{H1(key)}, k2{H2(key)};
    if (tab[0][k1].key == key) std::cout << tab[0][k1].val << std::endl;
    else if (tab[1][k2].key == key) std::cout << tab[1][k2].val << std::endl;
    else std::cout << "Key Not Found" << std::endl;
}

void cuckooHash::Delete(int key) {
    int k1{H1(key)}, k2{H2(key)};
    if (tab[0][k1].key == key) tab[0][k1].makeEmpty();
    else if (tab[1][k2].key == key) tab[1][k2].makeEmpty();
    else std::cout << "Key Not Found" << std::endl;
}

void cuckooHash::resize() {
    size *= 2;
    auto tmp0 = tab[0];
    auto tmp1 = tab[1];
    tab[0] = new pair[size]{};
    tab[1] = new pair[size]{};

    int i;
    for (i = 0; i < size / 2; i++)
        if (!tmp0[i].isAvailable())
            insert(tmp0[i].key, tmp0[i].val);
    for (i = 0; i < size / 2; i++)
        if (!tmp1[i].isAvailable())
            insert(tmp1[i].key, tmp1[i].val);
}
