#include "./read.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void read_players(Trie *trie, HashTable<PlayerData*> *player_table) {
  ifstream f(PLAYERS_FILE_PATH);
  CsvParser parser(f);

  for (auto &row : parser) {
    if (row[0].at(0) == 's')
      continue;
    unsigned int identifier = stoi(row[0]);
    string name = row[1];
    trie->insert(identifier, name);

    PlayerData *data = new PlayerData;
    data->name = name;
    data->positions = row[2];
    data->identifier = identifier;
    data->rating = 0;
    data->count = 0;
    player_table->insert(identifier, data);
  }
  f.close();
}


void read_tags_ratings(BPTree *bplus) {
  ifstream fr(RATING_FILE_PATH);
  CsvParser parserr(fr);

  for (auto &row : parserr) {
    if (row[0].at(0) == 's')
      continue;
    unsigned int identifier = stoi(row[0]);
    unsigned int sofifa_id = stoi(row[1]);
    float rating = stof(row[2]);
    TagData data;
    data.user_id = identifier;
    data.sofifa_id = sofifa_id;
    data.rating = rating;
    bplus->insert(data);
  }
  fr.close();
  
  ifstream ft(TAGS_FILE_PATH);
  CsvParser parsert(ft);

  for (auto &row : parsert)
  {
    if(row[0].at(0) == 's')
      continue;
    unsigned int identifier = stoi(row[0]);
    unsigned int sofifa_id = stoi(row[1]);
    string tag = row[2];
    
    TagData data;
    data.user_id = identifier;
    data.sofifa_id = sofifa_id;
    data.tag = tag;

    if(bplus->search(identifier))
      bplus->update(data);    //da para ver se deu certo ou nao com um if!
    else
      bplus->insert(data);
  }

  ft.close();
}

void read_ratings(HashTable<PlayerData*> *player_table,
                  HashTable<BinarySearchTree *> *users_table) {
  ifstream f(RATING_FILE_PATH);
  CsvParser parser(f);

  for (auto &row : parser) {
    if (row[0].at(0) == 'u')
      continue;
    unsigned int user_id = stoi(row[0]);
    unsigned int player_id = stoi(row[1]);
    float rating = stof(row[2]);
    BinarySearchTree **user_tree = users_table->search(user_id);
    if (!user_tree) {
      BinarySearchTree *tree = new BinarySearchTree;
      tree->insert(player_id, rating);
      users_table->insert(user_id, tree);
    } else {
      (*user_tree)->insert(player_id, rating);
    }
    PlayerData **data = player_table->search(player_id);
    if (data)
      (*data)->rating = ((*data)->rating * (*data)->count + rating) / ++((*data)->count);
  }
  f.close();
}