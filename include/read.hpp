#ifndef READ_HPP
#define READ_HPP

#include "./hash_table.hpp"
#include "./trie.hpp"
#include "./csv-parser/parser.hpp"
#include "constants.hpp"
#include "structures.hpp"

using namespace std;
using namespace aria::csv;

void read_players(Trie& trie, HashTable<unsigned int, PlayerData *>& player_table) {
    ifstream f(PLAYERS_FILE_PATH);
    CsvParser parser(f);

    for (auto &row: parser) {
        if (row[0].at(0) == 's')
            continue;
        unsigned int identifier = stoi(row[0]);
        const string &name = row[1];
        trie.insert(identifier, name);

        auto *data = new PlayerData;
        data->name = name;
        data->positions = row[2];
        data->identifier = identifier;
        data->rating = 0;
        data->count = 0;
        data->tags = new set<string>;
        player_table.insert(identifier, data);
    }
    f.close();
}

void read_ratings(HashTable<unsigned int, PlayerData *> *player_table,
                  HashTable<unsigned int, set<ReviewedPlayer *, decltype(users_fun)> *> *users_table) {
    ifstream f(RATING_FILE_PATH);
    CsvParser parser(f);

    for (auto &row: parser) {
        if (row[0].at(0) == 'u')
            continue;
        unsigned int user_id = stoi(row[0]);
        unsigned int player_id = stoi(row[1]);
        float rating = stof(row[2]);
        set<ReviewedPlayer *, decltype(users_fun)> **user_reviews = users_table->search(user_id);
        auto *new_review = new ReviewedPlayer;
        new_review->rating = rating;
        new_review->identifier = player_id;
        if (!user_reviews) {
            auto *new_set = new set<ReviewedPlayer *, decltype(users_fun)>(users_fun);
            new_set->insert(new_review);
            users_table->insert(user_id, new_set);
        } else {
            (*user_reviews)->insert(new_review);
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
        auto tags = (*player_table->search(player_id))->tags;
        tags->insert(tag);
    }
    f.close();
}

void
insert_into_positions(HashTable<string, set<ReviewedPlayer *, decltype(users_fun)> *> *positions, string &tag,
                      unsigned int identifier, double rating) {
    if (tag.at(0) == ' ')
        tag = tag.substr(1);
    auto stored = positions->search(tag);
    auto review = new ReviewedPlayer;
    review->rating = rating;
    review->identifier = identifier;
    if (!stored) {
        auto new_set = new set<ReviewedPlayer *, decltype(users_fun)>(users_fun);
        new_set->insert(review);
        positions->insert(tag, new_set);
        return;
    }
    (*stored)->insert(review);
}

void update_positions(HashTable<unsigned int, PlayerData *> *players,
                      HashTable<string, set<ReviewedPlayer *, decltype(users_fun)> *> *positions) {
    for (auto &identifier: players->keySet()) {
        PlayerData player = **players->search(identifier);
        if(player.count < MINIMUM_REVIEW_COUNT)
            return;
        istringstream stream(player.positions);
        string tag;
        while (getline(stream, tag, ','))
            insert_into_positions(positions, tag, identifier, player.rating);
    }
}

#endif