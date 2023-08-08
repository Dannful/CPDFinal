#include "./binary_tree.hpp"
#include "./graphics.hpp"
#include "./read.hpp"
#include <iostream>
#include <string>

using namespace std;

#define PLAYERS_SIZE 32768 // tamanho da Hash Table precisa ser uma potencia de 2
#define USERS_SIZE 9366354
#define MAX_USER_ENTRIES 20
#define TAG_BUCKET_COUNT 64

unsigned int hash_int(unsigned int identifier) {
    constexpr uint64_t BIT_NOISE1 = 0x9E3779B185EBCA87ULL;
    constexpr uint64_t BIT_NOISE2 = 0xC2B2AE3D27D4EB4FULL;
    constexpr uint64_t BIT_NOISE3 = 0x27D4EB2F165667C5ULL;
    identifier *= BIT_NOISE1;
    identifier ^= (identifier >> 8);
    identifier += BIT_NOISE2;
    identifier ^= (identifier << 8);
    identifier *= BIT_NOISE3;
    identifier ^= (identifier >> 8);
    return identifier;
}

unsigned int hash_string(string s) {
    unsigned int hash = 5381;
    char character;
    unsigned int character_position = 0;
    unsigned int length = s.length();

    while (character_position < length && (character = s.at(character_position++)))
        hash = ((hash << 5) + hash) + character;
    return hash;
}

int main() {
    HashTable<unsigned int, PlayerData *> players(PLAYERS_SIZE, &hash_int);
    HashTable<unsigned int, BinarySearchTree<float, unsigned int> *> users(USERS_SIZE, &hash_int);
    HashTable<string, BinarySearchTree<double, unsigned int> *> positions(TAG_BUCKET_COUNT, &hash_string);
    Trie player_names_trie;
    read_players(&player_names_trie, &players);
    read_ratings(&players, &users);
    update_positions(&players, &positions);
    read_tags(&players);
    bool halt_condition = false;

    while (!halt_condition) {
        string query;
        cout << "Digite seu comando:" << endl;
        getline(std::cin, query);
        if (query.rfind("player", 0) == 0) {
            vector<int> trie_results;
            string name = query.substr(query.find(' ') + 1, query.length());
            player_names_trie.search(name, trie_results);
            for (const unsigned int identifier: trie_results) {
                PlayerData player = **players.search(identifier);
                char separator[] = "\n";
                print_player(player, separator);
            }
        } else if (query.rfind("user", 0) == 0) {
            unsigned int user_id =
                    stoi(query.substr(query.find(' ') + 1, query.length()));
            (*users.search(user_id))->inorder_traverse(
                    MAX_USER_ENTRIES, [&players](float rating, unsigned int identifier) {
                        PlayerData player = **players.search(identifier);
                        print_user_player(player, rating);
                    });
        } else if (query.rfind("top", 0) == 0) {
            string excluding_top = query.substr(query.find("top") + 3);
            unsigned int count = stoi(excluding_top.substr(0, excluding_top.find(' ')));
            string tag = excluding_top.substr(excluding_top.find(' ') + 1);
            tag = tag.substr(1, tag.length() - 2);
            (*positions.search(tag))->inorder_traverse(count, [&players](double rating, unsigned int identifier) {
                PlayerData player = **players.search(identifier);
                char separator[] = "\n";
                print_player(player, separator);
            });
        } else if (query.rfind("tags", 0) == 0) {
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
        } else if (query.rfind("sair", 0) == 0) {
            cout << "Saindo" << endl;
            halt_condition = true;
        }
    }
}