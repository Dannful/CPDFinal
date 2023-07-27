#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "./linked_list.hpp"

typedef struct {
  unsigned int min;
  unsigned int max;
  float average;
} LIST_STATS;

class HashTable {
private:
  LinkedList *linked_lists = nullptr;

public:
  unsigned int used = 0;
  unsigned int size;

  HashTable(unsigned int s) {
    linked_lists = new LinkedList[s]();
    size = s;
  }
  LIST_STATS calculate_list_stats();
  void insert(unsigned int identifier, string name);
  SEARCH_RESULT search(unsigned int identifier);
};
#endif
