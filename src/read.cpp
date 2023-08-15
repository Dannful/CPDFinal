#include "./read.hpp"
#include "binary_tree.hpp"
#include "hash_table.hpp"
#include <string>
#include <vector>


void read_players(Trie *trie, HashTable<unsigned int, PlayerData *> *player_table) {
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
        data->tags = new BinarySearchTree<string, short>([](const string &a, const string &b) {
            return strcmp(a.c_str(), b.c_str());
        });
        player_table->insert(identifier, data);
    }
    f.close();
}

void read_ratings(HashTable<unsigned int, PlayerData *> *player_table,
                  HashTable<unsigned int, BinarySearchTree<float, unsigned int> *> *users_table) {
    ifstream f(RATING_FILE_PATH);
    CsvParser parser(f);

    for (auto &row: parser) {
        if (row[0].at(0) == 'u')
            continue;
        unsigned int user_id = stoi(row[0]);
        unsigned int player_id = stoi(row[1]);
        float rating = stof(row[2]);
        BinarySearchTree<float, unsigned int> **user_tree = users_table->search(user_id);
        if (!user_tree) {
            auto *tree = new BinarySearchTree<float, unsigned int>([](float a, float b) {
                return a - b;
            });
            tree->insert(rating, player_id);
            users_table->insert(user_id, tree);
        } else {
            (*user_tree)->insert(rating, player_id);
        }
        PlayerData **data = player_table->search(player_id);
        if (data)
            (*data)->rating = ((*data)->rating * (*data)->count + rating) / ++((*data)->count);
    }
    f.close();
}

void read_tags(HashTable<unsigned int, PlayerData *> *player_table) {
    ifstream f(TAGS_FILE_PATH);
    CsvParser parser(f);
    for (auto &row: parser) {
        if (row[0].at(0) == 'u')
            continue;
        unsigned int player_id = stoi(row[1]);
        const string &tag = row[2];
        BinarySearchTree<string, short> *tags = (*player_table->search(player_id))->tags;
        tags->insert(tag, 0xF);
    }
    f.close();
}

void insert_into_positions(HashTable<string, BinarySearchTree<double, unsigned int> *> *positions, const string &tag,
                           unsigned int identifier, double rating) {
    BinarySearchTree<double, unsigned int> **stored = positions->search(tag);
    if (!stored) {
        auto *bst = new BinarySearchTree<double, unsigned int>([](double a, double b) {
            return a - b;
        });
        bst->insert(rating, identifier);
        positions->insert(tag, bst);
        return;
    }
    (*stored)->insert(rating, identifier);
}

void update_positions(HashTable<unsigned int, PlayerData *> *players,
                      HashTable<string, BinarySearchTree<double, unsigned int> *> *positions) {
    for (auto &identifier: players->keySet()) {
        PlayerData player = **players->search(identifier);
        if (player.count < MINIMUM_REVIEW_COUNT)
            continue;
        const char *static_tag = player.positions.data();
        char tag[strlen(static_tag) + 1] = {};
        strcpy(tag, static_tag);
        char *next = strtok(tag, ", ");
        while (next) {
            insert_into_positions(positions, next, identifier, player.rating);
            next = strtok(nullptr, ", ");
        }
    }
}