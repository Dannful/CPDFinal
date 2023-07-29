#include "./trie.hpp"
#include <iostream>

int get_char(int index, string name) { return name.at(index) - 'a'; }

void Trie::initialize(trie_node *node) {
  node->left = nullptr;
  node->right = nullptr;
  node->mid = nullptr;
  node->identifier = -1;
}

trie_node *Trie::insert(trie_node *node, unsigned int identifier, string name,
                        unsigned int char_position) {
  char current_char = name.at(char_position);
  if (!node) {
    node = new trie_node;
    initialize(node);
    node->c = current_char;
  }
  if (node->c > current_char)
    node->left = insert(node->left, identifier, name, char_position);
  else if (node->c < current_char)
    node->right = insert(node->right, identifier, name, char_position);
  else if (char_position < name.length() - 1)
    node->mid = insert(node->mid, identifier, name, char_position + 1);
  else
    node->identifier = identifier;
  return node;
}

void Trie::insert(unsigned int identifier, string name) {
  root = insert(root, identifier, name, 0);
}

void Trie::search(trie_node *node, unsigned int current_char, string name,
                  string buffer, HashTable *out) {
  if (!node)
    return;
  char c = name.at(current_char);
  if (node->identifier != -1) {
    out->insert(node->identifier, buffer + string(1, c));
  }
  if (node->c > c)
    search(node->left, current_char, name, buffer, out);
  else if (node->c < c)
    search(node->right, current_char, name, buffer, out);
  else if (current_char < name.length() - 1)
    search(node->mid, current_char + 1, name, buffer + string(1, c), out);
}

void Trie::search(string name, HashTable *out) {
  search(root, 0, name, "", out);
  /* Versao iterativa unica, codigo feio
  trie_node *current = root;
  unsigned int char_pos = 0;
  string buffer = "";
  while (current) {
    char current_char = name.at(char_pos);
    if (current->identifier != -1) {
      out->insert(current->identifier, buffer + string(1, c));
    }
    if (current->c > current_char) {
      current = current->left;
    } else if (current->c < current_char) {
      current = current->right;
    } else {
      buffer += string(1, current_char);
      current = current->mid;
      char_pos++;
    }
  }*/
}