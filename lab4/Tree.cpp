#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>

#include "Tree.h"

using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/
double Distance(int x1, int y1, int x2, int y2) {
    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

int TreeNode::getX() {
    // TODO: Your code here
    return data[0];
}

int TreeNode::getY() {
    // TODO: Your code here
    return data[1];
}

TreeNode::~TreeNode() {
    // TODO: Your code here
}

istream &operator>>(istream &in, BinaryDimonTree &tree) {
    // TODO: Your code here
    int num, d[2];
    in >> num;
//    for (int i = 0; i < num; i++) {
//        in >> d[0] >> d[1];
//        tree.insert(d);
//    }
    auto data = new int[num * 2]{};
    auto flag = new bool[num]{};

    int i, j;
    srand(0);
    for (i = 0; i < num; i++) {
        j = rand() % num;
        while (flag[j]) j = (j + 1) % num;
        in >> data[j * 2] >> data[j * 2 + 1];
        flag[j] = true;
    }

    for (i = 0; i < num; i++)
        tree.insert(data + i * 2);

    delete []data;
    delete []flag;


    return in;
}

BinaryDimonTree::BinaryDimonTree(): root(nullptr), distance(&Distance) {
    // TODO: Your code here
}

TreeNode *BinaryDimonTree::find_nearest_node(int x, int y) {
    // TODO: Your code here
    TreeNode *guess = nullptr;
    auto bestDist = (double)INT64_MAX;

    int d[] = {x, y};
//    return new TreeNode(d, 0);
    recur_search(root, d, bestDist, &guess);
    return guess;
}

void BinaryDimonTree::recur_search(TreeNode *cur, int *d, double &min_distance, TreeNode **guess) {
    // TODO: Your code here
    if (cur == nullptr) return;

    int cX = cur->getX(), cY = cur->getY();
    double dist = distance(d[0], d[1], cX, cY);
    if (dist < min_distance ||
            dist == min_distance && (
            *guess == nullptr
            || (*guess)->getX() > cX ||
            ((*guess)->getX() == cX && (*guess)->getY() > cY)
            )) {
        min_distance = dist;
        *guess = cur;
    }

    int targetD = d[cur->getIdx()], targetC = cur->getTarget();
    bool l = targetD < targetC;

    recur_search(l ? cur->ln : cur->rn, d, min_distance, guess);

    if (pow(targetC - targetD, 2) <= min_distance)
        recur_search(!l ? cur->ln : cur->rn, d, min_distance, guess);
}

BinaryDimonTree::~BinaryDimonTree()
{
    // TODO: Your code here
    reset(root);
}

void BinaryDimonTree::insert(int *d, TreeNode *&t, bool i) {
    if (t == nullptr) {
        t = new TreeNode(d, i);
        return;
    }
    if (d[t->getIdx()] < t->getTarget()) insert(d, t->ln, !i);
    else insert(d, t->rn, !i);
}

void BinaryDimonTree::reset(TreeNode *t) {
    if (t == nullptr) return;
    reset(t->ln);
    reset(t->rn);
    delete t;
}
