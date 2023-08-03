#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//int MAX = 3;

class Node {
  bool IS_LEAF;
  int *key, size;
  Node **ptr;
  friend class BPTree;

   public:
  Node(int max);
};

// BP tree
class BPTree {
  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

   public:
  int max;

  BPTree(int max);
  void search(int);
  void insert(int);
  void display(Node *);
  Node *getRoot();
};
