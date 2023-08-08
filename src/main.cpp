#include "./binary_tree.hpp"
#include "./graphics.hpp"
#include "./read.hpp"
#include <iostream>
#include <string>

using namespace std;

#define PLAYERS_SIZE 32768 // tamanho da Hash Table precisa ser uma potencia de 2
#define USERS_SIZE 9366354
#define MAX_USER_ENTRIES 20
#define MINIMUM_REVIEW_COUNT 1000

int main() {
    HashTable<PlayerData *> players(PLAYERS_SIZE);
    HashTable<BinarySearchTree<PlayerWithRating *> *> users(USERS_SIZE);
    Trie player_names_trie;
    read_players(&player_names_trie, &players);
    read_ratings(&players, &users);
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
                    MAX_USER_ENTRIES, [&players](PlayerWithRating *playerWithRating) {
                        PlayerData player = **players.search(playerWithRating->identifier);
                        print_user_player(player, (float) playerWithRating->rating);
                    });
        } else if (query.rfind("top", 0) == 0) {
            string excluding_top = query.substr(query.find("top") + 3);
            unsigned int count = stoi(excluding_top.substr(0, excluding_top.find(' ')));
            string tag = excluding_top.substr(excluding_top.find(' ') + 1);
            BinarySearchTree<PlayerWithRating> tree([](PlayerWithRating a, PlayerWithRating b) {
                return a.rating - b.rating;
            });
            for (unsigned int identifier: players.keySet()) {
                PlayerData player = **players.search(identifier);
                if (player.count < MINIMUM_REVIEW_COUNT)
                    continue;
                if (player.positions.find(tag) == string::npos)
                    continue;
                tree.insert({identifier, player.rating});
            }
            tree.inorder_traverse(count, [&players](PlayerWithRating playerWithRating) {
                PlayerData player = **players.search(playerWithRating.identifier); // cada um desses jogadores esta no ranking
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
                    PlayerWithTag playerWithTag = {identifier, tag};
                    if (!player.tags->contains(&playerWithTag)) {
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