#include "./read.hpp"
#include "hash_table.hpp"
#include <iostream>
#include <string>
#define PLAYERS_FILE_PATH "arquivos-suporte/players.csv"
#define RATING_FILE_PATH "arquivos-suporte/rating.csv"
#define TAGS_FILE_PATH "arquivos-suporte/tags.csv"

using namespace std;

void read_players(Trie *trie, PlayerTable *table) {
  ifstream f(PLAYERS_FILE_PATH);
  CsvParser parser(f);

  for (auto &row : parser) {
    if (row[0].at(0) == 's')
      continue;
    unsigned int identifier = stoi(row[0]);
    string name = row[1];
    trie->insert(identifier, name);

    PlayerData data;
    data.identifier = identifier;
    data.name = name;
    data.positions = row[2];
    table->insert(data);
  }
  f.close();
}