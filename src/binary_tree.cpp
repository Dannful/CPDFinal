#include "./binary_tree.hpp"

BinaryTreeNode *BinarySearchTree::insert(BinaryTreeNode *node,
                                         unsigned int identifier,
                                         double rating) {
  if (!node) {
    node = new BinaryTreeNode;
    node->left = node->right = nullptr;
    node->identifier = identifier;
    node->rating = rating;
    return node;
  }
  if (node->rating > rating)
    node->left = insert(node->left, identifier, rating);
  else
    node->right = insert(node->right, identifier, rating);
  return node;
}

void BinarySearchTree::insert(unsigned int identifier, double rating) {
  root = insert(root, identifier, rating);
}

void BinarySearchTree::inorder_traverse(
    unsigned int max, unsigned int *visited, BinaryTreeNode *node,
    function<void(unsigned int, double)> on_element) {
  if (!node || max == *visited)
    return;
  (*visited)++;
  inorder_traverse(max, visited, node->right, on_element);
  on_element(node->identifier, node->rating);
  inorder_traverse(max, visited, node->left, on_element);
}

void BinarySearchTree::inorder_traverse(
    unsigned int count, function<void(unsigned int, double)> on_element) {
  unsigned int visited = 0;
  inorder_traverse(count, &visited, root, on_element);
}