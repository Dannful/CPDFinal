#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <string>
using namespace std;

typedef struct {
  unsigned int comparisons;
  string name;
} SEARCH_RESULT;

typedef struct {
  unsigned int identifier;
  string name;
} DATA;

typedef struct node {
  struct node *next;
  DATA data;
} NODE;

class LinkedList {
public:
  NODE *tail = nullptr;
  unsigned int size = 0;
  
  void insert(unsigned int identifier, string name);
  SEARCH_RESULT search(unsigned int identifier);
};
#endif
