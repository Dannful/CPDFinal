#include "./binary_tree.hpp"
#include "./read.hpp"
#include "./researches.hpp"
#include <iostream>
#include <string>

using namespace std;


int main() {
    HashTable<unsigned int, PlayerData *> players(PLAYERS_SIZE, &hash_int);
    HashTable<unsigned int, BinarySearchTree<float, unsigned int> *> users(USERS_SIZE, &hash_int);
    HashTable<string, BinarySearchTree<double, unsigned int> *> positions(TAG_BUCKET_COUNT, &hash_string);
    Trie player_names_trie;
    bool halt_condition = false;

    read_players(&player_names_trie, &players);
    read_ratings(&players, &users);
    update_positions(&players, &positions);
    read_tags(&players);

    while (!halt_condition) {
        string query;

        cout << "Digite seu comando:" << endl;
        getline(std::cin, query);

        if (query.rfind("player", 0) == 0) 
            player_find(query, player_names_trie, players);
        else if (query.rfind("user", 0) == 0) 
            user_find(query,players, users);
        else if (query.rfind("top", 0) == 0) 
            top_find(query, players, positions);
        else if (query.rfind("tags", 0) == 0) 
            tags_find(query, players);
        else if (query.rfind("sair", 0) == 0) 
        {
            cout << "Saindo" << endl;
            halt_condition = true;
        }
        else
            cout << "Comando não especificado." << endl;
    }
}
