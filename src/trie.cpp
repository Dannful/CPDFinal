#include "./trie.hpp"

int get_char(int index, string name) {
    return name.at(index) - 'a';
}

void Trie::initialize(TRIE_NODE *node) {
    for(int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = nullptr;
        node->identifier = -1;
    }
}

void Trie::insert(unsigned int identifier, string name) {
    TRIE_NODE *current_node = &root;
    int length = name.length();
    for(int i = 0; i < length; i++) {
        if(!current_node->children[get_char(i, name)]) {
            current_node->children[get_char(i, name)] = new TRIE_NODE;
            initialize(current_node->children[get_char(i, name)]);
        }
        current_node = current_node->children[get_char(i, name)];
    }
    current_node->identifier = identifier;
}

void Trie::search(string name, HashTable *out) {
    TRIE_NODE *current_node = &root;
    int length = name.length();
    string buffer;
    for(int i = 0; i < length && current_node; i++) {
        buffer += string(1, name.at(i));
        if(current_node->identifier != -1) {
            out->insert(current_node->identifier, buffer);
            buffer = "";
        }
        current_node = current_node->children[get_char(i, name)];
    }
}