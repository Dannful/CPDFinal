#ifndef RESEARCHES_HPP
#define RESEARCHES_HPP

using namespace std;

#include "./hash_table.hpp"
#include "./graphics.hpp"
#include "./trie.hpp"

#define PLAYERS_SIZE 32768 
#define USERS_SIZE 9366354
#define MAX_USER_ENTRIES 20
#define TAG_BUCKET_COUNT 64


void player_find(string &query, Trie &player_names_trie, HashTable<unsigned int, PlayerData *> &players);
void user_find(string &query, HashTable<unsigned int, PlayerData *> &players, HashTable<unsigned int, BinarySearchTree<float, unsigned int> *> &users);
void top_find(string &query, HashTable<unsigned int, PlayerData *> &players, HashTable<string, BinarySearchTree<double, unsigned int> *> &positions);
void tags_find(string &query, HashTable<unsigned int, PlayerData *> &players);

#endif