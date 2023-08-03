#include "./read.hpp"
#include "hash_table.hpp"
#include "trie.hpp"
#include <iostream>
#include <string>
using namespace aria::csv;
using namespace std;

#define BUCKET 32768 // tamanho da Hash Table precisa ser uma potencia de 2
#define MAXIMO_JOGADORES 20

int main(void) {
  HashTable<PlayerData> players(BUCKET); 
  Trie player_names_trie;
  read_players(&player_names_trie, &players);
  read_ratings(&players);
  bool condicao_parada = false;

  while (!condicao_parada) {
    string query;
    cout << "Digite seu comando:" << endl;
    getline(std::cin, query);
    if (query.rfind("player", 0) == 0) {
      vector<int> trie_results;
      string name = query.substr(query.find(" ") + 1, query.length());
      player_names_trie.search(name, trie_results);
      for (const unsigned int identifier : trie_results) {
        PlayerData player = *players.search(identifier);
        printf("%30s\t%1.5lf\t%5d\n", player.name.c_str(), player.rating,
               player.count);
      }
    }
    else if(query.rfind("user", 0) == 0)  // precisa de uma b+ tree
    {
      int id_user = stoi(query.substr(query.find(" ") + 1, query.length()));
    }
    else if(query.rfind("sair", 0) == 0)
    {
      cout << "Saindo" << endl;
      condicao_parada = true;
    }
  }
}