#include "./read.hpp"
#include "binary_tree.hpp"
#include "hash_table.hpp"
#include <string>
#include <vector>

using namespace std;

void read_players(Trie *trie, HashTable<PlayerData *> *player_table) {
    ifstream f(PLAYERS_FILE_PATH);
    CsvParser parser(f);

    for (auto &row: parser) {
        if (row[0].at(0) == 's')
            continue;
        unsigned int identifier = stoi(row[0]);
        const string &name = row[1];
        trie->insert(identifier, name);

        auto *data = new PlayerData;
        data->name = name;
        data->positions = row[2];
        data->identifier = identifier;
        data->rating = 0;
        data->count = 0;
        data->tags = new BinarySearchTree<PlayerWithTag *>([](PlayerWithTag *a, PlayerWithTag *b) {
            return strcmp(a->tag.c_str(), b->tag.c_str());
        });
        player_table->insert(identifier, data);
    }
    f.close();
}

void read_ratings(HashTable<PlayerData *> *player_table,
                  HashTable<BinarySearchTree<PlayerWithRating *> *> *users_table) {
    ifstream f(RATING_FILE_PATH);
    CsvParser parser(f);

    for (auto &row: parser) {
        if (row[0].at(0) == 'u')
            continue;
        unsigned int user_id = stoi(row[0]);
        unsigned int player_id = stoi(row[1]);
        float rating = stof(row[2]);
        BinarySearchTree<PlayerWithRating *> **user_tree = users_table->search(user_id);
        auto *playerWithRating = new PlayerWithRating;
        playerWithRating->rating = rating;
        playerWithRating->identifier = player_id;
        if (!user_tree) {
            auto *tree = new BinarySearchTree<PlayerWithRating *>([](PlayerWithRating *a, PlayerWithRating *b) {
                return a->rating - b->rating;
            });
            tree->insert(playerWithRating);
            users_table->insert(user_id, tree);
        } else {
            (*user_tree)->insert(playerWithRating);
        }
        PlayerData **data = player_table->search(player_id);
        if (data)
            (*data)->rating = ((*data)->rating * (*data)->count + rating) / ++((*data)->count);
    }
    f.close();
}

void read_tags(HashTable<PlayerData *> *player_table) {
    ifstream f(TAGS_FILE_PATH);
    CsvParser parser(f);
    for (auto &row: parser) {
        if (row[0].at(0) == 'u')
            continue;
        unsigned int player_id = stoi(row[1]);
        const string &tag = row[2];
        BinarySearchTree<PlayerWithTag *> *tags = (*player_table->search(player_id))->tags;
        auto *playerWithTag = new PlayerWithTag;
        playerWithTag->identifier = player_id;
        playerWithTag->tag = tag;
        tags->insert(playerWithTag);
    }
    f.close();
}