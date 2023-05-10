//
// Created by Smile on 2019/4/8.
//

#ifndef C_BINARYDIMEN_TREE_H
#define C_BINARYDIMEN_TREE_H

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

/****************************************************************
 *                    Write your code below
 ****************************************************************/

class TreeNode
{
  friend class BinaryDimonTree;

private:
  /* data */
  int data[2]{};
  bool idx;
  TreeNode *ln;
  TreeNode *rn;

public:
  /* methods */
  TreeNode(const int *d, bool idx, TreeNode *ln=nullptr, TreeNode *rn=nullptr):
  idx(idx), ln(ln), rn(rn) { data[0] = d[0]; data[1] = d[1]; }
  int getX();  /* DO NOT CHANGE */
  int getY();  /* DO NOT CHANGE */
  int getIdx() const { return idx; }
  int getTarget() const { return data[idx]; }
  ~TreeNode(); /* DO NOT CHANGE */
};


class BinaryDimonTree
{
friend istream &operator>>(istream &in, BinaryDimonTree &tree); /* DO NOT CHANGE */

private:
  /* data */
  TreeNode *root;
  double (*distance)(int, int, int, int);

public:
  /* methods */
  BinaryDimonTree();          /* DO NOT CHANGE */
  TreeNode *find_nearest_node(int x, int y);  /* DO NOT CHANGE */

  void insert(int *d) { insert(d, root, 0); }
  void insert(int *d, TreeNode *&t, bool i);
  void reset(TreeNode *t);

  void recur_search(TreeNode *cur, int *d, double &min_distance, TreeNode **guess);
  ~BinaryDimonTree();
};

#endif //C_BINARYDIMEN_TREE_H
