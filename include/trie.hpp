#ifndef TRIE_HPP
#define TRIE_HPP

using namespace std;

#include <string>
#include <vector>
#include "./hash_table.hpp"

struct trie_node {
    char character;
    struct trie_node *left, *mid, *right;
    int identifier;
};

class Trie {
    private:
    trie_node *root;
    
    trie_node *insert(trie_node *node, unsigned int identifier, string name, unsigned int char_position);
    void search(trie_node *node, vector<int> &players);
    void initialize(trie_node *node);

    public:
    Trie() {
        root = new trie_node;
        initialize(root);
        root->character = 0;
    }

    void insert(unsigned int identifier, string name);
    void search(string name, vector<int> &players);
};
#endif