#include "./hash_table.hpp"

unsigned int hash_code(unsigned int identifier) {
  return ((identifier * identifier + identifier) / 2);
}

void PlayerTable::insert(PlayerData data) {
  unsigned int index = hash_code(data.identifier) % BUCKETS;

  if (table[index].empty())
    used++;

  table[index].push_back(data);
}

PlayerData PlayerTable::search(unsigned int identifier) {
  unsigned int index = hash_code(identifier) % BUCKETS;

  for (auto &element : table[index])
    if (element.identifier == identifier)
      return element;

  return PlayerData();
}