#ifndef READ_HPP
#define READ_HPP

#include "./hash_table.hpp"
#include "./trie.hpp"
#include "./csv-parser/parser.hpp"
#include "./binary_tree.hpp"
#include "binary_tree.hpp"

#define PLAYERS_FILE_PATH "arquivos-suporte/players.csv"
#define RATING_FILE_PATH "arquivos-suporte/rating.csv"
#define TAGS_FILE_PATH "arquivos-suporte/tags.csv"

using namespace aria::csv;

void read_players(Trie *trie, HashTable<PlayerData*> *player_table);
void read_ratings(HashTable<PlayerData*> *player_table, HashTable<BinarySearchTree*> *users_table);

#endif