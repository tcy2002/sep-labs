#pragma once

template <typename T> class Stack {
    // TODO
    struct node {
        T val;
        node *next;
        explicit node(T v, node* n=nullptr): val(v), next(n) {}
        ~node() {delete next;}
    };
    node *head;
    int cSize;

 public:
    Stack(): head(nullptr), cSize(0) {
        // TODO
    }
    
    ~Stack() {
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
        head = new node(t, head);
        cSize++;
    }
    
    void pop() {
        // TODO
        node *tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        cSize--;
    }
    
    T& top() const {
        // TODO
        return head->val;
    }

    void reset() {
        if (empty()) return;
        delete head;
        head = nullptr;
    }
};
