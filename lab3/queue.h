#include <iostream>

template <typename T> class Queue {
    // TODO
    struct node {
        T val;
        node* next;
        explicit node(T v, node* n=nullptr): val(v), next(n) {}
        ~node() {delete next;}
    };
    node *head;
    node *tail;
    int cSize;

public:
    Queue(): tail(nullptr), head(nullptr), cSize(0) {
        // TODO
    }

    ~Queue() {
        // TODO
        delete head;
    }

    int size() const {
        // TODO
        return cSize;
    }

    bool empty() const {
        return size() == 0;
    }

    void push(T t) {
        // TODO
        if (empty()) head = tail = new node(t);
        else tail = tail->next = new node(t);
        cSize++;
    }

    void pop() {
        // TODO
        if (empty()) return;
        node* tmp = head;
        head = head->next;
        if (head == nullptr) tail = head;
        tmp->next = nullptr;
        delete tmp;
        cSize--;
    }

    T& front() const {
        // TODO
        if (empty()) throw "empty queue";
        return head->val;
    }

    T& back() const {
        // TODO
        if (empty()) throw "empty queue";
        return tail->val;
    }

    void reset() {
        if (empty()) return;
        delete head;
        head = tail = nullptr;
    }
};