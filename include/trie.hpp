#ifndef TRIE_H
#define TRIE_H

using namespace std;

#include <string>
#include <vector>
#include "./hash_table.hpp"

struct trie_node {
    struct trie_node *equal;
    vector<struct trie_node> smaller;
    vector<struct trie_node> grater;
    int identifier;
};

class Trie {
    private:
    trie_node root;

    public:
    Trie() {
        root.identifier = -1;
        initialize(&root);
    }

    void initialize(trie_node *node);
    void insert(unsigned int identifier, string name);
    void search(string name, HashTable *out);
};
#endif