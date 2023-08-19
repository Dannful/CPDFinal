#include "./trie.hpp"
#include <iostream>

void Trie::initialize(trie_node *node) {
    node->left = nullptr;
    node->right = nullptr;
    node->mid = nullptr;
    node->identifier = -1;
}

void Trie::insert(unsigned int identifier, string name) {
    root = insert(root, identifier, name, 0);
}

trie_node *Trie::insert(trie_node *node, unsigned int identifier, string name,
                        unsigned int char_position) {
    char current_char = name.at(char_position);
    if (!node) {
        node = new trie_node;
        initialize(node);
        node->character = current_char;
    }
    if (node->character > current_char)
        node->left = insert(node->left, identifier, name, char_position);
    else if (node->character < current_char)
        node->right = insert(node->right, identifier, name, char_position);
    else if (char_position < name.length() - 1)
        node->mid = insert(node->mid, identifier, name, char_position + 1);
    else
        node->identifier = identifier;
    return node;
}

void Trie::search(string name, vector<int> &players) {
    unsigned int char_position = 0;
    unsigned int length = name.length();
    trie_node *current_node = root;
    while (current_node && char_position < length) {
        char current_character = name.at(char_position);
        if (current_node->character > current_character) {
            current_node = current_node->left;
        } else if (current_node->character < current_character) {
            current_node = current_node->right;
        } else {
            current_node = current_node->mid;
            char_position++;
        }
    }
    search(current_node, players);
}

void Trie::search(trie_node *node, vector<int> &players) {
    if (!node)
        return;
    if (node->identifier != -1)
        players.push_back(node->identifier);
    search(node->left, players);
    search(node->right, players);
    search(node->mid, players);
}