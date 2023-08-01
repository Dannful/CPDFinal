#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;

#include <list>
#include <string>

struct LIST_STATS {
  unsigned int min;
  unsigned int max;
  float average;
};

struct Data {
  unsigned int identifier;
  string name;
};

struct SEARCH_RESULT {
  unsigned int comparisons;
  string name;
};

class HashTable {
private:
  list<Data> *table;
  int BUCKETS;

public:
  unsigned int used = 0;

  HashTable(unsigned int s) {
    this->BUCKETS = s;
    table = new list<Data>[BUCKETS];
  }

  LIST_STATS calculate_list_stats();
  void insert(unsigned int identifier, string name);
  SEARCH_RESULT search(unsigned int identifier);
};
#endif
