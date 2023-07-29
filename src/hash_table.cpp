#include "./hash_table.hpp"

unsigned int hash_code(unsigned int identifier) {
  return ((identifier * identifier + identifier) / 2);
}

void HashTable::insert(unsigned int identifier, string name) {
  unsigned int index = hash_code(identifier) % BUCKETS;
  Data data = {identifier, name};

  if (table[index].empty())
    used++;

  table[index].push_back(data);
}

SEARCH_RESULT HashTable::search(unsigned int identifier) {
  unsigned int index = hash_code(identifier) % BUCKETS;
  SEARCH_RESULT search_result = {0, ""};

  for(auto &element : table[index])
  {
    search_result.comparisons++;

    if(element.identifier == identifier)
      search_result.name = element.name;

    return search_result;
  }

  return search_result;
}

LIST_STATS HashTable::calculate_list_stats() {
  LIST_STATS list_stats;
  int total_lists;

  for(int index = 0; index < BUCKETS; index++)
  {
    total_lists = 0;
    for(auto &element : table[index])
      total_lists++;

    if(index != 0)
    {
      if(total_lists > list_stats.max)
        list_stats.max = total_lists;
      if(total_lists < list_stats.min)
        list_stats.min = total_lists;

      list_stats.average++;
    }
    else
    {
      list_stats.min = list_stats.max = total_lists;
      list_stats.average = 0;
    }
  }
  
  list_stats.average /= (float) BUCKETS;

  return list_stats;
}

