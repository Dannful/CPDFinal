#include "researches.hpp"

void player_find(string &query, Trie &player_names_trie, HashTable<unsigned int, PlayerData *> &players)
{
    vector<int> trie_results;
    string name = query.substr(query.find(' ') + 1, query.length());
    player_names_trie.search(name, trie_results);
    for (const unsigned int identifier: trie_results) {
        PlayerData player = **players.search(identifier);
        char separator[] = "\n";
        print_player(player, separator);
    }
}

void user_find(string &query,HashTable<unsigned int, PlayerData *> &players, HashTable<unsigned int, BinarySearchTree<float, unsigned int> *> &users)
{
    unsigned int user_id = stoi(query.substr(query.find(' ') + 1, query.length()));

    (*users.search(user_id))->inorder_traverse(MAX_USER_ENTRIES, [&players](float rating, unsigned int identifier) 
    {
        PlayerData player = **players.search(identifier);
        print_user_player(player, rating);
    });
}

void top_find(string &query, HashTable<unsigned int, PlayerData *> &players, HashTable<string, BinarySearchTree<double, unsigned int> *> &positions)
{
    string excluding_top = query.substr(query.find("top") + 3);
    unsigned int count = stoi(excluding_top.substr(0, excluding_top.find(' ')));
    string tag = excluding_top.substr(excluding_top.find(' ') + 1);

    tag = tag.substr(1, tag.length() - 2);

    (*positions.search(tag))->inorder_traverse(count, [&players](double rating, unsigned int identifier) {
        PlayerData player = **players.search(identifier);
        char separator[] = "\n";
        print_player(player, separator);
    });
}

void tags_find(string &query, HashTable<unsigned int, PlayerData *> &players)
{
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
            if (!player.tags->contains(tag)) {
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