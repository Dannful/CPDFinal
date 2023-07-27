#ifndef TRIE_H
#define TRIE_H
#define ALPHABET_SIZE 26
using namespace std;
#include <string>
#include "./hash_table.hpp"

typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];
    int identifier;
} TRIE_NODE;

class Trie {
    private:
    TRIE_NODE root;

    public:
    Trie() {
        root.identifier = -1;
        initialize(&root);
    }

    void initialize(TRIE_NODE *node);
    void insert(unsigned int identifier, string name);
    void search(string name, HashTable *out);
};
#endif