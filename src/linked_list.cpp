#include "./linked_list.hpp"

void LinkedList::insert(unsigned int identifier, string name) {
  NODE *new_node = nullptr;
  if (!tail) {
    tail = new NODE;
    new_node = tail;
  } else {
    tail->next = new NODE;
    new_node = tail->next;
  }
  new_node->next = nullptr;
  new_node->data.identifier = identifier;
  new_node->data.name = name;
  size++;
}

SEARCH_RESULT LinkedList::search(unsigned int identifier) {
  SEARCH_RESULT search_result;
  search_result.comparisons = 0;
  search_result.name[0] = '\0';
  NODE *current = tail;
  while (current) {
    search_result.comparisons++;
    if (current->data.identifier == identifier) {
      search_result.name = current->data.name;
      return search_result;
    }
    current = current->next;
  }
  return search_result;
}