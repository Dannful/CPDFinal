#ifndef BPLUS_HPP
#define BPLUS_HPP

#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>

#define MAX 20
using namespace std;

struct TagData
{
  unsigned int user_id;
  unsigned int sofifa_id;
  float rating;
  string tag;
};


class Node {
  bool IS_LEAF;
  int size;
  TagData *info;
  Node **ptr;
  friend class BPTree;

   public:
  Node();
};

// BP tree
class BPTree {
  Node *root;
  void insertInternal(TagData, Node *, Node *);
  Node *findParent(Node *, Node *);

   public:

  BPTree( );
  int search(int);     // pesquisa é feita por user.id
  void insert(TagData);
  void display(Node *);
  Node *getRoot();
  int update(TagData x);
};

#endif