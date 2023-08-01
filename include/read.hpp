#ifndef READ_HPP
#define READ_HPP

#include "./csv-parser/parser.hpp"
#include "./hash_table.hpp"
#include "./trie.hpp"

using namespace aria::csv;
using namespace std;

void read_hash(HashTable *hash);
void read_trt(Trie *trie);

#endif
