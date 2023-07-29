#ifndef TRIE_H
#define TRIE_H

using namespace std;

#include <string>
#include <vector>
#include "./hash_table.hpp"

struct trie_node {
    char c;
    struct trie_node *left, *mid, *right;
    int identifier;
};

class Trie {
    private:
    trie_node *root;
    trie_node *insert(trie_node *node, unsigned int identifier, string name, unsigned int char_position);
    void search(trie_node *node, unsigned int current_char, string name, string buffer, HashTable *out);

    public:
    Trie() {
        root = new trie_node;
        initialize(root);
        root->c = 0;
    }

    void initialize(trie_node *node);
    void insert(unsigned int identifier, string name);
    void search(string name, HashTable *out);
};
#endif