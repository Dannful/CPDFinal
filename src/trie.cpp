#include "./trie.hpp"
#include <iostream>

int get_char(int index, string name) { return name.at(index) - 'a'; }

void Trie::initialize(trie_node *node) {
  node->left = nullptr;
  node->right = nullptr;
  node->mid = nullptr;
  node->identifier = -1;
}

void Trie::insert(unsigned int identifier, string name) {
  root = insert(root, identifier, name, 0);
}

trie_node *Trie::insert(trie_node *node, unsigned int identifier, string name, unsigned int char_position) {
  char current_char = name.at(char_position);

  if (!node) {
    node = new trie_node;
    initialize(node);
    node->caracter = current_char;
  }
  else
  {
    if (node->caracter > current_char)
    node->left = insert(node->left, identifier, name, char_position);
    else if (node->caracter < current_char)
      node->right = insert(node->right, identifier, name, char_position);
    else
    {
      if (char_position < name.length() - 1)
      node->mid = insert(node->mid, identifier, name, char_position + 1);
      else
        node->identifier = identifier;
    }
  }

  return node;
}

void Trie::search(string name, vector<int> &players) {
  search(root, 0, name, "", players);
}

void Trie::search(trie_node *node, unsigned int current_char, string name,
                  string buffer, vector<int> &players) {
  if (!node)
    return;

  char caracter = name.at(current_char);
  
  if (node->identifier != -1) {
    // players->insert(node->identifier, buffer + string(1, caracter));
    players.push_back(node->identifier);
  }
  if (node->caracter > caracter)
    search(node->left, current_char, name, buffer, players);
  else if (node->caracter < caracter)
    search(node->right, current_char, name, buffer, players);
  else if (current_char < name.length() - 1)
    search(node->mid, current_char + 1, name, buffer + string(1, caracter), players);
}


void Trie::display_trie(trie_node *root, char word[], int level)
{
  if(!root)
    return;
  
  if(root->identifier != -1)
  {
    word[level] = '\0';
    cout << word << endl;
  }
  else
  {
    display_trie(root->left, word, level + 1);
    display_trie(root->mid, word, level + 1);
    display_trie(root->right, word, level + 1);
  }
  

}