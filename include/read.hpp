#ifndef READ_HPP
#define READ_HPP

#include "./hash_table.hpp"
#include "./trie.hpp"
#include "./csv-parser/parser.hpp"

using namespace aria::csv;

void read_players(Trie *trie, HashTable<PlayerData> *player_table);
void read_ratings(HashTable<PlayerData> *player_table);

#endif
