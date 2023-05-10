#include <fstream>
#include <iostream>
#include "Buffer.h"

//TODO: your code here
//implement the functions in ListBuffer
template<class T>
void linkList<T>::clear()
{
    node *p = head->next;
    while (p != NULL){
        node *q = p;
        p = p->next;
        delete q;
    }
    cLength = 0;
}

template<class T>
void linkList<T>::add(const T &x)
{
    node *p = move(cLength - 1);
    p->next = new node(x);
    cLength++;
}

template<class T>
void linkList<T>::insert(int i, const T &x)
{
    node *p = move(i - 1);
    p->next = new node(x, p->next);
    cLength++;
}

template<class T>
void linkList<T>::remove(int i)
{
    node *p = move(i - 1), *q = p->next;
    p->next = p->next->next;
    delete q;
    cLength--;
}

template<class T>
int linkList<T>::search(const T &x) const
{
    node *p = head->next;
    int i = 0;
    while (p != NULL && p->data != x) {p = p->next; i++;}
    if (p == NULL) return -1; else return i;
}

template<class T>
T linkList<T>::visit(int i) const
{
    return move(i)->data;
}

template<class T>
typename linkList<T>::node *linkList<T>::move(int i) const
{
    node *p = head;
    while (i-- > -1) p = p->next;
    return p;
}

template<class T>
long long linkList<T>::traverse(const string &filename) const {
    std::ofstream out(filename);
    node *p = head;
    long long bytes{};
    while ((p = p->next) != NULL) {
        out << p->data << std::endl;

    }
    bytes = out.tellp();
    out.close();
    return bytes;
}

template<class T>
int linkList<T>::getLength() const {
    return cLength;
}

void Buffer::writeToFile(const string &filename) const {
    long long bytes = lines.traverse(filename);
    std::cout << bytes << " byte(s) written" << std::endl;
}

void Buffer::showLines(int from, int to) {
    for (int i = from; i <= to; i++) {
        std::cout << i << "\t" << lines.visit(i - 1) << std::endl;
    }
    currentLineNum = to;
}

void Buffer::deleteLines(int from, int to) {
    for (int i = from; i <= to; i++)
        lines.remove(from - 1);
    currentLineNum = from <= lines.getLength() ? from : lines.getLength();
}

void Buffer::insertLine(const string &text) {
    if (currentLineNum == 0) currentLineNum++;
    lines.insert(currentLineNum - 1, text);
}

void Buffer::appendLine(const string &text) {
    lines.insert(currentLineNum, text);
    currentLineNum++;
}

string Buffer::moveToLine(int idx) {
    currentLineNum = idx;
    return lines.visit(idx - 1);
}

int Buffer::getLength() const {
    return lines.getLength();
}
