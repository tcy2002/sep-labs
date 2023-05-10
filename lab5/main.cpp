#include "cuckoo.h"
#include <cstring>

void input_test() {
    int num, key, val;
    char buf[7]{};
    cuckooHash c;

    std::cin >> num;
    while (num-- > 0) {
        std::cin >> buf >> key;
        if (strncmp(buf, "Insert", 6) == 0) {
            std::cin >> val;
            c.Insert(key, val);
        } else if (strncmp(buf, "Lookup", 6) == 0)
            c.Lookup(key);
        else if (strncmp(buf, "Delete", 6) == 0)
            c.Delete(key);
        else
            throw std::runtime_error("input error");
    }
}

int main() {
    input_test();
//    cuckooHash c;
//    c.Insert(16, 0);
//    c.Insert(80, 1);
//    c.Lookup(16);
//    c.Lookup(17);
//    c.Insert(144, 2);
    return 0;
}