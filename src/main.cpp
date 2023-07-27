#include "./csv-parser/parser.hpp"
#include "./hash_table.hpp"
#include "./linked_list.hpp"
#include "./trie.hpp"
#include <iostream>
#include <string>

using namespace aria::csv;
using namespace std;

void read_players(HashTable *table) {
  ifstream f("arquivos-suporte/players.csv");
  CsvParser parser(f);
  bool first = false;
  for (auto &row : parser) {
    if (!first) {
      first = true;
      continue;
    }
    unsigned int identifier = stoi(row[0]);
    string name = row[1];
    table->insert(identifier, name);
  }
}

int main(void) {
  /* exemplo bobo de como usar as estruturas de dados */
  Trie trie;
  HashTable table(100);
  trie.insert(13, "romano");
  trie.insert(20, "romeno");
  trie.insert(50, "roma");
  trie.search("romano", &table); // os resultados da busca (strings que iniciam com "romano") sao colocados na hash table referenciada
  cout << table.search(50).name << endl;
}