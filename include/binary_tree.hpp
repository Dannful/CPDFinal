#ifndef BINARY_TREE_HPP
#define BINARY_TREE_HPP

#include <bits/stdc++.h>

using namespace std;

struct BinaryTreeNode {
  struct BinaryTreeNode *left, *right;
  unsigned int identifier;
  double rating;
};

class BinarySearchTree {
private:
  BinaryTreeNode *root = nullptr;
  BinaryTreeNode *insert(BinaryTreeNode *node, unsigned int identifier, double rating);
  void inorder_traverse(unsigned int max, unsigned int *visited,
                        BinaryTreeNode *node,
                        function<void(unsigned int, double)> on_element);

public:
  void insert(unsigned int identifier, double rating);
  void inorder_traverse(unsigned int count,
                        function<void(unsigned int, double)> on_element);
  double search(unsigned int identifier);
};
#endif