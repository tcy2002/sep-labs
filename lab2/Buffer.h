#pragma once

#include <string>

using std::string;

template<class T>
class linkList
{
private:
    struct node
    {
        T data;
        node *next;
        explicit node(const T &d, node *n=NULL):data(d), next(n){}
        node():next(NULL){}
        ~node()= default;
    };
    node *head;
    int cLength;
    node *move(int i) const;
public:
    linkList(){head = new node; cLength = 0;}
    ~linkList() {
        node *p = head->next;
        while (p != NULL){
            node *q = p;
            p = p->next;
            delete q;
        }
        delete head;
    }
    void clear();
    void add(const T &x);
    void insert(int i, const T &x);
    void remove(int i);
    int search(const T &x) const;
    T visit(int i) const;
    long long traverse(const string &filename) const;
    int getLength() const;
};

class Buffer {
private:
    int currentLineNum{};
    // TODO: add a List here for storing the input lines
    linkList<string> lines;

public:
    Buffer() = default;
    ~Buffer() = default;

    void writeToFile(const string &filename) const;

    string moveToLine(int idx);

    void showLines(int from, int to);

    void deleteLines(int from, int to);
    void insertLine(const string &text);
    void appendLine(const string &text);
    int getLength() const;
};
