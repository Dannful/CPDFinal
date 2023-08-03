#include "./read.hpp"
#include "hash_table.hpp"
#include <iostream>
#include <string>
#include <vector>
#define PLAYERS_FILE_PATH "arquivos-suporte/players.csv"
#define RATING_FILE_PATH "arquivos-suporte/rating.csv"
#define TAGS_FILE_PATH "arquivos-suporte/tags.csv"

using namespace std;

void read_players(Trie *trie, HashTable<PlayerData> *player_table) {
  ifstream f(PLAYERS_FILE_PATH);
  CsvParser parser(f);

  for (auto &row : parser) {
    if (row[0].at(0) == 's')
      continue;
    unsigned int identifier = stoi(row[0]);
    string name = row[1];
    trie->insert(identifier, name);

    PlayerData data;
    data.name = name;
    data.positions = row[2];
    data.identifier = identifier;
    data.rating = 0;
    data.count = 0;
    player_table->insert(identifier, data);
  }
  f.close();
}

void read_ratings(HashTable<PlayerData> *player_table) {
  ifstream f(RATING_FILE_PATH);
  CsvParser parser(f);

  for (auto &row : parser) {
    if (row[0].at(0) == 'u')
      continue;
    unsigned int user_id = stoi(row[0]);
    unsigned int player_id = stoi(row[1]);
    float rating = stof(row[2]);
    PlayerData *data =
        player_table->search(player_id);
    if (data)
      data->rating = (data->rating * data->count + rating) / ++(data->count);
  }
  f.close();
}