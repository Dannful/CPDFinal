#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "structures.hpp"
#include "hash_table.hpp"

void free_memory(HashTable<unsigned int, PlayerData *> &players,
                 HashTable<unsigned int, set < ReviewedPlayer * , decltype(users_fun)> *>& users,
                 HashTable<string, set < ReviewedPlayer * , decltype(users_fun)> *>& positions) {
    cout << "Liberando memoria..." << endl;
    for (const auto &item: players.keySet())
        delete *players.search(item);
    for (const auto &item: users.keySet()) {
        auto bucket = *users.search(item);
        set<ReviewedPlayer*, decltype(users_fun)>::iterator iterator;
        for(iterator = bucket->begin(); iterator != bucket->end(); iterator++)
            delete *iterator;
        delete bucket;
    }
    for (const auto &item: positions.keySet()) {
        auto bucket = *positions.search(item);
        set<ReviewedPlayer*, decltype(users_fun)>::iterator iterator;
        for(iterator = bucket->begin(); iterator != bucket->end(); iterator++)
            delete *iterator;
        delete bucket;
    }
}

#endif