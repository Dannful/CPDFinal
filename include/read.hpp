#ifndef READ_HPP
#define READ_HPP

#include "./hash_table.hpp"
#include "./trie.hpp"
#include "./csv-parser/parser.hpp"
#include "./binary_tree.hpp"

#define PLAYERS_FILE_PATH "arquivos-suporte/players.csv"
#define RATING_FILE_PATH "arquivos-suporte/rating.csv"
#define TAGS_FILE_PATH "arquivos-suporte/tags.csv"
#define MINIMUM_REVIEW_COUNT 1000

using namespace std;
using namespace aria::csv;

void read_players(Trie *trie, HashTable<unsigned int, PlayerData *> *player_table);

void read_ratings(HashTable<unsigned int, PlayerData *> *player_table, HashTable<unsigned int, BinarySearchTree<float, unsigned int>*> *users_table);

void read_tags(HashTable<unsigned int, PlayerData *> *player_table);

void update_positions(HashTable<unsigned int, PlayerData *> *players, HashTable<string, BinarySearchTree<double, unsigned int>*> *positions);

#endif