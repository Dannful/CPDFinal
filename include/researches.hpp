#ifndef RESEARCHES_HPP
#define RESEARCHES_HPP

using namespace std;

#include "./hash_table.hpp"
#include "./graphics.hpp"
#include "./trie.hpp"
#include "read.hpp"
#include "constants.hpp"

void player_find(string &query, Trie &player_names_trie, HashTable<unsigned int, PlayerData *> &players) {
    vector<int> trie_results;
    string name = query.substr(query.find(' ') + 1, query.length());
    player_names_trie.search(name, trie_results);
    for (const unsigned int identifier: trie_results) {
        PlayerData player = **players.search(identifier);
        char separator[] = "\n";
        print_player(player, separator);
    }
}

void user_find(string &query, HashTable<unsigned int, PlayerData *> &players,
               const HashTable<unsigned int, set<ReviewedPlayer *, decltype(users_fun)> *> &users) {
    unsigned int user_id = stoi(query.substr(query.find(' ') + 1, query.length()));
    set<ReviewedPlayer *, decltype(users_fun)>::iterator itr;
    auto user_set = *(*users.search(user_id));
    unsigned int count = 0;
    for (itr = user_set.begin(); count < MAX_USER_ENTRIES && itr != user_set.end(); itr++, count++) {
        auto value = *itr;
        PlayerData player = **players.search(value->identifier);
        print_user_player(player, (float) value->rating);
    }
}

void top_find(string &query, HashTable<unsigned int, PlayerData *> &players,
              HashTable<string, set<ReviewedPlayer *, decltype(users_fun)> *> &positions) {
    string excluding_top = query.substr(query.find("top") + 3);
    unsigned int count = stoi(excluding_top.substr(0, excluding_top.find(' ')));
    string tag = excluding_top.substr(excluding_top.find(' ') + 1);
    tag = tag.substr(1, tag.length() - 2);
    set<ReviewedPlayer *, decltype(users_fun)>::iterator itr;
    auto user_set = *positions.search(tag);
    for (itr = user_set->begin(); count > 0 && itr != user_set->end(); itr++, count--) {
        auto value = *itr;
        PlayerData player = **players.search(value->identifier);
        char separator[] = "\n";
        print_player(player, separator);
    }
}

void tags_find(string &query, HashTable<unsigned int, PlayerData *> &players) {
    vector<string> tagList;
    vector<PlayerData> results; // ao final desse bloco, isso contem os jogadores com as tags
    string buffer;
    bool open = false;
    unsigned int length = query.length();

    for (int i = 0; i < length; i++) {
        char character = query.at(i);
        if (character == '\'') {
            if (!open) {
                open = true;
            } else {
                tagList.push_back(buffer);
                open = false;
            }
            buffer = "";
            continue;
        }
        buffer += character;
    }

    for (const auto &identifier: players.keySet()) {
        PlayerData player = **players.search(identifier);
        bool add = true;
        for (const auto &tag: tagList) {
            if (player.tags->find(tag) == player.tags->end()) {
                add = false;
                break;
            }
        }
        if (add)
            results.push_back(player);
    }

    for (const auto &item: results) {
        char separator[] = "\n";
        print_player(item, separator);
    }
}

#endif