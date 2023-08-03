#include "./read.hpp"
#include "hash_table.hpp"
#include "trie.hpp"
#include <iostream>
#include <string>

using namespace aria::csv;
using namespace std;

int main(void) {
  HashTable<PlayerData> players(
      32768); // tamanho da Hash Table precisa ser uma potencia de 2
  Trie player_names_trie;
  read_players(&player_names_trie, &players);
  read_ratings(&players);

  while (1) {
    vector<int> trie_results;
    string query;
    cout << "Digite seu comando:" << endl;
    getline(std::cin, query);
    if (query.rfind("player", 0) == 0) {
      string name = query.substr(query.find(" ") + 1, query.length());
      player_names_trie.search(name, trie_results);
      for (const unsigned int identifier : trie_results) {
        PlayerData player = *players.search(identifier);
        printf("%30s\t%1.5lf\t%5d\n", player.name.c_str(), player.rating,
               player.count);
      }
    }
  }
}