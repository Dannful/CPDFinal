#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

using namespace std;

#include <list>
#include <string>

struct PlayerData {
  unsigned int identifier;
  string name;
  string positions;
  double rating;
  unsigned int count;
};

class PlayerTable {
private:
  list<PlayerData> *table;
  int BUCKETS;

public:
  unsigned int used = 0;

  PlayerTable(unsigned int s) {
    this->BUCKETS = s;
    table = new list<PlayerData>[BUCKETS];
  }

  void insert(PlayerData data);
  PlayerData search(unsigned int identifier);
};
#endif
