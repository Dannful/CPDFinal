#include "./read.hpp"
#include "./researches.hpp"
#include "memory_management.hpp"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    HashTable<unsigned int, PlayerData *> players(PLAYERS_SIZE, &int_hash_function);
    HashTable<unsigned int, set<ReviewedPlayer *, decltype(users_fun)> *> users(USERS_SIZE, &int_hash_function);
    HashTable<string, set<ReviewedPlayer *, decltype(users_fun)> *> positions(TAG_BUCKET_COUNT, &string_hash_function);
    Trie player_names_trie;

    auto start = std::chrono::high_resolution_clock::now();
    read_players(player_names_trie, players);
    thread tags_thread(read_tags, &players);
    thread ratings_thread([](decltype(players) *players, decltype(users) *users, decltype(positions) *positions) {
        read_ratings(players, users);
        update_positions(players, positions);
    }, &players, &users, &positions);
    tags_thread.join();
    ratings_thread.join();
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    cout << "Levou " << duration << " segundo(s) para montar as estruturas." << endl;

    while (true) {
        string query;

        cout << "Digite seu comando:" << endl;
        getline(std::cin, query);

        if (query.rfind("player", 0) == 0)
            player_find(query, player_names_trie, players);
        else if (query.rfind("user", 0) == 0)
            user_find(query, players, users);
        else if (query.rfind("top", 0) == 0)
            top_find(query, players, positions);
        else if (query.rfind("tags", 0) == 0)
            tags_find(query, players);
        else if (query.rfind("sair", 0) == 0) {
            break;
        } else
            cout << "Comando não especificado." << endl;
    }
    free_memory(players, users, positions);
}
