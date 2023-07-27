#include "./hash_table.hpp"

unsigned int hash_code(unsigned int identifier) {
  return (identifier * identifier + identifier) / 2;
}

void HashTable::insert(unsigned int identifier, string name) {
  unsigned int index = hash_code(identifier) % size;
  if (!linked_lists[index].tail)
    used++;
  linked_lists[index].insert(identifier, name);
}

SEARCH_RESULT HashTable::search(unsigned int identifier) {
  unsigned int index = hash_code(identifier) % size;
  return linked_lists[index].search(identifier);
}

LIST_STATS HashTable::calculate_list_stats() {
  LIST_STATS list_stats;
  list_stats.min = linked_lists[0].size;
  list_stats.max = linked_lists[0].size;
  list_stats.average = 0;
  for (int i = 0; i < size; i++) {
    if (linked_lists[i].size > list_stats.max)
      list_stats.max = linked_lists[i].size;
    if (linked_lists[i].size < list_stats.min)
      list_stats.min = linked_lists[i].size;
    list_stats.average += linked_lists[i].size;
  }
  list_stats.average /= (float) size;
  return list_stats;
}
