#include "./binary_tree.hpp"
#include "./graphics.hpp"
#include "./hash_table.hpp"
#include "./read.hpp"
#include "./trie.hpp"
#include "./bplus.hpp"
#include <cstdio>
#include <iostream>
#include <string>
using namespace aria::csv;
using namespace std;

#define PLAYERS_SIZE 32768 // tamanho da Hash Table precisa ser uma potencia de 2
#define USERS_SIZE 9366354
#define MAX_USER_ENTRIES 20

int main(void) {
  HashTable<PlayerData*> players(PLAYERS_SIZE);
  // HashTable<BinarySearchTree*> users(USERS_SIZE);
  Trie player_names_trie;
  BPTree *bplus;
  read_players(&player_names_trie, &players);
  // read_ratings(&players, &users);
  read_tags_ratings(bplus);
  
  bplus->display(bplus->getRoot());
  
  // bool condicao_parada = false;

  // while (!condicao_parada) {
  //   string query;
  //   cout << "Digite seu comando:" << endl;
  //   getline(std::cin, query);
  //   if (query.rfind("player", 0) == 0) {
  //     vector<int> trie_results;
  //     string name = query.substr(query.find(" ") + 1, query.length());
  //     player_names_trie.search(name, trie_results);
  //     for (const unsigned int identifier : trie_results) {
  //       PlayerData player = **players.search(identifier);
  //       char separator[] = "\n";
  //       print_player(player, separator);
  //     }
  //   } else if (query.rfind("user", 0) == 0) {
  //     unsigned int user_id =
  //         stoi(query.substr(query.find(" ") + 1, query.length()));
  //     (*users.search(user_id))->inorder_traverse(
  //         MAX_USER_ENTRIES, [&players](unsigned int identifier, double rating) {
  //           PlayerData player = **players.search(identifier);
  //           print_user_player(player, rating);
  //         });
  //   } else if (query.rfind("sair", 0) == 0) {
  //     cout << "Saindo" << endl;
  //     condicao_parada = true;
  //   }
  // }


}