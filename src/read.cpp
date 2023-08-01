#include "./read.hpp"

void read_trt(Trie *trie) {
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
    trie->insert(identifier, name);
  }
}

void read_hash(HashTable *hash) {
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
    hash->insert(identifier, name);
  }
}

