#ifndef TRIE_HPP
#define TRIE_HPP

using namespace std;

#include <string>
#include <vector>
#include "./hash_table.hpp"

struct trie_node {
    char caracter;
    struct trie_node *left, *mid, *right;
    int identifier;
};

class Trie {
    private:
    trie_node *root;
    
    trie_node *insert(trie_node *node, unsigned int identifier, string name, unsigned int char_position);
    void search(trie_node *node, unsigned int current_char, string name, string buffer,  vector<int> &players);
    void display_trie(trie_node *root, char word[], int level);

    public:
    Trie() {
        root = new trie_node;
        initialize(root);
        root->caracter = 0;
    }

    trie_node get_root(Trie *trie);
    void initialize(trie_node *node);   // essa função não deveria ser privada? dai só o construtor acessa ela
    void insert(unsigned int identifier, string name);
    void search(string name, vector<int> &players);
    void display_trie();
};
#endif